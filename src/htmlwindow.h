#ifndef HTMLWINDOW_H
#define HTMLWINDOW_H

#include <QDialog>
#include <QWebView>

namespace Ui {
    class HtmlWindow;
}

class HtmlWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit HtmlWindow();
    ~HtmlWindow();

    void resizeEvent ( QResizeEvent * e) ;

public slots:
    void resize(int w,int h) ;
    void onPopulateScriptObject() ;

private:
    Ui::HtmlWindow *ui;
};

#endif // HTMLWINDOW_H
