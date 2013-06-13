#include "scriptapi.h"
#include <QWebView>
#include <QDebug>
#include <QWebInspector>
#include <QFile>
#include <QApplication>
#include <QSound>
#include <windowsx.h>
#include "qxtglobalshortcut.h"

#include <QLocalSocket>
#include <stdlib.h>
#include <unistd.h>

#define getHtmlWnd(ret) \
    int nWndId = wndId.toInt() ; \
    if( nWndId>=m_pWindowPool->length() ) \
    {\
        return ret;\
    }\
    HtmlWindow * wnd = m_pWindowPool->at(nWndId) ;\


ScriptAPI::ScriptAPI()
    : QObject()
    , m_pWindowPool(new QList<HtmlWindow*>)
    , screenshoter(new ScreenShoter(NULL))
    , draggingWindow(NULL)
{}
ScriptAPI::~ScriptAPI()
{
    delete m_pWindowPool ;
    delete screenshoter ;

}

#define loadscript(url) \
    frame->evaluateJavaScript(\
                QString("var script=document.createElement('script');script.src='%1';document.head.appendChild(script);")\
                    .arg(url)\
    ) ;\


void ScriptAPI::setupWebkitScript(HtmlWindow* wnd,QWebFrame * frame)
{
    qDebug() << "setupWebkitScript" ;
    QString folder = QApplication::instance()->applicationDirPath() ;
    QString appFolder = folder+"/../app" ;

    frame->addToJavaScriptWindowObject("kateapi",this) ;
    frame->evaluateJavaScript(QString("kateapi.wndId = %1 ;").arg(wnd->id)) ;
    frame->evaluateJavaScript(QString("kateapi.parentWndId = %1 ;").arg(wnd->parentId)) ;
    frame->evaluateJavaScript(QString("kateapi.appFolder = \"%1\";").arg(appFolder)) ;

    loadscript(folder+"/../asserts/kate.js") ;
}


QVariant ScriptAPI::createWindow(QVariant url,int parentId)
{
    qDebug() << "create html window by url :" << url.toString() ;

    HtmlWindow * wnd = new HtmlWindow(url.toString(),this,m_pWindowPool->length()) ;
    wnd->parentId = parentId ;
    m_pWindowPool->append(wnd) ;
    //wnd->show() ;

    return QVariant(wnd->id) ;
}

HtmlWindow * ScriptAPI::htmlWindow(int wndId)
{
    return m_pWindowPool->at(wndId) ;
}


void ScriptAPI::drag(QVariant wndId)
{
    getHtmlWnd()
    draggingWindow = wnd ;
    preMousePos = QCursor::pos();//获取当前光标的位置
}

void ScriptAPI::onMouseMoving(int x,int y )
{
    if(!draggingWindow)
    {
        return ;
    }

    QPoint pos = draggingWindow->pos() ;
    draggingWindow->move(
        pos.x() + x-preMousePos.x()
        , pos.y() + y-preMousePos.y()
    );

    preMousePos.setX(x);
    preMousePos.setY(y);
}
void ScriptAPI::onMouseUp()
{
    draggingWindow = NULL ;
}


void ScriptAPI::require(QString url)
{

    QFile scriptFile(url) ;
    if(!scriptFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "can't require script, file not found: " << url ;
        return ;
    }
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();

    //m_window->webView()->page()->mainFrame()->evaluateJavaScript(contents) ;

    scriptFile.close() ;
//    QString code = "(function (){var node = document.createElement('script') ; node.src = '"
//            + url
//            + "' ; document.head.appendChild(node) ;})()" ;
//    m_window->webView()->page()->mainFrame()->evaluateJavaScript(code) ;
}



void ScriptAPI::show(QVariant wndId)
{
    //qDebug() << "show()" << wndId << m_pWindowPool->length() ;

    getHtmlWnd()
    wnd->show() ;
}

