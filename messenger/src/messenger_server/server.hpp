#include <cstring>
#include "thread.hpp"
#include "socket.hpp"
#include <vector>

namespace messenger
{
        class server;
        class talker;
}
class messenger::server
{
    private:
        void run();
        void login_user();
        void logout_user();
        void register_user();
        void notify();
        void add_user(std::string user) ;
        bool find_user(std::string user) const;

        std::vector<std::string> m_users;
        std::vector<talker*> talkers;
        char* m_buffer;
};

class messenger::talker : public threads::thread
{
    public:
        talker(messenger::server s, ipc::socket rx, ipc::socket tx)
            : rx_socket(rx)
            , tx_socket(tx)
            , m_server(s)
    {}
        void run();
    private:
        void parse(command_name);
    private:
        ipc::socket rx_socket;
        ipc::socket tx_socket;
        messenger::server m_server;
        char* m_command;
        char* m_response;
};

int main()
{
    messenger::server s;
    s.run();
    return 0;
}
