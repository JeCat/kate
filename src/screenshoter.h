#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPoint>

class QSystemTrayIcon;
class QMenu;
class QAction;
class QRubberBand;
class QLabel;

namespace Ui {
    class ScreenShoter;
}

class ScreenShoter : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenShoter(QWidget *parent = 0);
    ~ScreenShoter();

public slots:
    /**
      descr：截取全屏
    */
    void grapWindowScreen();
protected:
    virtual bool eventFilter(QObject *o, QEvent *e);

private:
    /**
      descr：实例化控件
    */
    void createWidgets();
    void createConnects();
    void createEventFilter();

    QString getSaveShotPixmap();

private slots:

    /**
      descr：将主窗口最小化
    */
    void miniWindows();

    /**
      descr：将主窗口恢复
    */
    void restoreWindows();

    /**
      descr：退出程序
    */
    void quitApplication();

    void saveShotPixmap();

private:
    Ui::ScreenShoter *ui;

    //托盘所有控件***************************************************************
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QAction *restore;
    QAction *mini;
    QAction *quit;
    //托盘所有控件***************************************************************

    //存放全屏截图和用户选择截图的控件
    QLabel *fullScreenLabel;
    QLabel *shotScreenLabel;

    //用户截图后点击鼠标右键的上下文，用以保存截图
    QAction *savePixmap;

    //橡皮筋框
    QRubberBand *rubberBand;

    //用户选择的初始坐标和终止坐标
    QPoint origin;
    QPoint termination;

    //用户点击截屏按钮时截取的全屏信息
    QPixmap fullScreenPixmap;

    //鼠标左键按下标志位
    bool leftMousePress;
};

#endif // WIDGET_H
