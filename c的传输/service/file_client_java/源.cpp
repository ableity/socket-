#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//�ȿ��Ժ�javaͨ�ţ��ֿ��Ժ�cͨ��
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

SOCKET m_Client;
void SendFile();
void RecvFile(string filename);
string RecvStr();
std::string& trim(std::string& s)
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

int main(int argc, char* argv[])
{
	//��ʼ��WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//�����׽���  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//��IP�Ͷ˿�  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(18895);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//��ʼ����  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//ѭ����������  
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	int nameok = 0;
	string filename;
	while (true)
	{
		printf("�ȴ�����...\n");
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
			filename=RecvStr();
			nameok = 1;
		}
		else if(nameok == 1)
		{
			RecvFile(filename);
			nameok = 0;
		}


		closesocket(m_Client);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}

string RecvStr()
{
	cout << "start recv str!" << endl;
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

void RecvFile(string filename) {
	cout << "start recv!" << endl;
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	int readLen = 0;
	string desFileName = "D:\\data\\in\\"+filename;
	trim(desFileName);
	cout << "filepath:" << desFileName <<"end"<< endl;
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




