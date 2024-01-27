#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <iostream>
#include <QDialog>
#include <QAbstractButton>
#include <QMessageBox>

#include "login_handler.h"
#include "mainwindow.h"
#include "createuserform.h"
#include "User.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    login_handler *lh;
    MainWindow *mw;
    CreateUserForm *cuf;
    bool login(const QString username, const QString password);
};

#endif // LOGINWINDOW_H
