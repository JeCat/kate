#include <QFile>
#include <QMainWindow>
#include <QAction>
#include "kateengine.h"
#include "jsapi/qtwidgets.cpp"

KateEngine::KateEngine(QObject *parent) :
    QScriptEngine(parent)
{}


void KateEngine::init()
{
    qDebug() << __FILE__ << ": line " << __LINE__ ;

    // 控制台
    debugger.attachTo(this);
    debugger.standardWindow()->resize(1024, 640);
    debugger.action(QScriptEngineDebugger::InterruptAction)->trigger();

    // bingding native classes
    importQtWidgets(this);
}

void KateEngine::launch(QString fileName)
{
    qDebug() << __FILE__ << ": line " << __LINE__ ;

    QFile scriptFile(fileName);

    scriptFile.open(QIODevice::ReadOnly);
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();

    // 执行
    evaluate(contents,fileName) ;
}
