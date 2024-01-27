#include "include/createuserform.h"
#include "ui_createuserform.h"

CreateUserForm::CreateUserForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUserForm)
{
    ui->setupUi(this);
    lh = new login_handler();
}

CreateUserForm::~CreateUserForm()
{
    delete ui;
    delete lh;
}

void CreateUserForm::on_buttonBox_clicked(QAbstractButton *button)
{
    QString text = button->text();
    if(text == QString("&OK")) {
        QString username = ui->user_field->text();
        QString password = ui->pass_field->text();
        QString confirm_password = ui->confirm_field->text();

        if(username.isEmpty()) {
            QMessageBox msg(this);
            msg.setText("Please enter a username.");
            msg.exec();
        }

        else if(password.isEmpty()) {
            QMessageBox msg(this);
            msg.setText("Please enter a password.");
            msg.exec();
        }

        else if(password != confirm_password) {
            QMessageBox msg(this);
            msg.setText("Please confirm password.");
            msg.exec();
        }

        else {
            bool success = lh->createUser(username.toStdString(), password.toStdString());

            if(success) {
                QMessageBox msg(this);
                msg.setText("User successfully created. Thank you for registering!");
                msg.exec();
            }
            else {
                QMessageBox msg(this);
                msg.setText("User already exists or password is not strong enough. Please try again.");
                msg.exec();

            }
        }

    }
}

