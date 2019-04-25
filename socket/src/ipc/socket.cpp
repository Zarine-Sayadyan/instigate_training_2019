#include "socket.hpp"

ipc::socket::socket(int domain, protocol p)
	: m_protocol(p)
	, m_domain(domain)
{
        switch (m_protocol) {
                case TCP:
                        m_socket = ::socket(m_domain, SOCK_STREAM, 0);
                        break;
                case UDP:
                        m_socket = ::socket(m_domain, SOCK_DGRAM, 0);
                        break;
                default: throw "wrong protocol\n";
        }
}

ipc::socket::socket(protocol p)
	: m_protocol(p)
{
        switch (m_protocol) {
                case TCP:
                        m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
                        break;
                case UDP:
                        m_socket = ::socket(AF_INET, SOCK_DGRAM, 0);
                        break;
                default: throw "wrong protocol\n";
        }
}

ipc::socket::socket(const socket& other)
{
        m_socket = other.m_socket;
	m_protocol = other.m_protocol;
	m_domain = other.m_domain;
        m_port = other.m_port;
        m_addr = other.m_addr;
}

ipc::socket::~socket()
{}

void ipc::socket::bind(unsigned short port)
{
        struct sockaddr_in addr;
	addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        m_addr = addr;
	int ret = ::bind(m_socket, (const sockaddr*)&addr, sizeof(addr));
	if (ret <= 0) {
		throw "can't bind socket\n";
		::close(m_socket);
	} return;
}

void ipc::socket::listen(unsigned short queue_len)
{
	int ret = ::listen(m_socket, queue_len);
	if (ret < 0) {
		throw "Listen error\n";
		::close(m_socket);
	} return;
}

ipc::socket ipc::socket::accept()
{
        socklen_t s = 0;
	int client_socket = ::accept(m_socket, (sockaddr*)&m_addr, &s);
	if (client_socket >= 0) {
		return socket(m_domain, m_protocol);
	}
	throw "error accept\n";
}

void ipc::socket::connect()
{
	int c = ::connect(m_socket,(struct sockaddr*)&m_addr, sizeof(m_addr));
	if (-1 == c) {
		throw "Error connection to remote server\n";
	}
}
void ipc::socket::send(char response[MSG_SIZE])
{
	::send(m_socket, &response, MSG_SIZE, 0);
}

void ipc::socket::recv(char response[MSG_SIZE])
{
	::recv(m_socket, &response, MSG_SIZE, 0);
}

void ipc::socket::close()
{
	::close(m_socket);
}


