#include "htmlwindow.h"
#include "ui_htmlwindow.h"
#include <QWebSettings>
#include <QWebFrame>
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QMetaObject>
#include <QApplication>
#include <QDebug>
#include "qxtglobalshortcut.h"
#include "networkcookiejar.h"

HtmlWindow::HtmlWindow(QString appUrl,ScriptAPI*api,int id)
    : QWidget()
    , ui(new Ui::HtmlWindow)
    , m_appUrl(appUrl)
    , m_api(api)
    , id(id)
    , m_inspector(NULL)
    , parentId(-1)
{
    qDebug() << appUrl ;

    ui->setupUi(this) ;

    // webkit settings
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    ui->webView->settings()->setAttribute(QWebSettings::XSSAuditingEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
    ui->webView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::LocalStorageEnabled,true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard,true);

    // cache dir -------------------------------------------------
    QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
    QString location = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    diskCache->setCacheDirectory(location);
    ui->webView->page()->networkAccessManager()->setCache(diskCache);

    // webkit events -------------------------------------------------
    connect(mainFrame(), SIGNAL(loadFinished(bool)), SLOT(onLoadFinished(bool)));

    // load a blank page for app
    ui->webView->load(QUrl(appUrl)) ;

    // CookieJar
    ui->webView->page()->networkAccessManager()->setCookieJar(NetworkCookieJar::instance()) ;

}

HtmlWindow::~HtmlWindow()
{
    delete ui;
}

void HtmlWindow::onLoadFinished(bool suc){
    qDebug() << "OnLoadFinished " << suc ;
    QWebFrame * frame = (QWebFrame *)sender() ;
    m_api->setupWebkitScript(this,frame) ;
}

void HtmlWindow::resizeEvent ( QResizeEvent * e)
{
    // webkit
    ui->webView->move(0,0) ;
    ui->webView->resize( width(),height() ) ;

    QWidget::resizeEvent(e) ;
}

QWebView* HtmlWindow::webView()
{
    return ui->webView ;
}

QWebFrame* HtmlWindow::mainFrame()
{
    return ui->webView->page()->mainFrame() ;
}

QWebInspector* HtmlWindow::inspector()
{
    if(!m_inspector)
    {
        m_inspector = new QWebInspector;
        m_inspector->setPage(webView()->page());
        m_inspector->show() ;
    }
    return m_inspector ;
}


void HtmlWindow::keyEvent()
{// kate.window.regGlobalKeyEvent("CTRL+ALT+A") ;
    QString code = QString("onKateGlobalKeyEvent(\"%1\")")
            .arg( ((QxtGlobalShortcut*)sender())->shortcut().toString() ) ;
    qDebug() << code ;
    mainFrame()->evaluateJavaScript(code) ;
}

