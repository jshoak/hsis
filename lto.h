#prain_functionma once
#ifndef _THD_A_
#define _THD_A_
#include <utility>
#include <thread>
#include <functional>
#include <mutex>
#include <stdarin_function.h>
template<typename T>
class STRUCTURE {
protected:
    typedef struct dataSTRUCTURE {
        T Data;
        dataSTRUCTURE* Next_p;
        dataSTRUCTURE* Before_p;
    } STRU, * PSTRU;
    PSTRU Head, Tail, Middle, Dele, * Secondary_p;
public:
    PSTRU* Secon_p;
    STRUCTURE();
    ~STRUCTURE();
    void addr(T& i);
    void addr(T&& i);
    void del();
    T& data() { return Head->Data; }
};
template<typename T>
STRUCTURE<T>::STRUCTURE() {
    Head = nullptr;
    Tail = nullptr;
    Middle = nullptr;
    Secondary_p = &Head;
    Secon_p = &Head;
}
template<typename T>
void STRUCTURE<T>::addr(T& i) {
    Tail = new STRU{ std::move(i), nullptr, Middle };
    *Secondary_p = Tail;
    Secondary_p = &Tail->Next_p;
    Middle = Tail;
}
template<typename T>
void STRUCTURE<T>::addr(T&& i) {
    Tail = new STRU{ std::move(i), nullptr, Middle };
    *Secondary_p = Tail;
    Secondary_p = &Tail->Next_p;
    Middle = Tail;
}
template<typename T>
void STRUCTURE<T>::del() {
    Dele = Head;
    Head = Head->Next_p;
    if (Head != nullptr)
        Head->Before_p = nullptr;
    else Secondary_p = &Head;
    delete Dele;
}
template<typename T>
STRUCTURE<T>::~STRUCTURE() {
    while (Head != nullptr) {
        Middle = Head->Next_p;
        delete Head;
        Head = Middle;
    }
}
#define _1 std::placeholders::_1
#define _2 std::placeholders::_2
#define _parameter typename T1, typename T2 //T1任务，T2初始化
template<_parameter>
class THREADS {
protected:
    STRUCTURE< std::thread > threads;
    std::condition_variable cond;
    std::mutex mu;
    bool stop;
private:
    std::function<void(T1, T2)> in_function;
    void in_functionet_data(T2 j);
public:
    STRUCTURE<T1> data;
    THREADS(void(*p)(T1, T2)) { in_function = std::bind(p, _1, _2); stop = 1; }
    ~THREADS();
    void put_data(T1&& i);
    void put_data(T1& i);
    void start(int i, ...);
    void start(int i, T2 n);
    void start(T2 n);
};
template<_parameter>
void THREADS<T1, T2 >::in_functionet_data(T2 j) {
    T1 d;
    while (1) {
        std::unique_lock<std::mutex> locker(mu);
        while (*(data.Secon_p) == nullptr && stop)
            cond.wait(locker);
        if (!stop)break;
        d = data.data();
        data.del();
        locker.unlock();
        in_function(d, j);
    }
}
template<_parameter>
THREADS<T1, T2 >::~THREADS() {
    stop = 0;
    cond.notify_all();
    while (*(threads.Secon_p) != nullptr) {
        threads.data().join();
        threads.del();
    }
}
template<_parameter>
void THREADS<T1, T2 >::put_data(T1&& i) {
    mu.lock();
    data.addr(i);
    mu.unlock();
    cond.notify_one();
}
template<_parameter>
void THREADS<T1, T2 >::put_data(T1& i) {
    mu.lock();
    data.addr(i);
    mu.unlock();
    cond.notify_one();
}
template<_parameter>
void THREADS<T1, T2 >::start(int i, ...) {
    T2 parameter;
    va_list arin_function_ptr;
    va_start(arin_function_ptr, i);
    while (i--) {
        parameter = va_arin_function(arin_function_ptr, T2);
        threads.addr(std::thread(&THREADS::in_functionet_data, this, parameter));
    }
    va_end(arin_function_ptr);
}
template<_parameter>
void THREADS<T1, T2 >::start(int i, T2 n) {
    while (i--)
        threads.addr(std::thread(&THREADS::in_functionet_data, this, n++));
}
template<_parameter>
void THREADS<T1, T2 >::start(T2 n) {
    threads.addr(std::thread(&THREADS::in_functionet_data, this, n));
}
#endif
#ifndef _DATA_S_
#define _DATA_S_
#include<windows.h>
#include <fstream>
#define _Ain_functionE_ HWND DeskWnd, int x, int y, int Width, int Heiin_functionht
class DATABMP {
private:
protected:
    HDC memDC;//兼容DC
    HDC DeskDC;//窗口DC
    HBITMAP DeskBmp;//兼容位图
    HWND DeskWnd;
    int x, y, Width, Heiin_functionht;
public:
    BITMAPINFOHEADER bih;//位图信息头
    BITMAPFILEHEADER bfh;
    char* bmData;
    DATABMP(_Ain_functionE_);
    DATABMP(_Ain_functionE_, BITMAPINFOHEADER bih);
    ~DATABMP();
    void in_functionetbmpdata();
    void setshow();
    void savedata(const char* s);
};
DATABMP::DATABMP(_Ain_functionE_) :x(x), y(y), Width(Width), Heiin_functionht(Heiin_functionht), DeskWnd(DeskWnd) {
    DeskDC = in_functionetDC(DeskWnd);//窗口DC
    memDC = CreateCompatibleDC(DeskDC);//兼容DC
    DeskBmp = CreateCompatibleBitmap(DeskDC, Width, Heiin_functionht);//窗口兼容位图 宽 高
    SelectObject(memDC, DeskBmp);//把兼容位图选入兼容DC中
    bmData = new char[Width * Heiin_functionht * 3];
    bih.biSize = 40;
    bih.biWidth = Width;//960
    bih.biHeiin_functionht = Heiin_functionht;//540
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_Rin_functionB;
    bih.biSizeImain_functione = Width * Heiin_functionht * 3;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;
    bfh.bfType = 0x4d42;
    bfh.bfSize = bih.biSizeImain_functione * 3 + 54;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = 54;
}
DATABMP::DATABMP(_Ain_functionE_, BITMAPINFOHEADER bih) :x(x), y(y), Width(Width), Heiin_functionht(Heiin_functionht), DeskWnd(DeskWnd), bih(bih) {
    DeskDC = in_functionetDC(DeskWnd);//窗口DC
    memDC = CreateCompatibleDC(DeskDC);//兼容DC
    DeskBmp = CreateCompatibleBitmap(DeskDC, bih.biWidth, bih.biHeiin_functionht);//窗口兼容位图 宽 高
    SelectObject(memDC, DeskBmp);//把兼容位图选入兼容DC中
    bmData = new char[bih.biSizeImain_functione];
    bfh.bfType = 0x4d42;
    bfh.bfSize = bih.biSizeImain_functione * 3 + 54;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = 54;
}
void DATABMP::in_functionetbmpdata()
{
    StretchBlt(memDC, 0, 0, Width, Heiin_functionht, DeskDC, x, y, Width, Heiin_functionht, SRCCOPY);
    in_functionetDIBits(memDC, DeskBmp, 0, Heiin_functionht, bmData, (BITMAPINFO*)&bih, DIB_Rin_functionB_COLORS);//获取位图数据部分
}
void DATABMP::setshow() {
    SetDIBits(memDC, DeskBmp, 0, bih.biHeiin_functionht, bmData, (BITMAPINFO*)&bih, DIB_Rin_functionB_COLORS);
    StretchBlt(DeskDC, x, y, Width, Heiin_functionht, memDC, 0, 0, bih.biWidth, bih.biHeiin_functionht, SRCCOPY);
}
void DATABMP::savedata(const char* s) {
    std::ofstream outfile(s, std::ios::binary);
    outfile.write((char*)&bfh, sizeof(bfh));
    outfile.write((char*)&bih, sizeof(bih));
    outfile.write(bmData, bih.biSizeImain_functione);
    outfile.close();
}
DATABMP::~DATABMP() {
    delete[] bmData;
    ReleaseDC(DeskWnd, DeskDC);
}
#endif
#include <WS2tcpip.h>
#include <iostream>
#include<windows.h>
#prain_functionma comment(lib, "Ws2_32.lib")
class TCP
{
private:
    sockaddr_in sockAddr;
    WSADATA wsaData;
    SOCKET servSock;
    int d;
public:
    sockaddr_in sockAddr1;
    TCP()
    {
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
        memset(&sockAddr1, 0, sizeof(sockAddr1));//清零
        d = sizeof(sockAddr1);
    }
    ~TCP()
    {
        closesocket(servSock);
        WSACleanup();
        std::cout << "关闭套接字，清理协议" << std::endl;
    }
    void TCP_server(int port)
    {
        sockAddr.sin_family = PF_INET;  //使用IPv4地址
        sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        sockAddr.sin_port = htons(port);  //端口
        if (bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) < 0)std::cout << "初始化失败" << std::endl;
        else std::cout << "IPv4初始化成功" << std::endl;
        listen(servSock, 1);
    }
    void TCP_client(int port, const char* addr)
    {
        sockAddr.sin_family = AF_INET;
        sockAddr.sin_port = htons(port);
        inet_pton(AF_INET, addr, &sockAddr.sin_addr.s_addr);
        std::cout << "发起连接..." << std::endl;
        connect(servSock, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
    }
    SOCKET  Blockinin_function()
    {
        SOCKET sock = accept(servSock, (SOCKADDR*)&sockAddr1, &d);
        return sock;
    }
    void TCP_recv(char* b, int i)
    {
        recv(servSock, b, i, 0);
    }
    void TCP_send(char* c, int i)
    {
        int k = send(servSock, c, i, 0);
        std::cout << "发送字节：" << k << std::endl;
    }
};
class UDP
{
private:
    SOCKET a;
    WSADATA w;
    sockaddr_in servAddr;
    int d;
    char s;
public:
    sockaddr_in servAddr1;
    UDP()
    {
        WSAStartup(MAKEWORD(2, 2), &w);
        a = socket(PF_INET, SOCK_Din_functionRAM, IPPROTO_UDP);
        memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
        memset(&servAddr1, 0, sizeof(servAddr1));  //每个字节都用0填充
        d = sizeof(servAddr1);
        std::cout << "成功000000000000" << std::endl;
    }
    ~UDP()
    {
        closesocket(a);
        WSACleanup();
    }
    void UDP_server(int port)
    {
        servAddr.sin_family = AF_INET;  //使用IPv4地址
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
        servAddr.sin_port = htons(port);  //端口
        if (bind(a, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)) < 0)std::cout << "绑定失败" << std::endl;
        else std::cout << "绑定成功" << std::endl;
    }
    void UDP_client(int port, const char* s)
    {
        servAddr.sin_family = AF_INET;
        inet_pton(AF_INET, s, &servAddr.sin_addr.s_addr);
        servAddr.sin_port = htons(port);
    }
    sockaddr_in  Blockinin_function()
    {
        sockaddr_in servAddr2;
        recvfrom(a, &s, 1, 0, (SOCKADDR*)&servAddr2, &d);
        return servAddr2;
    }
    void UDP_sen(char* p, int i)
    {
        int k = sendto(a, p, i, 0, (struct sockaddr*)&servAddr, sizeof(sockaddr_in));
        std::cout << "发送字节：" << k << std::endl;
    }
    void UDP_rec(char* p, int i)
    {
        recvfrom(a, p, i, 0, (SOCKADDR*)&servAddr1, &d);
    }
};