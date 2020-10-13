#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tasklistwindow.h"
#include "taskpagecontrol.h"
#include "taskinfowindow.h"
#include <QJsonObject>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum PAGEINFO {
    TASK_LIST, TASK_ADD, TASK_EDIT,
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
private slots:
    void btnMenuTaskList_Clicked();
public:
    TaskPageControl* taskPageControl;
    QVBoxLayout *m_pageContainer;
    QWidget *m_currentWidget;
    QString szToken;
    static QMainWindow* findMainWindow();

public:
    void initializeEvent();
    void TransformPage(PAGEINFO PageInfo, QString param = "");
    QString getToken() {return szToken;}

};
#endif // MAINWINDOW_H
