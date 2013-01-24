#include "htmlwindow.h"
#include "ui_htmlwindow.h"
#include <QWebSettings>
#include <QWebFrame>
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QMetaObject>
#include <QDebug>


HtmlWindow::HtmlWindow()
    : QDialog()
    , ui(new Ui::HtmlWindow)
{
    ui->setupUi(this) ;


    //WebPage * pWebPage = new WebPage(this) ;
    //ui->webView->setPage(pWebPage) ;

    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);

    // -------------------------------------------------
    QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
    QString location = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    qDebug() << location ;
    diskCache->setCacheDirectory(location);
    ui->webView->page()->networkAccessManager()->setCache(diskCache);

    // -------------------------------------------------
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks) ;
    // connect(ui->webView->page(), SIGNAL(linkClicked(const QUrl &)), this, SLOT(OnLinkClick(const QUrl &)));


    connect(ui->webView, SIGNAL(loadStarted ()), SLOT(onLoadStarted()));
    connect(ui->webView, SIGNAL(loadFinished (bool)), SLOT(onLoadFinished(bool)));
    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(onPopulateScriptObject()));
}

HtmlWindow::~HtmlWindow()
{
    delete ui;
}

void HtmlWindow::resize(int w,int h)
{
    QDialog::resize(w,h) ;
}

void HtmlWindow::resizeEvent ( QResizeEvent * e)
{
    // webkit
    ui->webView->move(0,0) ;
    ui->webView->resize( width(),height() ) ;

    QWidget::resizeEvent(e) ;
}

void HtmlWindow::onPopulateScriptObject()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("_OS", this);
}
