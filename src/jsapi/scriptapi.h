#ifndef SCRIPTAPI_H
#define SCRIPTAPI_H

#include <QObject>
#include <QWebFrame>
#include "screenshoter.h"
#include <Windows.h>


class HtmlWindow ;

class ScriptAPI : public QObject
{
    Q_OBJECT

private:
    HtmlWindow * draggingWindow ;
    QPoint preMousePos ;

public:
    ScriptAPI() ;
    ~ScriptAPI() ;

    void setupWebkitScript(HtmlWindow*,QWebFrame *) ;
    HtmlWindow * htmlWindow(int wndId) ;

    void onMouseMoving(int x,int y) ;
    void onMouseUp() ;

public slots:
    void require(QString) ;
    QVariant createWindow(QVariant,int parentWndId=-1) ;
    void show(QVariant wndId) ;
    void hide(QVariant wndId) ;
    void close(QVariant wndId) ;
    void minimize(QVariant wndId) ;
    void maximize(QVariant wndId) ;
    void normal(QVariant wndId) ;

    QVariant argvs() ;
    void exit() ;

    void resize(QVariant wndId,int w,int h) ;
    QVariant width(QVariant wndId) ;
    QVariant height(QVariant wndId) ;
    void setWindowFlags(QVariant wndId,int) ;
    QVariant windowFlags(QVariant wndId) ;
    void inspector(QVariant wndId) ;
    QVariant eval(QVariant wndId,QString) ;
    void shotScreen() ;
    void setTitle(QVariant wndId,QString) ;
    QVariant title(QVariant wndId) ;
    void playSound(QString) ;
    int wndPosX(QVariant wndId) ;
    int wndPosY(QVariant wndId) ;
    void move(QVariant wndId,int x,int y) ;

    void regGlobalKeyEvent(QVariant,QString) ;

    void drag(QVariant wndId) ;

    bool startLocalServer(QVariant,QString) ;
    bool sendToLocalServer(QString,QString) ;

private:
    QList<HtmlWindow*> * m_pWindowPool ;
    ScreenShoter * screenshoter ;
};

#include "../htmlwindow.h"

#endif // SCRIPTAPI_H
