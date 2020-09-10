#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <winsock2.h>


#pragma comment(lib, "ws2_32.lib")

using namespace std;

//为适应java的修改版

SOCKET m_Client;

void RecvFile();
void SendFile();

int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	//while(true){
	m_Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Client == INVALID_SOCKET)
	{
		printf("invalid socket!");
		return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(m_Client, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{  //连接失败 
		printf("connect error !");
		closesocket(m_Client);
		return 0;
	}
	//RecvFile();
	SendFile();
	closesocket(m_Client);
	//}


	WSACleanup();
	return 0;

}

void RecvFile() {
	cout << "start recv!" << endl;
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	int readLen = 0;
	string desFileName = "D:\\data\\in\\xjpic.jpg";
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
}

void SendFile() {
	int haveSend = 0;
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	int readLen = 0;
	string srcFileName = "D:\\data\\out\\xjpic.jpg";;
	ifstream srcFile;
	srcFile.open(srcFileName.c_str(), ios::binary);
	if (!srcFile) {
		return;
	}
	while (!srcFile.eof()) {
		srcFile.read(buffer, bufferSize);
		readLen = srcFile.gcount();
		send(m_Client, buffer, readLen, 0);
		haveSend += readLen;
	}
	srcFile.close();
	cout << "send: " << haveSend << "B" << endl;
}