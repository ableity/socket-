// SocketTest.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"   
#include <WINSOCK2.H>  
#include<iostream>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
struct   UserInfo   {
	char   UserName[20];
	int   UserId;
};
struct   Employee   {
	UserInfo   user;
	float   salary;
};
int main(int argc, char* argv[]) {

	WSADATA   wsaData;
	char   buf[1024];
	int   nBytes = 1024, recvbytes;
	SOCKET   Listening;
	SOCKET   NewConnection;
	SOCKADDR_IN   ServerAddr;
	SOCKADDR_IN   ClientAddr;
	int   ClientAddrLen = sizeof(ClientAddr);
	int   Port = 5050;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	Listening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(Port);

	bind(Listening, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	listen(Listening, 5);
	printf("Wating   accpet....\n");


	while (true) {
		NewConnection = accept(Listening, (SOCKADDR   *)&ClientAddr, &ClientAddrLen);
		printf("Wating   recv.....\n");
		if ((recvbytes = recv(NewConnection, buf, nBytes, 0)) == SOCKET_ERROR)
		{
			printf("\nErrorcode=%d,   Recv   from   client\n", WSAGetLastError());
			return   0;
		}
		Employee   *data = new   Employee;
		data = (Employee   *)&buf;

		printf("Userid:   %d   Username:   %s  Salary:  %f", data->user.UserId, data->user.UserName, data->salary);
		data->user.UserId = 007;
		strcpy(data->user.UserName, "Testlilei");
		data->salary = 800;

		send(NewConnection, buf, recvbytes, 0);

	}
	//while (true) {
	//	NewConnection = accept(Listening, (SOCKADDR*)&ClientAddr, &ClientAddrLen);
	//	printf("Wating   recv.....\n");
	//	if ((recvbytes = recv(NewConnection, buf, nBytes, 0)) == SOCKET_ERROR)
	//	{
	//		printf("\nErrorcode=%d,   Recv   from   client\n", WSAGetLastError());
	//		return   0;
	//	}

	//	char* s = new char[recvbytes + 1];
	//	memcpy(s, buf, recvbytes);
	//	cout << s << endl;

	//}
	return   0;

}