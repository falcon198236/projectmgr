#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwidnow.h"
#include "taskinfowindow.h"
#include "tasklistwindow.h"
MainWindow *g_mainWindow = NULL;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    g_mainWindow = this;
    LoginWindow loginWindow;
    if(loginWindow.exec() != QDialog::Accepted){

        exit(0);
    }
    szToken = loginWindow.szToken;
    m_currentWidget = NULL;

    taskPageControl = new TaskPageControl(this);
    ui->setupUi(this);
    initializeEvent();

    setWindowTitle("QUWI");
    TransformPage(TASK_LIST);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeEvent() {
    connect(ui->btnMenuTaskList, SIGNAL(clicked()), this, SLOT(btnMenuTaskList_Clicked()));
}

void MainWindow::btnMenuTaskList_Clicked()
{
    TransformPage(TASK_LIST);
}
QMainWindow* MainWindow::findMainWindow() {
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        QMainWindow* pMainWnd = qobject_cast<QMainWindow*>(pWidget);
        if (pMainWnd)
           return pMainWnd;
    }
    return nullptr;
}
void MainWindow::TransformPage(PAGEINFO PageInfo, QString param) {

    if(m_currentWidget != NULL) {
       ui->pageLayoutContainer->removeWidget(m_currentWidget);
       delete m_currentWidget;
       m_currentWidget = NULL;
    }
    switch(PageInfo) {
    case TASK_LIST:
        {
            TaskListWindow *widget = new TaskListWindow();
            ui->pageLayoutContainer->addWidget(widget);
            m_currentWidget = widget;
            widget->RefreshItems();
        }
        break;
    case TASK_ADD:
        {
            TaskInfoWindow *widget = new TaskInfoWindow();
            widget->setObject(param);
            ui->pageLayoutContainer->addWidget(widget);
            m_currentWidget = widget;
        }
        break;
    case TASK_EDIT:
        {
            TaskInfoWindow *widget = new TaskInfoWindow();
            widget->setObject(param);
            ui->pageLayoutContainer->addWidget(widget);

            m_currentWidget = widget;
        }
        break;
    }
}

