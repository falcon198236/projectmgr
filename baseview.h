#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QObject>
#include <QWidget>
#include "mainwindow.h"
class BaseView : public QWidget
{
    Q_OBJECT
public:
    explicit BaseView(QWidget *parent = nullptr);

signals:
public:
    QMainWindow* findMainWindow();

};

#endif // BASEVIEW_H
