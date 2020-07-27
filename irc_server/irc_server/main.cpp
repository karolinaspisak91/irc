//#include <winsock2.h>
#include <Ws2tcpip.h>

#include <iostream>
#include <cstdlib>
#pragma warning(disable:4996) 
#pragma comment (lib, "ws2_32.lib")
#define DEFAULT_BUFLEN 512

using namespace std;
int main() {
    WSADATA wsaData;
    cout << "debug1" << endl;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR)
        cout << "Initialization error.";

    SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mainSocket == INVALID_SOCKET) {
        cout << "Error creating socket: %ld\n", WSAGetLastError();
        WSACleanup();
        system("pause");
        return 1;
    }

    sockaddr_in service;
    memset(&service, 0, sizeof(service));
    service.sin_family = AF_INET;
    InetPton(AF_INET, L"127.0.0.1", &service.sin_addr.s_addr);
    service.sin_port = htons(27015);
    cout << "debug2" << endl;
    if (bind(mainSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed.\n";
        closesocket(mainSocket);
        system("pause");
        return 1;
    }

    if (listen(mainSocket, 1) == SOCKET_ERROR)
        cout << "Error listening on socket.\n";
    cout << "debug3" << endl;
    SOCKET ClientSocket = INVALID_SOCKET;
    cout << "debug6" << endl;
    ClientSocket = accept(mainSocket, NULL, NULL);
    cout << "debug5" << endl;
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(mainSocket);
        WSACleanup();
        system("pause");
        return 1;
    }
    cout << "debug4" << endl;
    // No longer need server socket
    closesocket(mainSocket);
    int iResult;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    cout << "debug" << endl;
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                system("pause");
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            system("pause");
            return 1;
        }

    } while (iResult > 0);
    

    system("pause");
    return 0;

}