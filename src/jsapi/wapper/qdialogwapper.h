//.h文件
#ifndef QDialogWapper_H
#define QDialogWapper_H

#include <QDialog>
#include <QHBoxLayout>

class QDialogWapper : public QDialog
{
    Q_OBJECT

public:
    QDialogWapper(QWidget *parent=0) ;

public Q_SLOTS:
    void setLayout(QHBoxLayout *);


private:

};

#endif // QDialogWapper_H
