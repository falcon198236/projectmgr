#include "photowidget.h"
#include <QStyleOption>
#include <QRegion>
PhotoWidget::PhotoWidget(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("border-radius:25px;");
}

void PhotoWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    int w, h;
    w = this->width();
    h = this->height();
    QRegion rng (QRect(0,0,w,h), QRegion::Ellipse);
    painter.setClipRegion(rng);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    if(!m_pixPhoto.isNull()) {
        painter.drawPixmap(0,0, m_pixPhoto);
    }else {
        painter.drawEllipse(1,1, w-1,h-1);
    }



}
