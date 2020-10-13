#include "loginwidnow.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include "control/qbitmapbutton.h"
LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    ui.lineeditEmail->setText("falcon198236@gmail.com"); //this is my email.
}


void LoginWindow::on_btnLogin_clicked()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QUrl url("https://api.quwi.com/v2/auth/login");
    QNetworkRequest request(url);

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Client-Timezone-Offset", "60");
    request.setRawHeader("Client-Language", "ru-RU");
    request.setRawHeader("Client-Company", "udimiteam");
    request.setRawHeader("Client-Device", "desktop");

    QJsonObject object;
    object["email"] = ui.lineeditEmail->text();
    object["password"] = ui.lineeditPassword->text();

    QJsonDocument resultJson;
    resultJson.setObject(object);
    QByteArray byteArray = resultJson.toJson();

    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    manager->post(request, byteArray);
}

void LoginWindow::replyFinished(QNetworkReply *e) {
    //qDebug() << e->readAll();
    QJsonDocument itemDoc = QJsonDocument::fromJson(e->readAll());
    QJsonObject itemObject = itemDoc.object();
    //qDebug() << itemObject["token"];
    if(itemObject["token"].isNull()) {
        QMessageBox msgBox;
        msgBox.setText("please input the correct email or password.");
        msgBox.exec();
        ui.lineeditEmail->focusWidget();
    }else {
        szToken = itemObject["token"].toString();
        this->accept();
    }
}
