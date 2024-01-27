#include "include/loginwindow.h"
#include <QApplication>

#define DEBUG 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    #if !DEBUG
        LoginWindow lw;
        lw.setFixedSize(750, 500);
        lw.show();
    #endif

    #if DEBUG
        User *tempUser = new User(0, "test", "test");
        MainWindow mw(tempUser);
        mw.show();
    #endif

    return a.exec();
}
