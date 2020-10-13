#include "baseview.h"

BaseView::BaseView(QWidget *parent) : QWidget(parent)
{

}

QMainWindow* findMainWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        QMainWindow* pMainWnd = qobject_cast<QMainWindow*>(pWidget);
        if (pMainWnd)
           return pMainWnd;
    }
    return nullptr;
}
