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
    char to_ip[] = "127.0.0.1";
    unsigned short p = 9006;
    int len = sizeof(response);
    char msg[256] = " barev udp";
    c.sendto((const unsigned char*) msg, sizeof(msg), to_ip, p);
    char from_ip[IP_ADDRESS_LENGTH];
    c.recvfrom((unsigned char*)response, len, from_ip, p);

    // print server's response
    std::cout << "Server sent the data >>> " << response << std::endl;
//    c.close();
    return 0;
}
