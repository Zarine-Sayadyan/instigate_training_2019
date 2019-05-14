
#include "messenger.hpp"
#include "command.hpp"
#include <cassert>
#include <QTimer>

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

void messenger::parse(const std::string& s)
{
        messenger_server::command c(s);
        messenger_server::command::type t = c.get_command();
	switch (t) {
                case messenger_server::command::REGISTER :
			//handle_register();
			break;
                case messenger_server::command::LOGIN:
			//handle_login();
			break;
                case messenger_server::command::LOGOUT:
			//handle_logout();
			break;
                // case command::UPDATE:

                default:
                        assert(false);
                        break;
        }

}

void messenger::push_command(const std::string& str)
{
        m_queue.push(str);
}

std::string messenger::pop_command()
{
        std::string str = m_queue.front();
        m_queue.pop();
        return str;
}

void messenger::handle_messages()
{
        if (! m_queue.empty()) {
                std::string str = pop_command();
                parse(str);
        }
}

messenger::messenger()
        : m_server(ipc::socket::TCP)
        , m_login(0)
        , m_main(0)
        , m_timer(0)
{
        assert(m_server.is_valid());
        m_server.connect("127.0.0.1", 9000);
        m_login = new login_page(m_server);
        assert(0 != m_login);
        m_main = new main_page;
        assert(0 != m_main);

        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(handle_messages()));
        m_timer->start(2000);

        // QObject::connect(m_login->get_ok_button(), SIGNAL(clicked()),
        //                 this, SLOT(show_main()));
        // QObject::connect(m_main->get_logout(), SIGNAL(clicked()),
        //                 this, SLOT(show_login()));
}

messenger::~messenger()
{
        delete m_timer;
        delete m_login;
        delete m_main;
}

