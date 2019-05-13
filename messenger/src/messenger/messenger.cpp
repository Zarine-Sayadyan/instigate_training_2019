
#include "messenger.hpp"

#include <cassert>

void messenger::show_login()
{
        assert(0 != m_login);
        assert(0 != m_main);
        // assert(m_main->isVisible()); fails on run
        assert(! m_login->isVisible());
        m_main->hide();
        m_login->show();
}

void messenger::show_main()
{
        assert(0 != m_login);
        assert(0 != m_main);
        assert(! m_main->isVisible());
        assert(m_login->isVisible());
        m_login->hide();
        m_main->show();
}

messenger::messenger()
        : m_server(ipc::socket::TCP)
        , m_login(0)
        , m_main(0)
{
        assert(m_server.is_valid());
        m_server.connect("127.0.0.1", 9000);
        m_login = new login_page(m_server);
        assert(0 != m_login);
        m_main = new main_page;
        assert(0 != m_main);
        QObject::connect(m_login->get_ok_button(), SIGNAL(clicked()),
                        this, SLOT(show_main()));
        QObject::connect(m_main->get_logout(), SIGNAL(clicked()),
                        this, SLOT(show_login()));
}

messenger::~messenger()
{
        delete m_login;
        delete m_main;
}


