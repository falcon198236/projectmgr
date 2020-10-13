#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "taskinfowindow.h"

TaskInfoWindow::TaskInfoWindow(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(btnBackEventFT()));
}

void TaskInfoWindow::btnBackEventFT() {
    MainWindow* pMain = (MainWindow*)MainWindow::findMainWindow();
    pMain->TransformPage(TASK_LIST);
}


void TaskInfoWindow::setObject(QString id) {
    if(id == "") return;
    m_szProjectID = id;
    MainWindow* pMain = (MainWindow*)MainWindow::findMainWindow();
    QString szToken ="Bearer " +  pMain->getToken();

    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QUrl url("https://api.quwi.com/v2/projects-manage/" + m_szProjectID);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", szToken.toLocal8Bit());
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    manager->get(request);
}

void TaskInfoWindow::replyFinished(QNetworkReply *e) {
    QJsonDocument itemDoc = QJsonDocument::fromJson(e->readAll());
    QJsonObject itemObject = itemDoc.object();
    QJsonObject obj = itemObject["project"].toObject();

    ui.edName->setText(obj["name"].toString());
    if(obj["is_active"].toInt() ==  1) ui.chkActive->setChecked(true);
    else ui.chkActive->setChecked(false);

    if(obj["is_owner_watcher"].toInt() ==  1) ui.chkWatcher->setChecked(true);
    else ui.chkWatcher->setChecked(false);



}


