#include "talker_client.hpp"
#include "messenger.hpp"

#include <iostream>
#include <cassert>

void talker::run()
{
        unsigned char msg[512];
        while (1) {
                try {
                        memset(msg, 0, sizeof(msg));
                        int s = sizeof(msg);
                        int r = m_rx.recv(msg, s);
                        if (r == 0) {
                                std::cout << "Something wrong" << std::endl;
                                break;
                        }
                        assert(r < s);
                        assert('\0' == msg[r]);
                        std::string str((const char*)msg);
                        assert(0 != m_messenger);
                        m_messenger->push_command(str);
                } catch(const char* m) {
                        std::cout << m <<std::endl;
                }
        }
}

talker::talker(messenger* m, ipc::socket s)
        : m_messenger(m)
        , m_rx(s)
{
        assert(0 != m_messenger);
}

talker::~talker()
{
}
