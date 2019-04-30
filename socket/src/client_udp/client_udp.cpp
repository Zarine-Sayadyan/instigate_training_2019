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
    char msg[256] = "barev udp";
    sendto(c, msg, sizeof(msg), 9005)
    recv(c, &response, sizeof(response), 9005);

    // print server's response
    std::cout << "Server sent the data >>> " << response << std::endl;
    close(c);
    return 0;
}
