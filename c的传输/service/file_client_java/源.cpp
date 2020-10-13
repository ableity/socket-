#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//既可以和java通信，又可以和c通信
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


int main(int argc, char* argv[])
{
	//初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//创建套接字  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	//端口号18895
	sin.sin_port = htons(18895);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	/*循环接收数据  
	* 设计思路
	* 首先传输文件名（如lilei.jpg），然后传输文件本身
	* 标志位nameok判断本次传输是传输的文件名还是文件本身
	*/

	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	int nameok = 0;
	string filename;
	while (true)
	{
		if(nameok==0)
		printf("等待连接...\n");
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
		{	//while循环来阶段文件名尾部的异常字符（如"lilei.jpg"会传输为"lilei.jpg      "但经验证后面的不是空格，用去除空格的方法无法对字符串处理）
			//此处只判断了小写字母，没有判断其它情况，因为一般文件后缀都是小写字母，但可能留下未知的bug
			while (filename[filename.length() - 1] >= 'z' || filename[filename.length() - 1] <= 'a')
				filename.pop_back();
			RecvFile(filename);
			nameok = 0;
		}


		closesocket(m_Client);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}

//传输字符串
string RecvStr()
{
	cout << "开始传输文件名："<<endl;
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
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	int readLen = 0;

	//文件的存储路径（文件名前的部分，如"D:\\data\\in\\lilei.jpg"为"D:\\data\\in\\"）
	string desFileName,temp = "D:\\data\\in\\";
	desFileName=temp+filename;

	cout << "开始传输文件" << desFileName << endl;
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




