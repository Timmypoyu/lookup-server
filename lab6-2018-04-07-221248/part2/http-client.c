/*
 * http-client.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


static void die(const char *s) { perror(s); exit(1); }

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s <server-ip> <server-port> <filename>\n",
                argv[0]);
        exit(1);
    }

    //convert host name to ip address
    struct hostent *he;
    char *serverName = argv[1];

    //get server up from server name
    if((he = gethostbyname(serverName)) == NULL){
	    die("gethostbyname failed");
    }
    char *filePath = argv[3];
    char *serverIP = inet_ntoa(*(struct in_addr *)he->h_addr);
    unsigned short port = atoi(argv[2]);
    const char *filename = strrchr(argv[3], '/') + 1;
    FILE *fp;
   
    if((fp = fopen(filename, "wb")) == NULL){
		   die(filename);
	   }

    // Create a socket for TCP connection

    int sock; // socket descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket failed");
    // Construct a server address structure

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr)); // must zero out the structure
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(serverIP);
    servaddr.sin_port        = htons(port); // must be in network byte order

    // Establish a TCP connection to the server

    if (connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        die("connect failed");
    /*
     * send(int socket, const void *buffer, size_t length, int flags)
     *
     *   - normally, send() blocks until it sends all bytes requested
     *   - returns num bytes sent or -1 for error
     *   - send(sock,buf,len,0) is equivalent to write(sock,buf,len)
     */

    //send out Get signals
    char getSig[1000]; 
    snprintf(getSig, sizeof(getSig), "GET %s HTTP/1.0\r\nHost: %s:%d\r\n", filePath, serverName, (int)port);
    send(sock, getSig, strlen(getSig), 0);
    send(sock, "\r\n", strlen("\r\n"), 0);
    
    //wrap descriptor and recv (fread)
    char buf[4096];
    char key[4] = "200";
    FILE *input = fdopen(sock, "r");
    if (fgets(buf, sizeof(buf), input) == NULL){
	    die("header reading fail");
    }

    if(strstr(buf, key)){
	   //found 200
 	   while(fgets(buf, sizeof(buf), input) != NULL){
		   if(buf[0] == '\r'){
		 	  break;
		  }
	   }

	   while(fgets(buf, sizeof(buf), input) != NULL){
		   fwrite(buf, strlen(buf), 1, fp);
	   }

    }else{
	   //not found 200
	   printf("%s", buf);
	   remove(filename);
	  } 

    if (ferror(fp)) {
        // fread() returns 0 on EOF or error, so we check if error occurred
	die("fgets failed");
    }
    fclose(fp);
  
    // recv() will return 0 when the server closes the TCP connection
    char x;
    assert(recv(sock, &x, 1, 0) == 0);

    // Clean-up
    close(sock);
    return 0;
}
