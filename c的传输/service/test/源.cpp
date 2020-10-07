#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#include<iostream>
#include<string>
using namespace std;
#pragma comment(lib,"ws2_32")

//服务端
int main()
{
	SOCKET m_Client;
	////WSADATA用来存储被WSAStartup函数调用后返回的Windows Sockets数据
	//WORD sockVersion = MAKEWORD(2, 2);
	//WSADATA wsaData;
	//if (WSAStartup(sockVersion, &wsaData) != 0)
	//{
	//}


	//SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//sockaddr_in addrServer;
	//addrServer.sin_family = AF_INET;
	//addrServer.sin_port = htons(7777);

	//if（bind(sockServer, (LPSOCKADDR*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
	//{
	//	cout << "bind error" << endl;
	//}
	//listen(sockServer, 5);
	////客户端
		//初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
	}

	//创建套接字  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		//printf("socket error !");
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(7777);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		//printf("bind error !");
	}

	//开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		//printf("listen error !");
	}


	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);

	int nSzie = sizeof(remoteAddr);
	m_Client = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
	if (m_Client == INVALID_SOCKET)
	{
		cout << "accept error" << endl;
	}
	printf("客户端已经连接\n");

	//1.向客户端发送信息
	//string str = "hello client";
	//send(sockClient, str.c_str(), str.length(), NULL);
	/*while (1)
	{*/
	//2.接受客户端信息
	char buf[1024];
	int len = recv(m_Client, buf, 1024, 0);
	if (len == 0)
	{
		cout << "connection has closed" << endl;
		//break;
	}
	else if (len == SOCKET_ERROR)
	{
		cout << "recv error" << WSAGetLastError() << endl;
		//break;
	}
	else
	{
		char* outbuf = new char[len];
		cout << len << endl;
		memcpy(outbuf, buf, len);
		
		cout << "recv data:" << outbuf << endl;
		delete outbuf;
	}
	//}
	closesocket(m_Client);
	closesocket(slisten);
	WSACleanup();
	while (true)
	{

	}
	return 0;
}
