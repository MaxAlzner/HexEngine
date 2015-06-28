
#include <stdio.h>
#include <conio.h>
#include <time.h>

#include "..\include\MALib_sock.h"

struct TEST_STRUCT
{
	TEST_STRUCT()
	{
		memset(this, 0, sizeof(TEST_STRUCT));
	}
	int a;
	double g;
	int b;
	char c;
	float h;
	float j;
};

int send(char* buffer, uint bytes)
{
	TEST_STRUCT test1;
	test1.a = 81;
	test1.g = 18.02;
	test1.b = 2;
	test1.c = 57;
	test1.h = 23.008f;
	test1.j = 4.158f;
	*((TEST_STRUCT*)buffer) = test1;
	printf("SENT : %d %f %d %d %f %f\n", test1.a, test1.g, test1.b, test1.c, test1.h, test1.j);
	//int error = MALib::SOCK_CheckError();
	//if (error != 0) printf("SEND ERROR : %d\n", error);
	return 1000;
}
int receive(char* buffer, uint bytes)
{
	TEST_STRUCT test2;
	test2 = *((TEST_STRUCT*)buffer);
	printf("RECIEVED : %d %f %d %d %f %f\n", test2.a, test2.g, test2.b, test2.c, test2.h, test2.j);
	//int error = MALib::SOCK_CheckError();
	//if (error != 0) printf("RECIEVE ERROR : %d\n", error);
	return 1000;
}

int main()
{
	MALib::SOCK_Initialize(true);
	
	static char* ip = MALib::SOCK_GetMyIP();
	printf("HOST IP : %s\n", ip);
	printf("PORT NUM : %d\n", 20533);

	if (MALib::SOCK_Connect(20533, ip, send, receive))
	{
		printf("SERVER SETUP SUCCESSFUL\n");
	}
	else
	{
		printf("SERVER SETUP UNSUCCESSFUL\n");
		printf("CONNECTION ERROR : %d\n", MALib::SOCK_CheckError());
	}
	


	_getch();

	MALib::SOCK_Uninitialize();
	return 0;
}