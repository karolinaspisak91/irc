#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")

using namespace std;
int main() {
	string ipAddress = "127.0.0.1";
	int port = 27015;
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cout << "Can't start Winsock, Err" << wsResult << endl;
		return 1;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cout << "Can't create a socket! Quitting" << endl;
		return 1;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cout << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		system("pause");
		return 1;
	}
	else {
		cout << "Not failed" << endl;
	}
	system("pause");
	return 0;
}