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
	messenger::server* m_server;//?????????????

	std::vector<std::string> m_users;
	std::vector<talker*> talkers;
};

class messenger::talker : public threads::thread
{
public:
        talker(this, ipc::socket rx, ipc::socket tx);
public:
        void run();
private:
        void parse(command_name);
};

int main()
{
        messenger::server s;
        s.run();
        return 0;
}
