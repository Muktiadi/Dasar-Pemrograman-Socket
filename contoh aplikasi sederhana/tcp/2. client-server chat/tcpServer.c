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
	alamatServer.sin_port = htons(12345); // port aplikasi
    alamatServer.sin_addr.s_addr = INADDR_ANY; // alamat client yang diizinkan untuk membuat koneksi


	// mengaktifkan soket
	bind(idSocket, (struct sockaddr *) &alamatServer, sizeof(alamatServer));

	//  menangkap koneksi dari client
	// angka 5 merupakan jumlah maksimal antrian-client yang mencoba membuat koneksi ke server 
	listen(idSocket, 5);
	
	// membuat variabel alamatClient untuk menyimpan alamat Client
	struct sockaddr_in alamatClient;
	// membuat variabel yang menyimpan panjang data dari variabel alamat client
	int sizeAlamatClient = sizeof(&alamatClient);


	// menerima koneksi dari client, dan menyimpan alamat client.
	int idClient = accept(idSocket, (struct sockaddr *) &alamatClient, &sizeAlamatClient);
	
	// membuat variabel pesan untuk menyimpan pesan yang dikirim dari client
	char pesan[1024];
	
	// membersihkan variabel pesan
	bzero(pesan, 1024);

	printf("## Menunggu pesan dari client... \n");
	
	// menunggu pesan dari client
	read(idClient, pesan, 1024);

	// menampilkan pesan dari client ke konsol
	printf("# > Client: %s\n", pesan);
	
    // meminta input dari konsol
	bzero(pesan,256);
    printf("# > Server: \n");
    fgets(pesan,255,stdin);

	write(idClient,pesan,1024);
		
	// menutup koneksi
	close(idClient);
}