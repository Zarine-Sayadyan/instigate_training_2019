#include <QApplication>
#include "second_screen.hpp"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    second_screen scnd;
    scnd.show();

    return app.exec();
}
