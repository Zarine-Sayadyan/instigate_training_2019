#include "chat.hpp"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Chat chat;
    chat.show();
    return app.exec();
}
