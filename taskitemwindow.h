#ifndef TASKITEMWINDOW_H
#define TASKITEMWINDOW_H

#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include "ui_TaskItem.h"
#include "mainwindow.h"
#include "baseview.h"
#include "photowidget.h"
class TaskItemWindow: public BaseView
{
    Q_OBJECT
public:
    explicit TaskItemWindow(QWidget *parent = nullptr);
private slots:

protected:
     bool eventFilter(QObject* object, QEvent* event) override;
private:
    Ui::TaskItemWindow ui;

public:
    QJsonObject projectInfo;
    QString m_szProjectID;
    PhotoWidget *m_photoWidget;
public:
    void setObject(QJsonObject obj);
};

#endif // TASKITEMWINDOW_H
