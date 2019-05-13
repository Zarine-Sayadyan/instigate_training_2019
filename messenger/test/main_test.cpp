
#include "main_window.hpp"
#include <QApplication>

int main(int c, char* v[])
{
        QApplication a(c, v);
        MyClass m;
        return a.exec();
}

