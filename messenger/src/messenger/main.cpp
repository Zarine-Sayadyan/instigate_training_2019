
#include "messenger.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        messenger w;
        w.show_login();
        return app.exec();
}
