#ifndef SCRIPTAPI_H
#define SCRIPTAPI_H

#include <QObject>
#include <QWebFrame>

class HtmlWindow ;

class ScriptAPI : public QObject
{
    Q_OBJECT

public:
    ScriptAPI(HtmlWindow * window) ;

    void setupWebkitScript(QWebFrame *) ;

public slots:
    void require(QString) ;

private:
    HtmlWindow* m_window ;
};

#include "../htmlwindow.h"

#endif // SCRIPTAPI_H