void ScriptAPI::hide(QVariant wndId)
{
    //qDebug() << "hide()" << wndId << m_pWindowPool->length() ;
    getHtmlWnd()
    wnd->hide() ;
}
void ScriptAPI::close(QVariant wndId)
{
    //qDebug() << "hide()" << wndId << m_pWindowPool->length() ;
    getHtmlWnd()
    wnd->close() ;
}
void ScriptAPI::minimize(QVariant wndId)
{
    //qDebug() << "hide()" << wndId << m_pWindowPool->length() ;
    getHtmlWnd()
    wnd->showMinimized() ;
}
void ScriptAPI::maximize(QVariant wndId)
{
    //qDebug() << "hide()" << wndId << m_pWindowPool->length() ;
    getHtmlWnd()
    wnd->showMaximized() ;
}
void ScriptAPI::normal(QVariant wndId)
{
    //qDebug() << "hide()" << wndId << m_pWindowPool->length() ;
    getHtmlWnd()
    wnd->showNormal() ;
}

QVariant ScriptAPI::width(QVariant wndId)
{
    getHtmlWnd(QVariant(false))
    return wnd->width();
}
QVariant ScriptAPI::height(QVariant wndId)
{
    getHtmlWnd(QVariant(false))
    return wnd->height() ;
}

void ScriptAPI::resize(QVariant wndId,int w,int h)
{
    getHtmlWnd()
    wnd->resize(w,h) ;
}

void ScriptAPI::setWindowFlags(QVariant wndId,int flag)
{
    getHtmlWnd()
    wnd->setWindowFlags((Qt::WindowFlags)flag) ;
}

QVariant ScriptAPI::windowFlags(QVariant wndId)
{
    getHtmlWnd(QVariant(false))
    return QVariant((int)wnd->windowFlags()) ;
}

void ScriptAPI::inspector(QVariant wndId)
{
    getHtmlWnd()
    wnd->inspector()->show() ;
}

QVariant ScriptAPI::eval(QVariant wndId,QString code)
{
    getHtmlWnd(QVariant())
    return wnd->mainFrame()->evaluateJavaScript(code) ;
}

void ScriptAPI::shotScreen()
{
    screenshoter->grapWindowScreen();
}

void ScriptAPI::setTitle(QVariant wndId,QString title)
{
    getHtmlWnd()
    wnd->setWindowTitle(title);
}

QVariant ScriptAPI::title(QVariant wndId)
{
    getHtmlWnd(QVariant())
    return wnd->windowTitle();
}

void ScriptAPI::playSound(QString mediaPath)
{
    qDebug() << mediaPath ;
    QSound::play(mediaPath);
}


int ScriptAPI::wndPosX(QVariant wndId)
{
    getHtmlWnd(-1)
    return wnd->pos().x() ;
}

int ScriptAPI::wndPosY(QVariant wndId)
{
    getHtmlWnd(-1)
    return wnd->pos().y() ;
}
void ScriptAPI::move(QVariant wndId,int x,int y)
{
    getHtmlWnd()
    wnd->move(QPoint(x,y));
}
void ScriptAPI::regGlobalKeyEvent(QVariant wndId,QString keySqu)
{
    getHtmlWnd()
    QxtGlobalShortcut * sc = new QxtGlobalShortcut(QKeySequence(keySqu), this);
    connect(sc, SIGNAL(activated()),wnd, SLOT(keyEvent()));
}

bool ScriptAPI::startLocalServer(QVariant wndId,QString name)
{
    getHtmlWnd(false)
    return wnd->startLocalServer(name);
}

bool ScriptAPI::sendToLocalServer(QString name,QString data)
{
    QLocalSocket ls;
    ls.connectToServer(name);
    if(ls.waitForConnected())
    {
        QTextStream ts(&ls);
        ts << data ;
        ts.flush();
        ls.waitForBytesWritten();
        return true ;
    }
    else
    {
        return false ;
    }
}
void ScriptAPI::exit()
{
    QApplication::instance()->exit(0) ;
}


QVariant ScriptAPI::argvs()
{
    return QApplication::instance()->arguments() ;
}
