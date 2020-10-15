#include "tasklistwindow.h"
#include "taskitemwindow.h"
#include "mainwindow.h"
#include <QScrollArea>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
TaskListWindow::TaskListWindow(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    QScrollArea* scrollArea = new QScrollArea();
    vboxItemContainer = new QVBoxLayout();
    QWidget *widget = new QWidget();

    widget->setLayout(vboxItemContainer);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widget);


    QVBoxLayout* scrollVbox = new QVBoxLayout();
    ui.widgetContainer->setLayout(scrollVbox);
    scrollVbox->addWidget(scrollArea);

    connect(ui.btnCreateTask, SIGNAL(clicked()), this, SLOT(createTaskEventFT()));

}

void TaskListWindow::createTaskEventFT(){

    MainWindow* pMain = (MainWindow*)MainWindow::findMainWindow();
    pMain->TransformPage(TASK_ADD);
}

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        QWidget* widget;
        if (  (deleteWidgets)
              && (widget = item->widget())  ) {
            delete widget;
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

void TaskListWindow::RefreshItems() {
    clearLayout(vboxItemContainer, true);
    MainWindow* pMain = (MainWindow*)MainWindow::findMainWindow();
    QString szToken ="Bearer " +  pMain->getToken();

    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QUrl url("https://api.quwi.com/v2/projects-manage/index");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", szToken.toLocal8Bit());
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    manager->get(request);
}


void TaskListWindow::appendItem(QJsonObject value) {
    QHBoxLayout *hbox = new QHBoxLayout();
    TaskItemWindow* taskitem = new TaskItemWindow();
    taskitem->setObject(value);
    taskitem->setFixedHeight(taskitem->height());
    taskitem->setFixedWidth(taskitem->width());
    hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding,  QSizePolicy::Fixed));
    hbox->addWidget(taskitem);
    hbox->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
    vboxItemContainer->addLayout(hbox);
}
void TaskListWindow::replyFinished(QNetworkReply *e) {
    QJsonDocument itemDoc = QJsonDocument::fromJson(e->readAll());
    QJsonObject itemObject = itemDoc.object();
    QJsonArray jsonArray = itemObject["projects"].toArray();

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        appendItem(obj);
    }
    vboxItemContainer->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding));

}

