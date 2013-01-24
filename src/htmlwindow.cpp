#include "htmlwindow.h"
#include "ui_htmlwindow.h"
#include <QWebSettings>
#include <QWebFrame>
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QMetaObject>
#include <QApplication>
#include <QDebug>


HtmlWindow::HtmlWindow(QString appUrl)
    : QWidget()
    , ui(new Ui::HtmlWindow)
    , m_scriptAPI(new ScriptAPI(this))
    , m_appUrl(appUrl)
{
    qDebug() << appUrl ;

    ui->setupUi(this) ;

    // webkit settings
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);

    // cache dir -------------------------------------------------
    QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
    QString location = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    diskCache->setCacheDirectory(location);
    ui->webView->page()->networkAccessManager()->setCache(diskCache);

    // webkit events -------------------------------------------------
    connect(ui->webView->page()->mainFrame(), SIGNAL(loadFinished(bool)), SLOT(onLoadFinished(bool)));

    // load a blank page for app
    ui->webView->load(QUrl(QApplication::instance()->applicationDirPath()+"/../apps/blank.html")) ;
}

HtmlWindow::~HtmlWindow()
{
    delete ui;
    delete m_scriptAPI;
}

void HtmlWindow::resize(int w,int h)
{
    QWidget::resize(w,h) ;
}

void HtmlWindow::setWindowFlags(int flag)
{
    return QWidget::setWindowFlags((Qt::WindowFlags)flag) ;
}

int HtmlWindow::windowFlags()
{
    return (int)QWidget::windowFlags() ;
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

void HtmlWindow::onLoadFinished(bool suc){
    qDebug() << "OnLoadFinished " << suc ;

    QWebFrame * frame = (QWebFrame *)sender() ;

    // setup kate api
    m_scriptAPI->setupWebkitScript(frame) ;

    // load framework script
    m_scriptAPI->require(QApplication::instance()->applicationDirPath()+"/../apps/framework/waf.js");

    // execute app script
    m_scriptAPI->require(m_appUrl) ;
}

