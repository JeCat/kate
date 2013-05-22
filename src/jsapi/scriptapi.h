#ifndef SCRIPTAPI_H
#define SCRIPTAPI_H

#include <QObject>
#include <QWebFrame>
#include "screenshoter.h"


class HtmlWindow ;

class ScriptAPI : public QObject
{
    Q_OBJECT

public:
    ScriptAPI() ;
    ~ScriptAPI() ;

    void setupWebkitScript(HtmlWindow*,QWebFrame *) ;

public slots:
    void require(QString) ;
    QVariant createWindow(QVariant,int parentWndId=-1) ;
    void show(QVariant wndId) ;
    void hide(QVariant wndId) ;

    void resize(QVariant wndId,int w,int h) ;
    QVariant width(QVariant wndId) ;
    QVariant height(QVariant wndId) ;
    void setWindowFlags(QVariant wndId,int) ;
    QVariant windowFlags(QVariant wndId) ;
    void inspector(QVariant wndId) ;
    QVariant eval(QVariant wndId,QString) ;
    void shotScreen() ;



private:
    QList<HtmlWindow*> * m_pWindowPool ;
    ScreenShoter * screenshoter ;
};

#include "../htmlwindow.h"

#endif // SCRIPTAPI_H
