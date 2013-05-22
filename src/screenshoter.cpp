#include "ScreenShoter.h"
#include "ui_screenshoter.h"
#include <QtGui>

ScreenShoter::ScreenShoter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenShoter)
{
    ui->setupUi(this);
    createWidgets();
    createConnects();
    createEventFilter();
}

ScreenShoter::~ScreenShoter()
{
    delete ui;

    delete quit;
    delete mini;
    delete restore;
    delete menu;
    delete trayIcon;

    delete fullScreenLabel;
    delete shotScreenLabel;
}

bool ScreenShoter::eventFilter(QObject *o, QEvent *e)
{
    if (o != fullScreenLabel)
    {
        return ScreenShoter::eventFilter(o, e);
    }

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (e);

    //true 鼠标左键按下且按键还未弹起
    if ((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonPress))
    {
        //鼠标左键标志位按下
        leftMousePress = true;

        //获取鼠标点
        origin = mouseEvent->pos();

        if (!rubberBand)
        {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, fullScreenLabel);
        }

        rubberBand->setGeometry(QRect(origin,QSize()));
        rubberBand->show();

        return true;
    }

    //true 鼠标左键按下并拖动
    if ((mouseEvent->type() == QEvent::MouseMove)
        && (leftMousePress))
    {
        if (rubberBand)
        {
            rubberBand->setGeometry(QRect(origin, mouseEvent->pos()).normalized());
        }

        return true;
    }

    //鼠标左键松开
    if ((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonRelease))
    {
        //鼠标标志位弹起
        leftMousePress = false;

        if (rubberBand)
        {
            //获取橡皮筋框的终止坐标
            termination = mouseEvent->pos();
            QRect rect = QRect(origin, termination);

            //根据橡皮筋框截取全屏上的信息，并将其放入shotScreenLabel
            shotScreenLabel->setPixmap(fullScreenPixmap.grabWidget(fullScreenLabel,
                                                                   rect.x(),
                                                                   rect.y(),
                                                                   rect.width(),
                                                                   rect.height()));

            //将shotScreenLabel的用户区大小固定为所截图片大小
            shotScreenLabel->setFixedSize(rect.width(), rect.height());
            // shotScreenLabel->show();

            rubberBand->hide();
            fullScreenLabel->hide();


            saveShotPixmap() ;
        }

        return true;
    }

    return false;
}

/**
  descr：实例化控件
*/
void ScreenShoter::createWidgets()
{
    //两个QLabel的父控件不能为this，否则截图信息会现在是主窗口中，无法正确显示
    fullScreenLabel = new QLabel();
    shotScreenLabel = new QLabel();

    rubberBand = new QRubberBand(QRubberBand::Rectangle, fullScreenLabel);

    leftMousePress = false;

    //初始化托盘控件并组装**************************************************************

    trayIcon = new QSystemTrayIcon(QIcon(tr(":/images/heart.svg")), this);
    menu = new QMenu(this);
    restore = new QAction(tr("Restore"), this);
    mini = new QAction(tr("Mini"), this);
    quit = new QAction(tr("Quit"), this);

    menu->addAction(restore);
    menu->addAction(mini);
    menu->addAction(quit);
    trayIcon->setContextMenu(menu);

    //将托盘显示
    trayIcon->show();

    //初始化托盘控件并组装**************************************************************

    savePixmap = new QAction(tr("保存"), shotScreenLabel);

    shotScreenLabel->addAction(savePixmap);
    shotScreenLabel->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void ScreenShoter::createConnects()
{
    //主窗口信号槽*****************************************************************

    connect(ui->pbtnShot, SIGNAL(clicked()), this, SLOT(grapWindowScreen()));
    connect(ui->pbtnShotAndMin, SIGNAL(clicked()), this, SLOT(miniWindows()));
    connect(ui->pbtnMin, SIGNAL(clicked()), this, SLOT(miniWindows()));

    connect(savePixmap, SIGNAL(triggered()), this, SLOT(saveShotPixmap()));

    //主窗口信号槽*****************************************************************

    //托盘信号槽*******************************************************************

    connect(restore, SIGNAL(triggered()), this, SLOT(restoreWindows()));
    connect(mini, SIGNAL(triggered()), this, SLOT(miniWindows()));
    connect(quit, SIGNAL(triggered()), this, SLOT(quitApplication()));

    //托盘信号槽*******************************************************************
}

void ScreenShoter::createEventFilter()
{
    fullScreenLabel->installEventFilter(this);
}

QString ScreenShoter::getSaveShotPixmap()
{
    return QFileDialog::getSaveFileName(shotScreenLabel,
                                        tr("Open Image"),
                                        ".",
                                        tr("Image Files(*.JPG *.PNG)"));
}

void ScreenShoter::grapWindowScreen()
{
    if (!fullScreenLabel)
    {
        fullScreenLabel = new QLabel();
    }

    //获取全屏截图fullScreenPixmap，并将其放入fullScreenLabel
    fullScreenPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    fullScreenLabel->setPixmap(fullScreenPixmap);

    //label全屏显示
    fullScreenLabel->showFullScreen();
}

void ScreenShoter::miniWindows()
{
    showMinimized();
    grapWindowScreen();
}

void ScreenShoter::restoreWindows()
{
    showNormal();
}

void ScreenShoter::quitApplication()
{
    qApp->quit();
}

void ScreenShoter::saveShotPixmap()
{
    QString fileName = getSaveShotPixmap();

    if (!fileName.isNull())
    {
        fullScreenPixmap.save(fileName);
    }

}
