#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>

#define PORT_NUMBER 55555
#define BUFF_SIZE 2000

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
   ioctl(tunfd, TUNSETIFF, &ifr);       // sets up tunnel I/O rules in kernel

   return tunfd;
}

int initUDPServer() {
    int sockfd; // Socket File Descriptor
    struct sockaddr_in server; // sockaddr_in is a struct for the socket address and port for IPv4 addresses (AF_INET)
    char buff[100];

    memset(&server, 0, sizeof(server)); // Initialises memory to be used by the socket
    server.sin_family = AF_INET;  // Sets Address Family to Internet Addresses (pretty much always used)
    server.sin_addr.s_addr = htonl(INADDR_ANY); // htonl is a converter from host to network byte order
    server.sin_port = htons(PORT_NUMBER); // htons is a converter from host to network byte order

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Initialises socket as IP/UDP, meaning the third param isn't used.
    //bind() assigns the address specified by sockaddr to the socket referred to by the file descriptor sockfd.
    bind(sockfd, (struct sockaddr*) &server, sizeof(server));

    // Wait for the VPN client to "connect".
    bzero(buff, 100); //zero the buffer
    int peerAddrLen = sizeof(struct sockaddr_in);
    int len = recvfrom(sockfd, buff, 100, 0, (struct sockaddr *) &peerAddr, &peerAddrLen);

    printf("Connected with the client: %s\n", buff);
    return sockfd;
}

void tunSelected(int tunfd, int sockfd){
    int  len;
    char buff[BUFF_SIZE];

    printf("Got a packet from TUN, this should have been encrypted and ready to send out.\n");

    bzero(buff, BUFF_SIZE);// zero the buffer
    len = read(tunfd, buff, BUFF_SIZE);// read the incoming packet from the TUN
    sendto(sockfd, buff, len, 0, (struct sockaddr *) &peerAddr, sizeof(peerAddr));// send received packet to tunnel
}

void socketSelected (int tunfd, int sockfd){
    int  len;
    char buff[BUFF_SIZE];

    printf("Got a packet from the tunnel, this should now be decrypted and read.\n");

    bzero(buff, BUFF_SIZE);// zero the buffer
    len = recvfrom(sockfd, buff, BUFF_SIZE, 0, NULL, NULL);// read the incoming packet from the tunnel
    write(tunfd, buff, len);// write the packet to the TUN

}
int main (int argc, char * argv[]) {
   int tunfd, sockfd;

   tunfd  = createTunDevice();
   sockfd = initUDPServer();

   // Enter the main loop
   while (1) {
     fd_set readFDSet;// fd_set is a buffer for a set of file descriptors used by select()

     FD_ZERO(&readFDSet);// FD_ZERO clears the FD set
     FD_SET(sockfd, &readFDSet);// Adds sockfd to the FD set
     FD_SET(tunfd, &readFDSet);// Adds tunfd to the FD set
     select(FD_SETSIZE, &readFDSet, NULL, NULL, NULL);// select() now waits for the FD set to be readable without blocking

     if (FD_ISSET(tunfd,  &readFDSet)) tunSelected(tunfd, sockfd);// if tunfd ready, call tunSelected()
     if (FD_ISSET(sockfd, &readFDSet)) socketSelected(tunfd, sockfd);// if sockfd ready, call socketSelected()
  }
}
 
