#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32")

//�����
int main()
{
	//WSADATA�����洢��WSAStartup�������ú󷵻ص�Windows Sockets����
	WSADATA wsaDate = {};
	WSAStartup(MAKEWORD(2, 2), &wsaDate);
	/*
	int socket(int domain, int type, int protocol);
	domain����Э�����ֳ�ΪЭ���壨family�������õ�Э�����У�AF_INET��AF_INET6��AF_LOCAL�����AF_UNIX��Unix��socket����AF_ROUTE�ȵȡ�Э���������socket�ĵ�ַ���ͣ���ͨ���б�����ö�Ӧ�ĵ�ַ����AF_INET������Ҫ��ipv4��ַ��32λ�ģ���˿ںţ�16λ�ģ�����ϡ�AF_UNIX������Ҫ��һ������·������Ϊ��ַ��
	type��ָ��socket���͡����õ�socket�����У�SOCK_STREAM��SOCK_DGRAM��SOCK_RAW��SOCK_PACKET��SOCK_SEQPACKET�ȵȣ�socket����������Щ������
	protocol������˼�⣬����ָ��Э�顣���õ�Э���У�IPPROTO_TCP��IPPTOTO_UDP��IPPROTO_SCTP��IPPROTO_TIPC�ȣ����Ƿֱ��ӦTCP����Э�顢UDP����Э�顢STCP����Э�顢TIPC����Э�飨���Э���ҽ��ᵥ����ƪ���ۣ�����
	*/
	SOCKET sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//SOCKET sockServer = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in addrServer = {};
	addrServer.sin_family = PF_INET;
	//addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//�󶨱�����ַ
	addrServer.sin_port = htons(10000);
	//�󶨷������˿ںź�IP��ַ
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	//sockfd����socket�����֣�����ͨ��socket()���������ˣ�Ψһ��ʶһ��socket��bind()�������ǽ�����������ְ�һ�����֡�
	//addr��һ��const struct sockaddr *ָ�룬ָ��Ҫ�󶨸�sockfd��Э���ַ�������ַ�ṹ���ݵ�ַ����socketʱ�ĵ�ַЭ����Ĳ�ͬ����ͬ
	//addrlen����Ӧ���ǵ�ַ�ĳ���
	int bind_server = bind(sockServer, (SOCKADDR*)&addrServer, sizeof(addrServer));
	if (bind_server != 0)
	{
		cout << "bind error" << endl;
	}
	listen(sockServer, 2);
	//�ͻ���
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
		printf("�ͻ����Ѿ�����\n");

		//1.��ͻ��˷�����Ϣ
		//string str = "hello client";
		//send(sockClient, str.c_str(), str.length(), NULL);
		/*while (1)
		{*/
		//2.���ܿͻ�����Ϣ
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
