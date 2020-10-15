#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "taskinfowindow.h"

TaskInfoWindow::TaskInfoWindow(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    m_photoWidget = new PhotoWidget(ui.widget_3);
    m_photoWidget->setGeometry(360, 20, 100,100);
    QPushButton *btnRemovePhoto = new QPushButton(ui.widget_3);
    btnRemovePhoto->setStyleSheet("QPushButton\
                                        {\
                                            background-color:#888888;\
                                            border-radius: 10px;\
                                            image: url(:/Images/images/icon_07.png);\
                                        }\
                                QPushButton:hover \
                                        {\
                                            background-color:#000000;\
                                            border:1px solid #ffffff;\
                                    }");
    btnRemovePhoto->setGeometry(440, 25, 25,25);
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


    QUrl url(obj["logo_url"].toString());
    QNetworkAccessManager* netAccManager = new QNetworkAccessManager;
    QNetworkRequest request(QUrl(obj["logo_url"].toString()));
    QNetworkReply *reply = netAccManager->get(request);
    QEventLoop loop;
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    QByteArray bytes = reply->readAll();
    QImage img;
    img.loadFromData(bytes);
    QPixmap pix = QPixmap::fromImage(img).scaled(100,100, Qt::KeepAspectRatio);
    m_photoWidget->setPixmap(pix);

}


