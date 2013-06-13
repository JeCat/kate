#include <QApplication>
#include <QFile>
#include <QDebug>
//#include "jsapi/scriptapi.h"
#include "htmlwindow.h"
#include "networkcookiejar.h"

#include <Windows.h>
#include <QDesktopServices>

ScriptAPI * api = NULL ;

HHOOK g_mouseHook = NULL;
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam )
{
    MSG* pMsg = (MSG*)lParam ;
    switch(pMsg->message)
    {
    case  WM_MOUSEMOVE:
        api->onMouseMoving(pMsg->pt.x,pMsg->pt.y) ;
        return true;
    case  WM_LBUTTONUP:
        api->onMouseUp() ;
        return true;
    }

    return CallNextHookEx(0,nCode,wParam,lParam);
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    api = new ScriptAPI() ;
    g_mouseHook = SetWindowsHookEx( WH_GETMESSAGE,mouseProc,GetModuleHandle(NULL),GetCurrentThreadId());

    // localStorage
    QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    QWebSettings::globalSettings()->setOfflineStoragePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation)+"\\kate-localeStorage.dat");

    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    QWebSettings::globalSettings()->setLocalStoragePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation)+"\\kate-localeStorage.dat");
    qDebug() << "localeStorage path:" << QDesktopServices::storageLocation(QDesktopServices::DataLocation)+"\\kate-localeStorage.dat" ;

    bool autoshow = false ;
    QString app("") ;
    qDebug() << argc ;
    for(int i=1;i<argc;i++)
    {
        if(QString(argv[i])=="--show")
        {
            autoshow = true ;
        }
        else if(QString(argv[i])=="--app")
        {
            if(argc>++i)
            {
                app = argv[i] ;
            }
        }
    }

    // default app path
    if(!app.length())
    {
        app = application.applicationDirPath()+"/../app/index.html" ;
    }

    // create first window
    int wndId = api->createWindow(QVariant(app)).toInt() ;

    // auto show it
    if(autoshow)
    {
        api->htmlWindow(wndId)->show() ;
    }

    int ret = application.exec() ;

    delete api ;
    api = NULL ;

    NetworkCookieJar::instance()->Save() ;

    return ret ;
}

