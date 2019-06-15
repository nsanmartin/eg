/*
 * This page contains a client program that can request a file 
 * from the server program. The server responds by sending the
 * whole file.
 */

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 12345  /* arbitrary, but client & server must agree */
#define BUF_SIZE 4096      /* block transfer size */

void fatal(char *string) {
    printf("%s\n", string);
    exit(1);
}


int main(int argc, char **argv) {
    int c, s, bytes;              /* buffer for incoming file */
    char buf[BUF_SIZE];           /* info about server */       
    struct hostent *h;            /* holds IP address */        
    struct sockaddr_in channel;

    if (argc != 3) { fatal("Usage: client server-name file-name"); }

    /* look up host's IP address */
    if (!(h = gethostbyname(argv[1]))) { fatal("gethostbyname failed"); };
    if((s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        fatal("socket");
    };
    memset(&channel, 0, sizeof(channel));
    channel.sin_family= AF_INET;
    memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
    channel.sin_port= htons(SERVER_PORT);

    if((c = connect(s, (struct sockaddr *) &channel, sizeof(channel))) < 0) {;
        fatal("connect failed");
    }

   /* Connection is now established. Send file name including 0 byte at end. */
    write(s, argv[2], strlen(argv[2])+1);

    
    /* Go get the file and write it to standard output. */
    while (1) {
        /* read from socket */
        if ((bytes = read(s, buf, BUF_SIZE)) <= 0) { exit (0); }
        write(1, buf, bytes); /* write to standard output */
    }
}

