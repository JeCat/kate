#ifndef KATEENGINE_H
#define KATEENGINE_H

#include <QScriptEngine>
#include <QScriptEngineDebugger>

class KateEngine : public QScriptEngine
{
    Q_OBJECT
public:
    explicit KateEngine(QObject *parent = 0);

    void init() ;
    void launch(QString fileName) ;
    
signals:
    
public slots:


private:
    QScriptEngineDebugger debugger;
    
};

#endif // KATEENGINE_H
