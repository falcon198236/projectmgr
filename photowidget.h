#ifndef PHOTOWIDGET_H
#define PHOTOWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
class PhotoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event);
signals:

public:
    QPixmap m_pixPhoto;
public:
    void setPixmap(QPixmap pix) {m_pixPhoto = pix; this->update();}
};

#endif // PHOTOWIDGET_H
