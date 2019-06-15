#include <sys/types.h> 
#include <sys/fcntl.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>     
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 12345
#define BUF_SIZE 4096                      /* block transfer size */
#define QUEUE_SIZE 10

void fatal(char *string) {
    printf("%s\n", string);
    exit(1);
}

int main(int argc, char *argv[]) {
    int s, b, l, fd, sa, bytes, on = 1;
    char buf[BUF_SIZE];                   /* buffer for outgoing file */
    struct sockaddr_in channel;           /* holds IP address */

    /* Build address structure to bind to socket. */
    memset(&channel, 0, sizeof(channel)); /* zerochannel */
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);

    /* Passive open. Wait for connection. */
    if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
         fatal("socket failed");
    }
    
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    
    if ((b = bind(s, (struct sockaddr *) &channel, sizeof(channel))) < 0) {
        fatal("bind failed");
    }

    /* specify queue size */
    if ((l = listen(s, QUEUE_SIZE)) < 0) { fatal("listen failed"); }

    /* Socket is now set up and bound. Wait for connection and process it. */
    while (1) {
        /* block for connection request */
        if((sa = accept(s, 0, 0)) < 0) { fatal("accept failed"); }

        read(sa, buf, BUF_SIZE); /* read file name from socket */

        /* Get and return the file. */
        /* open the file to be sent back */
        if ((fd = open(buf, O_RDONLY)) < 0) { fatal("open failed");}
        
        while (1) {
            /* read from file */
            if((bytes = read(fd, buf, BUF_SIZE)) < 0) { break; }; 
            write(sa, buf, bytes);   /* write bytes to socket */
        } 
        close(fd);                   /* closefile */
        close(sa);                   /* close connection */
    }
}
