#include "taskitemwindow.h"
#include <QEvent>
#include <QPixmap>
#include <QJsonArray>
#include <QDebug>
TaskItemWindow::TaskItemWindow(QWidget *parent) : BaseView(parent)
{
    installEventFilter(this);
    ui.setupUi(this);

    m_photoWidget = new PhotoWidget(this);
    m_photoWidget->setGeometry(60,15, 50,50);
    m_photoWidget->setStyleSheet("border-radius:25px;");
    this->setAttribute(Qt::WA_Hover, true);
}
bool TaskItemWindow::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::HoverEnter) {
        ui.widgetBackground->setStyleSheet("QWidget {background-color:#cccccc; \
                                                    border:1px solid #BBBBBB;\
                                                    border-radius:10px;}");
    }else if(event->type() == QEvent::HoverLeave) {
        ui.widgetBackground->setStyleSheet("QWidget {background-color:#ffffff; \
                                                border:1px solid #BBBBBB;\
                                                border-radius:10px;}");
    }else if(event->type() == QEvent::MouseButtonRelease) {
        MainWindow* pMain = (MainWindow*)MainWindow::findMainWindow();
        pMain->TransformPage(TASK_EDIT, m_szProjectID);
        return true;
    }
    return QWidget::eventFilter( object, event );
}


void TaskItemWindow::setObject(QJsonObject obj) {
    m_szProjectID.sprintf("%d", obj["id"].toInt());
    ui.lblProjectName->setText(obj["name"].toString());
    QJsonArray users = obj["users"].toArray();

    QString sz;
    if(users.count() == 0) sz = "No workers";
    else sz.sprintf("%d Workers", users.count());
    ui.lblWorkers->setText(sz);
    //ui.lblPhoto->setPixmap(new QPixmap(obj["logo_url"].toString()));
    if(obj["is_active"].toInt() == 1) {
        ui.lblActive->setText("Active");
    }else {
        ui.lblActive->setText( "None Active");
    }
    qDebug() << obj["logo_url"].toString();
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
    QPixmap pix = QPixmap::fromImage(img).scaled(50,50, Qt::KeepAspectRatio);
    m_photoWidget->setPixmap(pix);
    //ui.lblPhoto->setPixmap(pix);

}




