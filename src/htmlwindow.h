#ifndef HTMLWINDOW_H
#define HTMLWINDOW_H

#include <QWidget>
#include <QWebView>
#include <QWebInspector>
#include "jsapi/scriptapi.h"

namespace Ui {
    class HtmlWindow;
}

class HtmlWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit HtmlWindow(QString,ScriptAPI*,int);
    ~HtmlWindow();

    void resizeEvent ( QResizeEvent * e) ;
    QWebView* webView() ;
    int id ;
    QWebFrame* mainFrame() ;
    QWebInspector*inspector() ;

public slots:
    void onLoadFinished(bool) ;

private:
    Ui::HtmlWindow *ui;
    QString m_appUrl ;
    ScriptAPI* m_api ;
    QWebInspector * m_inspector ;
};



#endif // HTMLWINDOW_H
