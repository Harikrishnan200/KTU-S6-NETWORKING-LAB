#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
int main()

{
	char buf[100];
	int k,nof;
	socklen_t len;
	int sock_desc;
	struct sockaddr_in server;
	sock_desc=socket(AF_INET, SOCK_STREAM,0);

	if(sock_desc==-1)
		printf("Error in Socket creation\n");

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;

	server.sin_port=3003;
	k=connect(sock_desc, (struct sockaddr*) &server, sizeof(server));

	if(k==-1)
		printf("Error in connecting to server\n");
	printf("Socket Creation Successful\nConnected to Server\n");
	printf("Enter the total number of frames:");
	scanf("%d",&nof);
	printf("\n");
	sprintf(buf,"%d", nof);
	k = send(sock_desc,buf,100,0);
    
	for(int i=0;i<nof;i++)
	{
		if(i%2==0){
			printf("Frame [0] Sent\n");
			k=send(sock_desc,buf,100,0);
			sleep(1);
		}
		else
		{
			printf("Frame [1] Sent\n");
			k = send(sock_desc,buf,100,0);
			sleep(1);
		}
		printf("Acknowledgement received from server for Frame [%d]\n",(i%2==0)?1:0);
		k=read(sock_desc,buf,100);
		printf("\n");
	}
	close(sock_desc);
	return 0;
}