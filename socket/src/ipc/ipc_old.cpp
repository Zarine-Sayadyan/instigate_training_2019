#include "ipc.hpp"

ipc::socket::socket(int domain, int type, protocol p)
{}

ipc::socket::socket(const socket& other)
{
	m_socket = other.m_socket;
}

ipc::socket::~socket()
{}

void ipc::bind(unsigned short port)
{
	int ret = bind(m_socket, m_addr, sizeof(m_addr) );
        if (ret <= 0) {
               throw "can't bind socket\n";
               close(m_socket);
        } return;

}

void ipc::listen(unsigned short queue_len)
{
	int max_len = listen(m_socket, queue_len);
	if (max_len < 0) {
                throw "Listen error\n";
                close(m_socket);
        } 
        return;
}

socket& ipc::socket::accept()
{}

void ipc::socket::connect(char *ip)
{}

void ipc::socket::send(char response[25], int flag)
{}

void ipc::socket::recv(char response[25], int flag)
{}

void ipc::socket::close()
{
	close(m_socket);
}

