#include "workthread.h"
#include <qdebug.h>
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <winsock2.h>
#include<thread>
#include<qlabel>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

workthread::workthread(int port_temp, string path_temp, QLabel *label)
{
	port = port_temp;
	path = path_temp;
	led = label;
	//workthread::port = port_temp;
	//workthread::path = path_temp;
}

void workthread::RecvFile() {
	led->setText("begin receive");
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	int readLen = 0;
	string desFileName = path;
	ofstream desFile;
	desFile.open(desFileName.c_str(), ios::binary);
	if (!desFile)
	{
		return;
	}
	do
	{
		readLen = recv(m_Client, buffer, bufferSize, 0);
		if (readLen == 0)
		{
			break;
		}
		else
		{
			desFile.write(buffer, readLen);
		}
	} while (true);
	desFile.close();
	led->setText("receive end");
}

void workthread::RecvStr()
{
		cout << "start recv str!" << endl;
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
			memcpy(outbuf, buf, len);
			outbuf[len] = 0;
			cout << "recv data:" << outbuf << endl;
			//delete outbuf;
		}
}




void workthread::run()
{
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
	sin.sin_port = htons(workthread::port);
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

	//循环接收数据  
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while (true)
	{
		printf("等待连接...\n");
		m_Client = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		if (m_Client == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		//printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
		//SendFile();
		RecvFile();
		closesocket(m_Client);
	}
	closesocket(slisten);
	WSACleanup();
}