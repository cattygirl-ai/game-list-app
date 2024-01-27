#ifndef GAMESEARCHFORM_H
#define GAMESEARCHFORM_H

#include <QDialog>

namespace Ui {
class GameSearchForm;
}

class GameSearchForm : public QDialog
{
    Q_OBJECT

public:
    explicit GameSearchForm(QWidget *parent = nullptr);
    ~GameSearchForm();

private:
    Ui::GameSearchForm *ui;
};

#endif // GAMESEARCHFORM_H
