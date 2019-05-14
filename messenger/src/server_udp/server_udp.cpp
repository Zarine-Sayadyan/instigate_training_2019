#include <ipc/socket.hpp>
#include <cassert>
#include <iostream>
#include <vector>

int main ()
{
    try {
        ipc::socket s(ipc::socket::UDP);
        s.bind(9006);
        char msg[256] = " ";
        char response[256] = "from udp server";
        unsigned short p = 0;
        int len = sizeof(msg);
        assert(s.is_valid());
        //send the message
        char from_ip[IP_ADDRESS_LENGTH];
        s.recvfrom((unsigned char*)msg, len, from_ip, p);
        std::cout << "Client sent" << msg << std::endl;
        s.sendto((const unsigned char*)response, sizeof(response),from_ip, p);
        s.close();
    } catch(const char* e) {
        std::cout << e << std::endl;
    }
    // s.close();
    return 0;
}
