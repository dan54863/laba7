#include <winSock2.h>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable:4996)
SOCKET Alltogether[50];//все соединени€ пользователей
int j = 0;
void CHandler(int id)
{
	setlocale(LC_ALL, "Russian");
	char chat[256];// текст клиента
	while (true) 
	{
		recv(Alltogether[id], chat, sizeof(chat), NULL);// принимаем сообщение клиента
		for (int i = 0; i < j; i++)// отправл€ем
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
	WSAData wsa;//cтруктура
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsa) != 0) 
	{
		cout << "Error - library" << endl;
		exit(1);
	}

	SOCKADDR_IN address;// хранение адресса
	int sizeofaddr = sizeof(address);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(8080);
	address.sin_family = AF_INET;

	SOCKET sock= socket(AF_INET, SOCK_STREAM, NULL);
	bind(sock, (SOCKADDR*)& address, sizeof(address));
	listen(sock, SOMAXCONN);// прослушка порта
	// дл€ удерижвани€ соединени€ с клиентом
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
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CHandler, (LPVOID)(i), NULL, NULL);// после ее выполнени€ работает два потока, принимаютс€ новые соединени€ и отправка сообщенй
		}
	}
	system("pause");
	return 0;
}