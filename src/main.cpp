#include <QApplication>
#include <QFile>
#include <QDebug>
#include "htmlwindow.h"

int main(int argc, char *argv[])
{
    for(int i=1;i<argc;i++)
    {
        QApplication application(argc, argv);

        HtmlWindow wnd( argv[i] ) ;
        wnd.show() ;

        return application.exec() ;
    }

    qDebug() << "kate quit, but nothing to do ." ;
    return 0 ;
}

