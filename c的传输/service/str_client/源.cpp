#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#include<iostream>
using namespace std;

#pragma comment(lib,"ws2_32")
//客户端
int main()
{
	WSADATA wsaDate = {};
	WSAStartup(MAKEWORD(2, 2), &wsaDate);
	SOCKET sockClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in addrServer = {};
	addrServer.sin_family = PF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrServer.sin_port = htons(10000);

	if (connect(sockClient, (SOCKADDR*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
	{
		cout << "connect error" << endl;
	}
	//connect(sockClient, (SOCKADDR*)&addrServer, sizeof(addrServer));
	string str = "李蕾";
	/*while (1)
	{*/
	int len = send(sockClient, str.c_str(), str.length(), 0);
	if (len < str.length())
	{
		cout << "data send uncompleted" << endl;
		str = str.substr(len + 1, str.length());
		len = send(sockClient, str.c_str(), str.length(), 0);
		cout << "send data uncomplete,send remaining data :" << str.c_str() << " ,length = " << str.length() << endl;
	}
	Sleep(1);

	//}
	//接受服务器消息
	char buf[1024];
	len = recv(sockClient, buf, 1024, NULL);
	char* outbuf = new char[len + 1];
	memcpy(outbuf, buf, len);
	outbuf[len] = 0;
	cout << "服务端：" << outbuf << endl;
	closesocket(sockClient);
	WSACleanup();
	while (true)
	{

	}
	return 0;

}
