#ifndef LOGINWIDNOW_H
#define LOGINWIDNOW_H

//! [0]
//!
#include <QDialog>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ui_loginwindow.h"
//! [0]

//! [1]
class LoginWindow: public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:

    void on_btnLogin_clicked();
    void replyFinished(QNetworkReply *);

private:
    Ui::LoginWindow ui;
public:
    QString szToken;
};
//! [1]


#endif // LOGINWIDNOW_H
