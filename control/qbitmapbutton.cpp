#include "qbitmapbutton.h"
#include <QDebug>
#include <QEvent>
QBitmapButton::QBitmapButton() {

}

void QBitmapButton::setStyle(QString normal, QString over, QString down) {
    this->normal = normal;
    this->over = over;
    this->down = down;
    this->setStyleSheet(normal);
}
void QBitmapButton::mousePressEvent(QMouseEvent *e) {
    this->setStyleSheet(down);
}
void QBitmapButton::mouseReleaseEvent(QMouseEvent *e) {
    this->setStyleSheet(normal);
}
bool QBitmapButton::event(QEvent * e)
{

    switch(e->type())
    {
    case QEvent::HoverEnter:
        this->setStyleSheet(over);
        break;
    case QEvent::HoverMove:
        break;
    case QEvent::HoverLeave:
        this->setStyleSheet(normal);
        break;
    default:
        //this->setStyleSheet(normal);
        break;
    }
    return QWidget::event(e);
}

