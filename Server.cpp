#include <winSock2.h>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable:4996)
SOCKET Alltogether[50];//��� ���������� �������������
int j = 0;
void CHandler(int id)
{
	setlocale(LC_ALL, "Russian");
	char chat[256];// ����� �������
	while (true) 
	{
		recv(Alltogether[id], chat, sizeof(chat), NULL);// ��������� ��������� �������
		for (int i = 0; i < j; i++)// ����������
		{
			if (i == id) 
			{
				continue;
			}
			send(Alltogether[i], chat, sizeof(chat), NULL);
		}
	}
}

int main(int argc, char* argv[]) 
{

	//WSAStartup
	WSAData wsa;//c��������
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsa) != 0) 
	{
		cout << "Error - library" << endl;
		exit(1);
	}

	SOCKADDR_IN address;// �������� �������
	int sizeofaddr = sizeof(address);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(8080);
	address.sin_family = AF_INET;

	SOCKET sock= socket(AF_INET, SOCK_STREAM, NULL);
	bind(sock, (SOCKADDR*)& address, sizeof(address));
	listen(sock, SOMAXCONN);// ��������� �����
	// ��� ����������� ���������� � ��������
	SOCKET newCon;
	for (int i = 0; i < 50; i++) 
	{
		newCon = accept(sock, (SOCKADDR*)& address, &sizeofaddr);

		if (newCon == 0)
		{
			cout << "clien not connect \n" << endl;
		}
		else 
		{
			cout << "Success Connection , Client here!" << endl;
			char text[256] = "You are Welcome! (Don't spam) @Danil Voronin - 746";
			send(newCon, text, sizeof(text), NULL);

			Alltogether[i] = newCon;
			j++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CHandler, (LPVOID)(i), NULL, NULL);// ����� �� ���������� �������� ��� ������, ����������� ����� ���������� � �������� ��������
		}
	}
	system("pause");
	return 0;
}