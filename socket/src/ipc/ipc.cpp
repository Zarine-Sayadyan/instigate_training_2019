#include "ipc.hpp"

ipc::socket::socket(int domain, int type, protocol p)
	:m_domain(domain)
	,m_type(type)
	,m_protocol(p)
{
	m_socket = socket(m_domain, m_type, m_protocol);
}

ipc::socket::socket(const socket& other)
{
	m_domain = other.m_domain;
	m_type = other.m_type;
	m_protocol = other.m_protocol;
}

ipc::socket::socket()
{}

ipc::socket::~socket()
{}

void ipc::socket::bind(struct sockaddr_in addr, unsigned short port)
{
	init_addr(addr, port);
	int ret = bind(m_socket, m_addr, sizeof(m_addr));
	if (ret <= 0) {
		throw "can't bind socket\n";
		close(m_socket);
	} return;
}

void ipc::socket::listen(unsigned short queue_len)
{
	int ret = listen(m_socket, queue_len);
	if (ret < 0) {
		throw "Listen error\n";
		close(m_socket);
	} return;
}

socket& ipc::socket::accept()
{
	int client_socket = accept(m_socket, m_addr, sizeof(m_addr));
	if (client_socket >= 0) {
		throw "error accept\n";
		return socket(m_domain, m_type, m_protocol);
	}
	return socket();
}

void ipc::socket::connect()
{
	int connection = connect(m_socket,  struct sockadddr* addr, sizeof(addr));
	if (-1 == connection) {
		throw "Error connection to remote server\n";
	}
}

void ipc::socket::init_addr(struct sockaddr_in addr, unsigned short port)
{
	addr. sa.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.m_socket_addr = INADDR_ANY;
        m_addr = addr;
}
void ipc::socket::send(char response[25], int flag)
{
	send(m_socket, &response, sizeof(response), flag);
}

void ipc::socket::recv(char response[25], int flag)
{
	recv(m_socket, &response, sizeof(response), flag);
}

void ipc::socket::close()
{
	close(m_socket);
}


