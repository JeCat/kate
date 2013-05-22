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
      descr����ȡȫ��
    */
    void grapWindowScreen();
protected:
    virtual bool eventFilter(QObject *o, QEvent *e);

private:
    /**
      descr��ʵ�����ؼ�
    */
    void createWidgets();
    void createConnects();
    void createEventFilter();

    QString getSaveShotPixmap();

private slots:

    /**
      descr������������С��
    */
    void miniWindows();

    /**
      descr���������ڻָ�
    */
    void restoreWindows();

    /**
      descr���˳�����
    */
    void quitApplication();

    void saveShotPixmap();

private:
    Ui::ScreenShoter *ui;

    //�������пؼ�***************************************************************
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QAction *restore;
    QAction *mini;
    QAction *quit;
    //�������пؼ�***************************************************************

    //���ȫ����ͼ���û�ѡ���ͼ�Ŀؼ�
    QLabel *fullScreenLabel;
    QLabel *shotScreenLabel;

    //�û���ͼ��������Ҽ��������ģ����Ա����ͼ
    QAction *savePixmap;

    //��Ƥ���
    QRubberBand *rubberBand;

    //�û�ѡ��ĳ�ʼ�������ֹ����
    QPoint origin;
    QPoint termination;

    //�û����������ťʱ��ȡ��ȫ����Ϣ
    QPixmap fullScreenPixmap;

    //���������±�־λ
    bool leftMousePress;
};

#endif // WIDGET_H
