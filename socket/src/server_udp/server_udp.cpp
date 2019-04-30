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
        s.listen();
        run(s);
    } catch(const char* e) {
        std::cout << e << std::endl;
    }
    // s.close();
    return 0;
}
