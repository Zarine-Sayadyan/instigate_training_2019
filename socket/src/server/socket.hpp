
try {
        socket s(socket::TCP);
        s.bind(9002);
        s.listen();
        socket c = s.accept();
} catch(const std::exception& e) {
}

class socket
{
        ::socket()
        ::bind
        enum protocol { TCP, UDP};
        socket(protocol p);
        bind(unsigned short port);
        listen();
        socket& accept() 
        {
                
        }
        connect(char* ip);
};
