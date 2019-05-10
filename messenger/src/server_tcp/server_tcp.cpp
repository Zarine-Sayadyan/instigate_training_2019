#include "talker_tcp.hpp"
#include <socket.hpp>
#include <iostream>
#include <vector>

std::vector<talker*> talkers;

void run(ipc::socket s)
{
        while (1) {
                try {
                        ipc::socket client = s.accept();
                        talker* t = new talker(client);
                        t->create_thread();
                        talkers.push_back(t);
                } catch (const char* s) {
                        std::cout << "Error: " << s << std::endl;
                }
        }
}

int main ()
{
        try {
                ipc::socket s(ipc::socket::TCP);
                s.bind(9003);
                s.listen();
                run(s);
                s.close();
        } catch(const char* e) {
                std::cout << e << std::endl;
        }
        return 0;
}
