
#include "server.hpp"

#include <iostream>

int main()
{
        try {
                messenger_server::server s(9010);
                s.run();
        } catch(const char* m) {
                std::cout << m << std::endl;
        }
        return 0;
}
