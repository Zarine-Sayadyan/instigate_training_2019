#include <socket.hpp>
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
        int len = 256;
        assert(s.is_valid());
        //send the message
        s.recvfrom((unsigned char*)msg, len, p);
        std::cout << p << std::endl;
        std::cout << "Clent sent" << msg << std::endl;
        s.sendto((const unsigned char*)response, sizeof(response), p);
//        s.close();
    } catch(const char* e) {
        std::cout << e << std::endl;
    }
    // s.close();
    return 0;
}
