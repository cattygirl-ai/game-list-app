#include "include/loginwindow.h"
#include "ui_loginwindow.h"

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    lh = new login_handler();
}

LoginWindow::~LoginWindow()
{
    delete lh;
    delete ui;
    delete mw;
    delete cuf;
}

// Close/OK
void LoginWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    QString text = button->text();

    if(text == QString("&Close")) {
        this->close();
        this->parentWidget()->close();
    }
    else if(text == QString("&OK")) {
        QString username = ui->user_field->text();
        QString password = ui->pass_field->text();

        if(password.isEmpty()) {
            QMessageBox msg(this);
            msg.setText("Please enter a password.");
            msg.exec();
        }

        else {
            User *user = lh->login(username.toStdString(), password.toStdString());

            if(user != NULL) {
                mw = new MainWindow(user);
                mw->show();
                this->hide();
            }
            else {
                QMessageBox msg(this);
                msg.setText("Invalid credentials.");
                msg.exec();
            }
        }
    }
}

// Create new user button
void LoginWindow::on_pushButton_clicked()
{
    cuf = new CreateUserForm(this);
    cuf->show();
}

