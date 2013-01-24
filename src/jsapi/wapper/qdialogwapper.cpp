#include "qdialogwapper.h"
#include <QLayout>

QDialogWapper::QDialogWapper(QWidget * parent)
    :QDialog(parent){}

void QDialogWapper::setLayout(QHBoxLayout * layout)
{
    QDialog::setLayout((QLayout *)layout) ;
}
