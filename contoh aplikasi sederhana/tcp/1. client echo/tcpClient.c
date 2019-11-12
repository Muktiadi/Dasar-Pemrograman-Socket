#include<stdio.h>
#include<sys/socket.h> 
#include <netinet/in.h>

int main(int argc, char *argv[]) {
	
	// Mendefinisikan jenis soket:
	// AF_INET = pengalamatan internet (ip address)
	// SOCK_STREAM = Koneksi TCP
	// 0 = Standar protokol default	
	int idSocket = socket(AF_INET, SOCK_STREAM, 0); 
	
	
	// Membuat variabel alamatServer dengan tipe data sockaddrr_in
	struct sockaddr_in alamatServer;

	
	// membersikan isi variabel alamatServer
	bzero((char *) &alamatServer, sizeof(alamatServer));

	
	// Mengisi detail alamat server:
    alamatServer.sin_family = AF_INET; // jenis pengalamatan ip address 
    alamatServer.sin_port = htons(12345); // port tujuan
    alamatServer.sin_addr.s_addr = inet_addr("127.0.0.1"); // alamat tujuan



	// membuat koneksi ke tujuan, dibalut dengan if untuk mendeteksi error
	// connect(idSocket, (struct sockaddr*)&alamatServer, sizeof(alamatServer))	
    if (connect(idSocket, (struct sockaddr*)&alamatServer, sizeof(alamatServer)) < 0) {
       perror("ERROR connecting");
       exit(1);
    }
	
	
	
	// membuat variabel untuk membaca pesan
	char pesan[1024];

	// membersihkan variabel pesan
	bzero(pesan, 1024);
	
	// menuliskan tulisan "client :" ke konsol
	printf("# > Client: \n");
	
	// menyimpan input dari keyboard user
	fgets(pesan,1024,stdin);

	
	// mengirimkan pesan ke server
	write(idSocket, pesan, strlen(pesan));

	// menutup koneksi soket
	close(idSocket);
}