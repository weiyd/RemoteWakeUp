#include<iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{
	unsigned char mac[6] = { 0x14,0xDD,0xA9,0x7E,0xD9,0x60 };
	unsigned char packet[102];//发送包
	struct sockaddr_in addr;//在ws2def.h中定义
	int sockfd, i, j, on = 1;
	for (int i = 0; i < 6; i++)
		packet[i] = 0xff;
	for (i = 1; i < 17; i++)
		for (j = 0; j < 6; j++)
			packet[i * 6 + j] = mac[j];
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);//UDP
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (const char *)&on, sizeof(on));
	if (sockfd < 0)
	{
		cout << "广播失败" << endl;
		exit(0);
	}
	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.1.255");//广播地址
	sendto(sockfd, (const char *)packet, sizeof(packet), 0, (const struct sockaddr *)&addr, sizeof(addr));
	closesocket(sockfd);
	return 0;
}