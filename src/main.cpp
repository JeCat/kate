#include <QApplication>
#include <QFile>
#include <QDebug>
#include "htmlwindow.h"

int main(int argc, char *argv[])
{
    QList<HtmlWindow*> windowPool ;
    ScriptAPI api(&windowPool) ;
    QApplication application(argc, argv);

    if(argc>1)
    {
        for(int i=1;i<argc;i++)
        {
            api.createWindow(QVariant(argv[i])) ;
        }
    }
    else
    {
        api.createWindow(QVariant(application.applicationDirPath()+"/../app/index.html")) ;
    }

    return application.exec() ;
}

