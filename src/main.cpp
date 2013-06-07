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
    int wnds = 0 ;
    for(int i=1;i<argc;i++)
    {
        if(QString(argv[i])=="--show")
        {
            autoshow = true ;
        }
        else
        {
            wnds ++ ;
        }
    }

    if(wnds)
    {
        for(int i=1;i<argc;i++)
        {
            if(QString(argv[i])!="--show")
            {
                int wndId = api->createWindow(QVariant(argv[i])).toInt() ;
                if(autoshow)
                {
                    api->htmlWindow(wndId)->show() ;
                }
            }
        }
    }
    else
    {
        api->createWindow(QVariant(application.applicationDirPath()+"/../app/index.html")) ;
    }

    int ret = application.exec() ;

    delete api ;
    api = NULL ;

    NetworkCookieJar::instance()->Save() ;

    return ret ;
}

