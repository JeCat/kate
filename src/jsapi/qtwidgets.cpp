#include <QtScript>
#include <QScriptEngine>
#include "wapper/qdialogwapper.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWebView>
#include <QWebFrame>


Q_SCRIPT_DECLARE_QMETAOBJECT(QWidget, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QDialogWapper, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QHBoxLayout, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QVBoxLayout, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QWebView, QWidget*)



void importQtWidgets(QScriptEngine * engine){

    engine->globalObject().setProperty("QHBoxLayout", engine->scriptValueFromQMetaObject<QHBoxLayout>()) ;
    engine->globalObject().setProperty("QVBoxLayout", engine->scriptValueFromQMetaObject<QVBoxLayout>()) ;
    engine->globalObject().setProperty("QWidget", engine->scriptValueFromQMetaObject<QWidget>()) ;
    engine->globalObject().setProperty("QDialog", engine->scriptValueFromQMetaObject<QDialogWapper>()) ;
    engine->globalObject().setProperty("QWebView", engine->scriptValueFromQMetaObject<QWebView>()) ;

}

