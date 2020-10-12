#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32")

//服务端
int main()
{
	//WSADATA用来存储被WSAStartup函数调用后返回的Windows Sockets数据
	WSADATA wsaDate = {};
	WSAStartup(MAKEWORD(2, 2), &wsaDate);
	/*
	int socket(int domain, int type, int protocol);
	domain：即协议域，又称为协议族（family）。常用的协议族有，AF_INET、AF_INET6、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等等。协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合、AF_UNIX决定了要用一个绝对路径名作为地址。
	type：指定socket类型。常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等（socket的类型有哪些？）。
	protocol：故名思意，就是指定协议。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议（这个协议我将会单独开篇讨论！）。
	*/
	SOCKET sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//SOCKET sockServer = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in addrServer = {};
	addrServer.sin_family = PF_INET;
	//addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//绑定本机地址
	addrServer.sin_port = htons(10000);
	//绑定服务器端口号和IP地址
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	//sockfd：即socket描述字，它是通过socket()函数创建了，唯一标识一个socket。bind()函数就是将给这个描述字绑定一个名字。
	//addr：一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。这个地址结构根据地址创建socket时的地址协议族的不同而不同
	//addrlen：对应的是地址的长度
	int bind_server = bind(sockServer, (SOCKADDR*)&addrServer, sizeof(addrServer));
	if (bind_server != 0)
	{
		cout << "bind error" << endl;
	}
	listen(sockServer, 2);
	//客户端
	SOCKET sockClient = {};
	SOCKADDR addrClient = {};
	int nSzie = sizeof(addrClient);

	while (true)
	{

		sockClient = accept(sockServer, &addrClient, &nSzie);
		if (sockClient == INVALID_SOCKET)
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
		int len = recv(sockClient, buf, 1024, 0);
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
			memcpy(outbuf, buf, len);
			outbuf[len] = 0;
			cout << "recv data:" << outbuf << endl;
			//delete outbuf;
		}

	}

	
	//}
	closesocket(sockServer);
	closesocket(sockClient);
	WSACleanup();
	while (true)
	{

	}
	return 0;
}
