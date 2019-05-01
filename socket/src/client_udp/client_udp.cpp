#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <socket.hpp>

int main ()
{
    //create a socket(client_socket)
    ipc::socket c(ipc::socket::UDP);
    char response[256];
    unsigned short p = 9005;
    int len = 0;
    char msg[256] = "barev udp";
    c.sendto((const unsigned char*) msg, sizeof(msg), p);
    c.recvfrom((unsigned char*)response, len, p);

    // print server's response
    std::cout << "Server sent the data >>> " << response << std::endl;
    c.close();
    return 0;
}
