#include <WS2tcpip.h>
#include<windows.h>
#include <string.h>
#include <thread>
#pragma comment(lib, "Ws2_32.lib")
#pragma once
#ifndef _dataudp_
#define _dataudp_
#define A_data_size 1024*2
class dataudp
{
private:
    int i, k, kai;
    sockaddr_in servAddr, servAddr_1;
    SOCKET sock;
    WSADATA wsaData;
    char* p;
    static int length;
    struct ppp{
        int number;
        char data[1024];
    } ;
    ppp nd, nd1, nd2;
public:
    dataudp(int port, const char* s);
    dataudp(int port);
    ~dataudp();
    void data_send(char* p, int n);
    void data_recv(char* p, int n);
    void data_recv1(char* p, int n);
    void data_recv2(char* p, int n);
    void drecv(char* p, int n);
};
int dataudp::length = sizeof(sockaddr_in);
dataudp::dataudp(int port, const char* s) : i(0), k(0), p(nullptr),kai(0) {
    memset(&servAddr, 0, sizeof(sockaddr_in));
    memset(&servAddr_1, 0, sizeof(sockaddr_in));
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    inet_pton(AF_INET, s, &servAddr.sin_addr.s_addr);
    sendto(sock, nullptr, 0, 0, (struct sockaddr*)&servAddr, sizeof(sockaddr_in));
}
dataudp::dataudp(int port) : i(0), k(0), p(nullptr) {
    memset(&servAddr, 0, sizeof(sockaddr_in));
    memset(&servAddr_1, 0, sizeof(sockaddr_in));
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
    recvfrom(sock, nullptr, 0, 0, (struct sockaddr*)&servAddr_1, &length);
}
void dataudp::data_send(char* p, int n) {
    std::thread kk(&dataudp::data_recv1, this, p, n);
    kk.detach();
    //std::thread kk1(&dataudp::data_recv2, this, p, n);
   // kk1.detach();
    /*i = n / 1024;
    for (k = 0; k <= i; k++) {
        nd.number = k;
        memcpy(nd.data, p, (k == i) ? n % 1024 : 1024);
        sendto(sock, (char*)&nd, ((k == i) ? n % 1024 : 1024)+ sizeof(int), 0, (struct sockaddr*)&servAddr_1, sizeof(sockaddr_in));
        p += A_data_size;
    }/**/
}
void dataudp::data_recv(char* p, int n) {
    i = 0;
    //std::thread kk(&dataudp::data_recv1, this, p, n);
    //for (k = 0; k <= i; k++) {
    //while (i <= n) {
        this->p = p;
        k = recvfrom(sock, (char*)&nd, sizeof(nd), 0, nullptr, nullptr);
        this->p += nd.number * 1024;
        memcpy(this->p, nd.data, k - sizeof(int));
        //std::cout << "接收" << i << std::endl;
        i += k - sizeof(int);
    //}
    //kk.join();
}
void dataudp::data_recv1(char* p, int n) {
    char* p1 = p;
    int k1 = 0, i1=0;
    while (1) 
    {
        p1 = p;
        k1 = recvfrom(sock, (char*)&nd1, sizeof(nd1), 0, nullptr, nullptr);
        p1 += nd1.number * 1024;
        memcpy(p1, nd1.data, k1 - sizeof(int));
        //std::cout << "接收kkk" << i1 << std::endl;
        //i1 += k1 - sizeof(int);
    }
}
void dataudp::data_recv2(char* p, int n) {
    char* p2 = p;
    int k2 = 0, i2 = 0;
    while (1)
    {
        p2 = p;
        k2 = recvfrom(sock, (char*)&nd2, sizeof(nd2), 0, nullptr, nullptr);
        p2 += nd2.number * 1024;
        memcpy(p2, nd2.data, k2 - sizeof(int));
        //std::cout << "接收kkk" << i1 << std::endl;
        //i1 += k1 - sizeof(int);
    }
}
void dataudp::drecv(char* p, int n) {
     recvfrom(sock, p, n, 0, nullptr, nullptr);
}
dataudp::~dataudp() {
    closesocket(sock);
    WSACleanup();
}
#endif
#ifndef _DATA_S_
#define _DATA_S_
#include<windows.h>
#include <fstream>
#define _AgE_ HWND DeskWnd, int x, int y, int Width, int Height
class DATABMP {
private:
protected:
    HDC memDC;//兼容DC
    HDC DeskDC;//窗口DC
    HBITMAP DeskBmp;//兼容位图
    HWND DeskWnd;
    int x, y, Width, Height;
public:
    BITMAPINFOHEADER bih;//位图信息头
    BITMAPFILEHEADER bfh;
    char* bmData;
    DATABMP(_AgE_);
    DATABMP(_AgE_, BITMAPINFOHEADER bih);
    ~DATABMP();
    void getbmpdata();
    void setshow();
    void savedata(const char* s);
};
DATABMP::DATABMP(_AgE_) :x(x), y(y), Width(Width), Height(Height), DeskWnd(DeskWnd) {
    DeskDC = GetDC(DeskWnd);//窗口DC
    memDC = CreateCompatibleDC(DeskDC);//兼容DC
    DeskBmp = CreateCompatibleBitmap(DeskDC, Width, Height);//窗口兼容位图 宽 高
    SelectObject(memDC, DeskBmp);//把兼容位图选入兼容DC中
    bmData = new char[Width * Height * 3];
    bih.biSize = 40;
    bih.biWidth = Width;//960
    bih.biHeight = Height;//540
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = Width * Height * 3;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;
    bfh.bfType = 0x4d42;
    bfh.bfSize = bih.biSizeImage * 3 + 54;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = 54;
}
DATABMP::DATABMP(_AgE_, BITMAPINFOHEADER bih) :x(x), y(y), Width(Width), Height(Height), DeskWnd(DeskWnd), bih(bih) {
    DeskDC = GetDC(DeskWnd);//窗口DC
    memDC = CreateCompatibleDC(DeskDC);//兼容DC
    DeskBmp = CreateCompatibleBitmap(DeskDC, bih.biWidth, bih.biHeight);//窗口兼容位图 宽 高
    SelectObject(memDC, DeskBmp);//把兼容位图选入兼容DC中
    bmData = new char[bih.biSizeImage];
    bfh.bfType = 0x4d42;
    bfh.bfSize = bih.biSizeImage * 3 + 54;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = 54;
}
void DATABMP::getbmpdata()
{
    StretchBlt(memDC, 0, 0, Width, Height, DeskDC, x, y, Width, Height, SRCCOPY);
    GetDIBits(memDC, DeskBmp, 0, Height, bmData, (BITMAPINFO*)&bih, DIB_RGB_COLORS);//获取位图数据部分
}
void DATABMP::setshow() {
    SetDIBits(memDC, DeskBmp, 0, bih.biHeight, bmData, (BITMAPINFO*)&bih, DIB_RGB_COLORS);
    StretchBlt(DeskDC, x, y, Width, Height, memDC, 0, 0, bih.biWidth, bih.biHeight, SRCCOPY);
}
void DATABMP::savedata(const char* s) {
    std::ofstream outfile(s, std::ios::binary);
    outfile.write((char*)&bfh, sizeof(bfh));
    outfile.write((char*)&bih, sizeof(bih));
    outfile.write(bmData, bih.biSizeImage);
    outfile.close();
}
DATABMP::~DATABMP() {
    delete[] bmData;
    ReleaseDC(DeskWnd, DeskDC);
}
#endif