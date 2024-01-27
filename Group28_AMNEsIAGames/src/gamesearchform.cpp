#include "include/gamesearchform.h"
#include "ui_gamesearchform.h"

GameSearchForm::GameSearchForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameSearchForm)
{
    ui->setupUi(this);
}

GameSearchForm::~GameSearchForm()
{
    delete ui;
}
