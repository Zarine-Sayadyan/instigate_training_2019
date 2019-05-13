#include "socket.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


ipc::socket ipc::socket::duplicate()
{
    if (! is_valid()) {
        throw "invalid socket\n";
    }
    int fd = ::dup(m_socket);
    if (fd < 0) {
        throw "Duplicate error";
    }
    if (-1 == fd) {
        throw "Error: see perror";
    }
    if (! fd.is_valid()) {
        throw "Duplicate error\n";
    }
    return fid;
}

void ipc::socket::bind(unsigned short port)
{
    assert(is_valid());
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    int r = ::bind(id(), (const sockaddr*)&addr, sizeof(addr));
    if (r < 0) {
        throw "can't bind socket\n";
    }
}

void ipc::socket::listen()
{
    assert(is_valid());
    int ret = ::listen(id(), MAX_CONNECTIONS);
    if (ret < 0) {
        throw "Listen error\n";
    }
}

ipc::socket ipc::socket::accept() const
{
    assert(is_valid());
    socket s(NONE);
    assert(! s.is_valid());
    s.m_socket = ::accept(m_socket, 0, 0);
    if (! s.is_valid()) {
        throw "Accept error\n";
    }
    return s;
}

void ipc::socket::connect(const char* ip, unsigned short p)
{
    assert(is_valid());
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(p);

    int r = ::inet_pton(AF_INET, ip, &addr.sin_addr);
    if (0 == r) {
        throw "Invalid network address\n";
    }
    if (r != 1) {
        throw "Error, see perror\n";
    }
    r = ::connect(id(), (struct sockaddr*)&addr, sizeof(addr));
    if (0 != r) {
        throw "Error connection to remote server\n";
    }
}

void ipc::socket::send(const unsigned char* m, unsigned int c)
{
    if (! is_valid()) {
        throw "attempt to send through invalid socket\n";
    }
    int sent_bytes = ::send(m_socket, m, c, 0);
    if (sent_bytes < 0) {
        throw "send error\n";
    }
    // TODO what if sent_bytes > 0 and sent_bytes < c?
    assert(sent_bytes == (int)c);
}

void ipc::socket::sendto(const unsigned char* m, unsigned int c,
                char * to_ip, unsigned short p)
{
    if (! is_valid()) {
        throw "attempt to send through invalid socket\n";
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(p);
    int r = ::inet_pton(AF_INET, to_ip, &addr.sin_addr);
    if (0 == r) {
        throw "Invalid network address\n";
    }
    if (r != 1) {
        throw "Error, see perror\n";
    }
    int sent_bytes = ::sendto(m_socket,(const char*) m, c, MSG_CONFIRM,
           (const struct sockaddr*) &addr, sizeof(addr));
    if (sent_bytes < 0) {
        throw "send error\n";
    }
    // TODO what if sent_bytes > 0 and sent_bytes < c?
    assert(sent_bytes == (int)c);
}

int ipc::socket::recv(unsigned char* m, int s)
{
    if (! is_valid()) {
        throw "attempt to receive through invalid socket\n";
    }
    int r = ::recv(m_socket, m, s, 0);
    if (r < 0) {
        throw "recv error\n";
    }
    return r;
}

int ipc::socket::recvfrom(unsigned char* m, int s,
                char* from_ip, unsigned short& from_port)
{
    if (! is_valid()) {
        throw "attempt to receive through invalid socket\n";
    }
    int r = 0;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t len = sizeof(addr);
    r = ::recvfrom(id(), m, s, MSG_WAITALL, (struct sockaddr*) &addr, &len);
    if (r < 0) {
        throw "recv error\n";
    }
    if (NULL == inet_ntop(AF_INET, &addr.sin_addr,
                            from_ip, IP_ADDRESS_LENGTH)) {
            throw "Error to get peer address\n";
    }
    from_port = ntohs(addr.sin_port);
    return r;
}

void ipc::socket::close()
{
    ::close(m_socket);
}

bool ipc::socket::is_valid() const
{
    return m_socket >= 0;
}

int ipc::socket::id() const
{
    return m_socket;
}

ipc::socket::protocol ipc::socket::get_protocol() const
{
    if (! is_valid()) {
        return NONE;
    }
    int so_type = -1;
    socklen_t optlen = sizeof(so_type);
    int r = ::getsockopt(id(), SOL_SOCKET, SO_TYPE, &so_type, &optlen);
    if (r != 0) {
        throw "Failed to get socket protocol\n";
    }
    return so_type == SOCK_STREAM ? TCP :
        so_type == SOCK_DGRAM  ? UDP : NONE;
}

ipc::socket::socket(protocol p)
    : m_socket(-1)
{
    if (TCP == p || UDP == p) {
        m_socket = ::socket(AF_INET,
                (TCP == p) ? SOCK_STREAM : SOCK_DGRAM, 0);
        if (m_socket < 0) {
            throw "failed to create socket\n";
        }
    }
}

ipc::socket::socket(const socket& s)
    : m_socket(s.m_socket)
{}

ipc::socket::~socket()
{}

