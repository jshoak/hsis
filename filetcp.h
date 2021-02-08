#pragma once
#ifndef _FILETCP_H_
#define _FILETCP_H_
#include <WS2tcpip.h>
#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")
constexpr int A_data_size = 1024;
class filetcp
{
private:
protected:
    sockaddr_in servAddr;
    SOCKET sock, _sock_;
    WSADATA wsaData;
    char buffer[A_data_size];
    int len, size, number;
    FILE* fp;
public:
    void file_send(char* p);
    void file_recv(char* p);
    filetcp(int port, const char* s);
    filetcp(int port);
    ~filetcp();
};
filetcp::filetcp(int port, const char* s) : len(0), size(0), number(0), sock(0),  _sock_(0) {
    memset(buffer, 0, A_data_size);
    memset(&servAddr, 0, sizeof(sockaddr_in));
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    _sock_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    inet_pton(AF_INET, s, &servAddr.sin_addr.s_addr);
    connect(_sock_, (SOCKADDR*)&servAddr, sizeof(sockaddr_in));
}
filetcp::filetcp(int port) : len(0), size(0), number(0), sock(0), _sock_(0) {
    memset(buffer, 0, A_data_size);
    memset(&servAddr, 0, sizeof(sockaddr_in));
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
    listen(sock, 2);
    _sock_ = accept(sock, nullptr, nullptr);
}
void filetcp::file_send(char* p) {
    fopen_s(&fp, p, "rb");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    send(_sock_, (char*)&size, sizeof(size), 0);
    recv(_sock_, (char*)&size, sizeof(size), 0);
    while ((len = fread(buffer, 1, A_data_size, fp)) > 0)
        send(_sock_, buffer, len, 0);
    fclose(fp);
}
void filetcp::file_recv(char* p) {
    fopen_s(&fp, p, "wb");
    recv(_sock_, (char*)&size, sizeof(size), 0);
    send(_sock_, (char*)&size, sizeof(size), 0);
    while (number != size) {
        len = recv(_sock_, buffer, A_data_size, 0);
        fwrite(buffer, len, 1, fp);
        number += len;
    }   
    fclose(fp);
}
filetcp::~filetcp() {
    closesocket(sock);
    closesocket(_sock_);
    WSACleanup();
}
#endif