#include<stdio.h>
#include<sys/socket.h> 
#include <netinet/in.h>

int main(int argc, char *argv[]) {
	
	int idSocket = socket(AF_INET, SOCK_STREAM, 0); 
	
	struct sockaddr_in alamatServer;
	bzero((char *) &alamatServer, sizeof(alamatServer));
	
    alamatServer.sin_family = AF_INET;
    alamatServer.sin_addr.s_addr = inet_addr("216.239.38.120");
    alamatServer.sin_port = htons(80);

    if (connect(idSocket, (struct sockaddr*)&alamatServer, sizeof(alamatServer)) < 0) {
       perror("ERROR connecting");
       exit(1);
    }
	
	char pesan[1024];
	bzero(pesan, 1024);
	
	strcpy(pesan,"GET / HTTP/1.1\r\n\r\n");	
	
	write(idSocket, pesan, strlen(pesan));
		
	read(idSocket, pesan, 1024);
	printf("Server: %s\n", pesan);
		
	close(idSocket);
}