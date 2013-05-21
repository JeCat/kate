#ifndef SCRIPTAPI_H
#define SCRIPTAPI_H

#include <QObject>
#include <QWebFrame>

class HtmlWindow ;

class ScriptAPI : public QObject
{
    Q_OBJECT

public:
    ScriptAPI(QList<HtmlWindow*> *) ;

    void setupWebkitScript(HtmlWindow*,QWebFrame *) ;

public slots:
    void require(QString) ;
    QVariant createWindow(QVariant) ;
    void show(QVariant wndId) ;
    void hide(QVariant wndId) ;

    void resize(QVariant wndId,int w,int h) ;
    QVariant width(QVariant wndId) ;
    QVariant height(QVariant wndId) ;
    void setWindowFlags(QVariant wndId,int) ;
    QVariant windowFlags(QVariant wndId) ;
    void inspector(QVariant wndId) ;
    QVariant eval(QVariant wndId,QString) ;

private:
    QList<HtmlWindow*> * m_pWindowPool ;
};

#include "../htmlwindow.h"

#endif // SCRIPTAPI_H
