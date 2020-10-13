#ifndef TASKLISTWINDOW_H
#define TASKLISTWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "baseview.h"
#include "ui_tasklist.h"

class TaskListWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListWindow(QWidget *parent = nullptr);

private slots:
    void createTaskEventFT();
    void replyFinished(QNetworkReply *e);
private:
    Ui::TaskListWindow ui;
public:
    QVBoxLayout *vboxItemContainer;
public:
    void RefreshItems();
    void appendItem(QJsonObject value);
};

#endif // TASKLISTWINDOW_H
