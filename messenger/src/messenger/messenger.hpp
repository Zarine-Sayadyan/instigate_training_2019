#ifndef MESSENGER_MESSENGER_HPP
#define MESSENGER_MESSENGER_HPP

#include "login_page.hpp"
#include "main_page.hpp"

#include <QObject>

class messenger : public QObject
{
        Q_OBJECT
public slots:
        void show_login();
        void show_main();
private:
        main_page* m_main;
        login_page* m_login;
public:
        explicit messenger();
        virtual ~messenger();
};

#endif // MESSENGER_MESSENGER_HPP
