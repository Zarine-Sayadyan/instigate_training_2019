#include "talker_client.hpp"
#include "messenger.hpp"

#include <iostream>
#include <cassert>

void talker::run()
{
        while (1) {
                try {
                        unsigned char msg[512];
                        int s = sizeof(msg);
                        int r = m_rx.recv(msg, s);
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
