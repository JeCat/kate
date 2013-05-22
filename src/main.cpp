#include <QApplication>
#include <QFile>
#include <QDebug>
//#include "jsapi/scriptapi.h"
#include "htmlwindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    ScriptAPI * api = new ScriptAPI() ;

    if(argc>1)
    {
        for(int i=1;i<argc;i++)
        {
            api->createWindow(QVariant(argv[i])) ;
        }
    }
    else
    {
        api->createWindow(QVariant(application.applicationDirPath()+"/../app/index.html")) ;
    }

    return application.exec() ;
}

