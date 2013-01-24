#ifndef HTMLWINDOW_H
#define HTMLWINDOW_H

#include <QWidget>
#include <QWebView>

namespace Ui {
    class HtmlWindow;
}

#include "jsapi/scriptapi.h"

class HtmlWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit HtmlWindow(QString);
    ~HtmlWindow();

    void resizeEvent ( QResizeEvent * e) ;
    QWebView* webView() ;

public slots:
    void resize(int w,int h) ;
    void setWindowFlags(int) ;
    int windowFlags() ;
    void onLoadFinished(bool) ;

private:
    Ui::HtmlWindow *ui;
    ScriptAPI * m_scriptAPI ;
    QString m_appUrl ;
};

#endif // HTMLWINDOW_H
