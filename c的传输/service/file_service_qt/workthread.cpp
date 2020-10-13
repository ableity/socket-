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

void workthread::RecvFile(string filename) {
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	int readLen = 0;

	//�ļ��Ĵ洢·�����ļ���ǰ�Ĳ��֣���"D:\\data\\in\\lilei.jpg"Ϊ"D:\\data\\in\\"��
	string desFileName;
	desFileName = path + filename;

	cout << "��ʼ�����ļ�" << desFileName << endl;
	led->setText("begin receive");
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
	led->setText("end");
}

string workthread::RecvStr()
{
	led->setText("��ʼ�����ļ���");
	cout << "��ʼ�����ļ�����" << endl;
	char buf[1024];
	int len = recv(m_Client, buf, 1024, 0);
	string out;
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
		out = outbuf;

		//delete outbuf;
	}

	return out;
}


void workthread::run()
{
	//��ʼ��WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
	}

	//�����׽���  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		//printf("socket error !");
	}

	//��IP�Ͷ˿�  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(workthread::port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		//printf("bind error !");
	}

	//��ʼ����  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		//printf("listen error !");
	}

	//ѭ����������  
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	int nameok = 0;
	string filename;
	int is1 = 1;
	while (true)
	{
		if (nameok == 0)
		{
			led->setText("waitting......");
			if (is1 == 0)
			{
				led->setText(QString::fromStdString(filename) +" is done \n waitting......");
			}
		}
		m_Client = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		if (m_Client == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		//SendFile();
		//RecvFile();
		if (nameok == 0)
		{
			filename = RecvStr();
			nameok = 1;
		}
		else if (nameok == 1)
		{	//whileѭ�����׶��ļ���β�����쳣�ַ�����"lilei.jpg"�ᴫ��Ϊ"lilei.jpg      "������֤����Ĳ��ǿո���ȥ���ո�ķ����޷����ַ�������
			//�˴�ֻ�ж���Сд��ĸ��û���ж������������Ϊһ���ļ���׺����Сд��ĸ������������δ֪��bug
			while (filename[filename.length() - 1] >= 'z' || filename[filename.length() - 1] <= 'a')
				filename.pop_back();
			RecvFile(filename);
			nameok = 0;
		}
		is1 = 0;
		closesocket(m_Client);
	}
	closesocket(slisten);
	WSACleanup();
}