#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

#define BUFF_SIZE 2000
#define PORT_NUMBER 55555
#define SERVER_IP "127.0.0.1"
struct sockaddr_in peerAddr; // sockaddr_in is a struct for the socket address and port for IPv4 addresses (AF_INET)

int createTunDevice() {
    int tunfd; // Tunnel File Descriptor
    struct ifreq ifr;  // ifreq is a struct for all information about a network device
    memset(&ifr, 0, sizeof(ifr)); //initializes memory block to be used by the net device

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

    tunfd = open("/dev/net/tun", O_RDWR); // Inititialises tun device with Read/Write access
    ioctl(tunfd, TUNSETIFF, &ifr); // sets up tunnel I/O rules in kernel

    return tunfd;
}

int connectToUDPServer(){
    int sockfd; // Socket File Descriptor
    char *hello="Hello";

    memset(&peerAddr, 0, sizeof(peerAddr)); // Initialises memory to be used by the socket
    peerAddr.sin_family = AF_INET; // Sets Address Family to Internet Addresses (pretty much always used)
    peerAddr.sin_port = htons(PORT_NUMBER); // htons is a converter from host to network byte order
    peerAddr.sin_addr.s_addr = inet_addr(SERVER_IP); // converts SERVER_IP to format used by the socket

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Initialises socket as IP/UDP, meaning the third param isn't used.

    // Send a hello message to "connect" with the VPN server
    sendto(sockfd, hello, strlen(hello), 0, (struct sockaddr *) &peerAddr, sizeof(peerAddr));

    return sockfd;
}



void tunSelected(int tunfd, int sockfd){
    int  len;
    char buff[BUFF_SIZE];

    printf("Got a packet from TUN, this should have been encrypted and ready to send out.\n");

    bzero(buff, BUFF_SIZE); // zero the buffer
    len = read(tunfd, buff, BUFF_SIZE); // read the incoming packet from the TUN
    printf("%s",buff);
    sendto(sockfd, buff, len, 0, (struct sockaddr *) &peerAddr, sizeof(peerAddr)); // send received packet to tunnel
}

void socketSelected (int tunfd, int sockfd){
    int  len;
    char buff[BUFF_SIZE];

    printf("Got a packet from the tunnel, this should now be decrypted and read.\n");

    bzero(buff, BUFF_SIZE); // zero the buffer
    len = recvfrom(sockfd, buff, BUFF_SIZE, 0, NULL, NULL); // read the incoming packet from the tunnel
    write(tunfd, buff, len); // write the packet to the TUN

}
int main (int argc, char * argv[]) {
    int tunfd, sockfd;

    tunfd  = createTunDevice();
    sockfd = connectToUDPServer();

    // Enter the main loop
    while (1) {
        fd_set readFDSet; // fd_set is a buffer for a set of file descriptors used by select()

        FD_ZERO(&readFDSet); // FD_ZERO clears the FD set
        FD_SET(sockfd, &readFDSet); // Adds sockfd to the FD set
        FD_SET(tunfd, &readFDSet); // Adds tunfd to the FD set
        select(FD_SETSIZE, &readFDSet, NULL, NULL, NULL); // select() now waits for the FD set to be readable without blocking

        if (FD_ISSET(tunfd,  &readFDSet)) tunSelected(tunfd, sockfd); // if tunfd ready, call tunSelected()
        if (FD_ISSET(sockfd, &readFDSet)) socketSelected(tunfd, sockfd); // if sockfd ready, call socketSelected()
    }
}

