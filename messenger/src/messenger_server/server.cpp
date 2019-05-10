#include "server.hpp"

void messenger::server::run()
{
	ipc::socket c = m_socket.accept();
	talker* t = new talker(this, c, c.duplicate());
	t->create_thread();
	talkers.push_back(t);
}

void messenger::server::login_user(char* user) //add_user() ete user goyutyun chuni
{
	auto it = find(m_users.begin(),m_users.end(),user);
    if (it == m_users.end()) {
        m_resronse = "ERROR:No such registered user";
    } else {
        *it->online;
        m_response = "UPDATE:user="+user+",status=online";
        notify(m_response);
    }
}

void messenger::server::logout_user() 
{
	user->offline;
}

void messenger::server::register_user()
{
	//find_user() -if true than failed.
}

void messenger::server::notify(m_response)
{
	for (auto i:talkers) {
		tx.send(m_respone); //update command
	}
}

void messenger::server::add_user(std::string user)
{
	m_users.push_back(user);
}

bool messenger::server::find_user(std::string user) const
{
	for (auto it = m_users->begin(); it != m_users->end(); ++it) {
		if (it == user) {
			return true;
		}
	}
	return false;
}

// talkers

messenger::talker::talker(this, ipc::socket rx, ipc::socket tx) 
{}
  
void messenger::talker::run()
{
	while (1) {
        assert(rx_socket.is_valid());
		m_command = rx.recv();
		parse(m_command); // syntax
		rx.send(m_response); //response=DONE||FAILED||error
	}
}

void messenger::talker::parse(command_name)
{
	switch (command_name) {
		case REGISTER :
			handle_register(); // m_server->register_user(); 
			break;
		case LOGIN:
			handle_login(); // m_server->login_user();
			break;
		case LOGOUT:
			handle_logout(); //m_server->logout_user();
			break;
	}
}

int main()
{
        messenger::server s;
        s.run();
        return 0;
}   
