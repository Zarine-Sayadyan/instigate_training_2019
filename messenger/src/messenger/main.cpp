
#include "messenger.hpp"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        messenger* w = 0;
        try {
                w = new messenger;
                w->show_login();
        } catch (const char* m) {
                std::cout << m << std::endl;
                return 1;
        }
        return app.exec();
}
