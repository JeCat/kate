#include "scriptapi.h"
#include <QWebView>
#include <QDebug>
#include <QWebInspector>
#include <QFile>
#include <QApplication>

ScriptAPI::ScriptAPI(QList<HtmlWindow*> * pWindowPool)
    : QObject()
    , m_pWindowPool(pWindowPool)
{}

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
    frame->evaluateJavaScript(QString("kateapi.appFolder = \"%1\";").arg(appFolder)) ;

    loadscript(folder+"/../asserts/kate.js") ;
}


QVariant ScriptAPI::createWindow(QVariant url)
{
    qDebug() << "create html window by url :" << url.toString() ;

    HtmlWindow * wnd = new HtmlWindow(url.toString(),this,m_pWindowPool->length()) ;
    m_pWindowPool->append(wnd) ;

    return QVariant(wnd->id) ;
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

#define getHtmlWnd(ret) \
    int nWndId = wndId.toInt() ; \
    if( nWndId>=m_pWindowPool->length() ) \
    {\
        return ret;\
    }\
    HtmlWindow * wnd = m_pWindowPool->at(nWndId) ;\


void ScriptAPI::show(QVariant wndId)
{
    getHtmlWnd()
    wnd->show() ;
}

void ScriptAPI::hide(QVariant wndId)
{
    getHtmlWnd()
    wnd->hide() ;
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
