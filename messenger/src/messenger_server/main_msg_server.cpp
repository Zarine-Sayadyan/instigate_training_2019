
#include "server.hpp"

#include <iostream>

int main()
{
        try {
                messenger_server::server s(9000);
                s.run();
        } catch(const char* m) {
                std::cout << m << std::endl;
        }
        return 0;
}
