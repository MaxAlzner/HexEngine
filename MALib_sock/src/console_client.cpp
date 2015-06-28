
#include <stdio.h>
#include <conio.h>

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
	test1.a = 5;
	test1.g = 8.1;
	test1.b = 6;
	test1.c = 23;
	test1.h = 0.67f;
	test1.j = 1.36f;
	*((TEST_STRUCT*)buffer) = test1;
	printf("SENT : %d %f %d %d %f %f\n", test1.a, test1.g, test1.b, test1.c, test1.h, test1.j);
	return 1000;
}
int receive(char* buffer, uint bytes)
{
	TEST_STRUCT test2;
	test2 = *((TEST_STRUCT*)buffer);
	printf("RECIEVED : %d %f %d %d %f %f\n", test2.a, test2.g, test2.b, test2.c, test2.h, test2.j);
	return 1000;
}

int main()
{
	MALib::SOCK_Initialize();
	
	static char ip[64];
	static uint port = 0;

	printf("IP ADDRESS : ");
	scanf("%s", ip);
	//printf("PORT : ");
	//scanf("%d", &port);

	TEST_STRUCT test1, test2;
	test1.a = 5;
	test1.g = 8.1;
	test1.b = 6;
	test1.c = 23;
	test1.h = 0.67f;
	test1.j = 1.36f;
	
	if (MALib::SOCK_Connect(20533, ip, send, receive))
	{
		printf("SERVER CONNECTION SUCCESSFUL\n");
	}
	else
	{
		printf("SERVER CONNECTION UNSUCCESSFUL\n");
		printf("CONNECTION ERROR : %d\n", MALib::SOCK_CheckError());
	}

	_getch();

	MALib::SOCK_Uninitialize();
	return 0;
}