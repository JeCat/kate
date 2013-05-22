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

    //true �����������Ұ�����δ����
    if ((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonPress))
    {
        //��������־λ����
        leftMousePress = true;

        //��ȡ����
        origin = mouseEvent->pos();

        if (!rubberBand)
        {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, fullScreenLabel);
        }

        rubberBand->setGeometry(QRect(origin,QSize()));
        rubberBand->show();

        return true;
    }

    //true ���������²��϶�
    if ((mouseEvent->type() == QEvent::MouseMove)
        && (leftMousePress))
    {
        if (rubberBand)
        {
            rubberBand->setGeometry(QRect(origin, mouseEvent->pos()).normalized());
        }

        return true;
    }

    //�������ɿ�
    if ((mouseEvent->button() == Qt::LeftButton)
        && (mouseEvent->type() == QEvent::MouseButtonRelease))
    {
        //����־λ����
        leftMousePress = false;

        if (rubberBand)
        {
            //��ȡ��Ƥ������ֹ����
            termination = mouseEvent->pos();
            QRect rect = QRect(origin, termination);

            //������Ƥ����ȡȫ���ϵ���Ϣ�����������shotScreenLabel
            shotScreenLabel->setPixmap(fullScreenPixmap.grabWidget(fullScreenLabel,
                                                                   rect.x(),
                                                                   rect.y(),
                                                                   rect.width(),
                                                                   rect.height()));

            //��shotScreenLabel���û�����С�̶�Ϊ����ͼƬ��С
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
  descr��ʵ�����ؼ�
*/
void ScreenShoter::createWidgets()
{
    //����QLabel�ĸ��ؼ�����Ϊthis�������ͼ��Ϣ���������������У��޷���ȷ��ʾ
    fullScreenLabel = new QLabel();
    shotScreenLabel = new QLabel();

    rubberBand = new QRubberBand(QRubberBand::Rectangle, fullScreenLabel);

    leftMousePress = false;

    //��ʼ�����̿ؼ�����װ**************************************************************

    trayIcon = new QSystemTrayIcon(QIcon(tr(":/images/heart.svg")), this);
    menu = new QMenu(this);
    restore = new QAction(tr("Restore"), this);
    mini = new QAction(tr("Mini"), this);
    quit = new QAction(tr("Quit"), this);

    menu->addAction(restore);
    menu->addAction(mini);
    menu->addAction(quit);
    trayIcon->setContextMenu(menu);

    //��������ʾ
    trayIcon->show();

    //��ʼ�����̿ؼ�����װ**************************************************************

    savePixmap = new QAction(tr("����"), shotScreenLabel);

    shotScreenLabel->addAction(savePixmap);
    shotScreenLabel->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void ScreenShoter::createConnects()
{
    //�������źŲ�*****************************************************************

    connect(ui->pbtnShot, SIGNAL(clicked()), this, SLOT(grapWindowScreen()));
    connect(ui->pbtnShotAndMin, SIGNAL(clicked()), this, SLOT(miniWindows()));
    connect(ui->pbtnMin, SIGNAL(clicked()), this, SLOT(miniWindows()));

    connect(savePixmap, SIGNAL(triggered()), this, SLOT(saveShotPixmap()));

    //�������źŲ�*****************************************************************

    //�����źŲ�*******************************************************************

    connect(restore, SIGNAL(triggered()), this, SLOT(restoreWindows()));
    connect(mini, SIGNAL(triggered()), this, SLOT(miniWindows()));
    connect(quit, SIGNAL(triggered()), this, SLOT(quitApplication()));

    //�����źŲ�*******************************************************************
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

    //��ȡȫ����ͼfullScreenPixmap�����������fullScreenLabel
    fullScreenPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    fullScreenLabel->setPixmap(fullScreenPixmap);

    //labelȫ����ʾ
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
