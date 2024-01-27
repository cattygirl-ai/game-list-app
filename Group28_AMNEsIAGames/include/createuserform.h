#ifndef CREATEUSERFORM_H
#define CREATEUSERFORM_H

#include <QDialog>
#include <QAbstractButton>
#include <QMessageBox>

#include "login_handler.h"

namespace Ui {
class CreateUserForm;
}

class CreateUserForm : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUserForm(QWidget *parent = nullptr);
    ~CreateUserForm();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CreateUserForm *ui;
    login_handler *lh;
};

#endif // CREATEUSERFORM_H
