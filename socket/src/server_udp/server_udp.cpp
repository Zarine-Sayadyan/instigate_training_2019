#include "talker_udp.hpp"
#include <socket.hpp>
#include <iostream>
#include <vector>

std::vector<talker*> talkers;

void run(ipc::socket s)
{
    try {
        talker* t = new talker(s);
        t->create_thread();
        talkers.push_back(t);
    } catch (const char* s) {
        std::cout << "Error: " << s << std::endl;
    }
}

int main ()
{
    try {
        ipc::socket s(ipc::socket::UDP);
        s.bind(9005);
        char msg[256] = " ";
        char response[256] = "from udp server";
        unsigned short p = 0;
        int len = 0;
        assert(s.is_valid());
        //send the message
        s.recvfrom((unsigned char*)msg, len, p);
        std::cout << "Clent sent" << msg << std::endl;
        s.sendto((unsigned char*)response, sizeof(response), p);
        s.close();

    } catch(const char* e) {
        std::cout << e << std::endl;
    }
    // s.close();
    return 0;
}
