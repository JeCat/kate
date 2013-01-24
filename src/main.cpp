#include <QApplication>
#include <QFile>
#include <QDebug>
#include "htmlwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HtmlWindow wnd ;

    int runningApps = 0 ;
    for(int i=1;i<argc;i++)
    {
        qDebug() << argv[i] ;

        wnd.show() ;

        runningApps++ ;
        break ;
    }

    if(runningApps>0)
    {
        return a.exec();
    }
    else
    {
        qDebug() << "exit, nothing todo" ;
        return 0 ;
    }
}

