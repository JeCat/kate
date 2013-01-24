#include "scriptapi.h"
#include <QWebView>
#include <QDebug>

ScriptAPI::ScriptAPI(HtmlWindow* window)
    : QObject()
    , m_window(window)
{}


void ScriptAPI::setupWebkitScript(QWebFrame * frame)
{
    qDebug() << "setupWebkitScript" ;

    frame->addToJavaScriptWindowObject("kate",this) ;
    frame->addToJavaScriptWindowObject("__kate_htmlWindow",this->m_window) ;
    frame->addToJavaScriptWindowObject("__kate_htmlView",this->m_window->webView()) ;

    frame->evaluateJavaScript("kate.window = __kate_htmlWindow ;") ;
    frame->evaluateJavaScript("kate.window.view = __kate_htmlView ;") ;
}

void ScriptAPI::require(QString url)
{
    QString code = "(function (){var node = document.createElement('script') ; node.src = '"
            + url
            + "' ; document.head.appendChild(node) ;})()" ;
    m_window->webView()->page()->mainFrame()->evaluateJavaScript(code) ;
}
