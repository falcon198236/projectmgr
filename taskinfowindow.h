#ifndef TASKINFOWINDOW_H
#define TASKINFOWINDOW_H

#include <QObject>
#include <QWidget>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "ui_taskInfowindow.h"
#include "baseview.h"
#include "photowidget.h"
class TaskInfoWindow: public QWidget
{
    Q_OBJECT
public:
    explicit TaskInfoWindow(QWidget *parent = nullptr);
private slots:
    void btnBackEventFT();
    void replyFinished(QNetworkReply *e);
private:
    Ui::TaskInfoWindow ui;

public :
    QString m_szProjectID;
    PhotoWidget *m_photoWidget;
public:
    void setObject(QString id);
};

#endif // TASKINFOWINDOW_H
