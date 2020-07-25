
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <cstdio>
#include <cstdlib>
#pragma warning(disable:4996) 
#pragma comment (lib, "ws2_32.lib")

int main() {
     WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR)
        printf("Initialization error.\n");

    SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mainSocket == INVALID_SOCKET) {
        printf("Error creating socket: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    sockaddr_in service;
    memset(&service, 0, sizeof(service));
    service.sin_family = AF_INET;
    //service.sin_addr.s_addr = inet_addr("127.0.0.1");
    InetPton(AF_INET, L"127.0.0.1", &service.sin_addr.s_addr);
    service.sin_port = htons(27015);

    if (bind(mainSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        printf("bind() failed.\n");
        closesocket(mainSocket);
        return 1;
    }

    if (listen(mainSocket, 1) == SOCKET_ERROR)
        printf("Error listening on socket.\n");

}