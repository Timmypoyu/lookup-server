/*
 * mdb-lookup-server
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

#include "mylist.h"
#include "mdb.h"
#define KeyMax 5 

static void die(const char *s) { perror(s); exit(1); }

int loadmdb(FILE *fp, struct List *dest){
	
	struct MdbRec r;
	struct Node *node = NULL;
	int count = 0;

	while(fread(&r, sizeof(r), 1, fp) == 1){

		struct MdbRec *rec = (struct MdbRec *)malloc(sizeof(r));
		if(!rec){
			return -1;
		}
		memcpy(rec, &r, sizeof(r));

	node = addAfter(dest, node, rec);
	if (node == NULL){
		return -1;
		}

	count++;
	}	

	if (ferror(fp)){
		return -1;
		}
	return count;
}

void freemdb(struct List *list){
	traverseList(list, &free);
	removeAllNodes(list);
}

int main(int argc, char **argv)
{
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR){
		die("signal() failed");
	}
	
    if (argc != 3) {
        fprintf(stderr, "usage: %s <database>  <server-port>\n", argv[0]);
        exit(1);
    }

    unsigned short port = atoi(argv[2]);
    char *filename = argv[1];

    // Create a listening socket (also called server socket) 

    int servsock;
    if ((servsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket failed");

    // Construct local address structure

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // any network interface
    servaddr.sin_port = htons(port);

    // Bind to the local address

    if (bind(servsock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        die("bind failed");

    // Start listening for incoming connections

    if (listen(servsock, 5 /* queue size for connection requests */ ) < 0)
        die("listen failed");

    int clntsock;
    socklen_t clntlen;
    struct sockaddr_in clntaddr;

    char buf[4096];

    while (1) {

        // Accept an incoming connection

        clntlen = sizeof(clntaddr); // initialize the in-out parameter

        if ((clntsock = accept(servsock,(struct sockaddr *) &clntaddr, &clntlen)) < 0)
            die("accept failed");
	
	fprintf(stderr, "A program starts at: %s\n", inet_ntoa(clntaddr.sin_addr));

	//open database and scan
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL)
		die(filename);
    	
	struct List list; 
	initList(&list);

	int loaded = loadmdb(fp, &list);
	if (loaded < 0){
		die("loadmdb");
	}

	fclose(fp);

	//socket descriptor into FILE *
	FILE *sockfp = fdopen(clntsock, "r");
        if (sockfp == NULL)
            die("socket file failed");

	char key[KeyMax +1];

	//Second, receive the file content
        while(fgets(buf, sizeof(buf), sockfp) != NULL){
		
	    //search list here
	    	strncpy(key, buf, sizeof(key)-1);
		key[sizeof(key) -1] = '\0';

		size_t last =strlen(key) -1;
		if(key[last] == '\n'){
			key[last] = '\0';
		}
	    	struct Node *node = list.head;
		int recNo = 1;
		while (node) {
			struct MdbRec *rec = (struct MdbRec *)node->data;
			if (strstr(rec->name, key) || strstr(rec->msg, key)){
				char buf2[1000];
				snprintf(buf2, sizeof(buf2), "%4d: {%s} said {%s}\n", recNo, rec->name, rec->msg);	
				if((send(clntsock, buf2, strlen(buf2), 0)) != strlen(buf2)){
					die("send");
				}
			}
			node = node->next;
			recNo++;
		}
		send(clntsock, "\n", strlen("\n"), 0);
    }

	if(ferror(sockfp)){
		die("sockfp");
	}

	fprintf(stderr, "A program terminated at: %s\n", inet_ntoa(clntaddr.sin_addr));

	fclose(sockfp);
        // Finally, close the client connection and go back to accept()
	freemdb(&list);
        close(clntsock);
    }

}
