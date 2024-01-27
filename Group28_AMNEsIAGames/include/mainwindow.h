#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QLineEdit>

#include <list>

#include "User.h"
#include "login_handler.h"
#include "gamesearchform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(User *user = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addGameButton_clicked();

    void on_addListButton_clicked();

    void on_gameButton_clicked();

    void on_removeGameButton_clicked();

    void on_removeListButton_clicked();

    void on_listName_edited();

private:
    Ui::MainWindow *ui;
    GameSearchForm *gsf;
    login_handler *lh;
    User *currentUser;

    QPushButton* setupNewGame() const;
    QScrollArea* setupList() const;
};
#endif // MAINWINDOW_H
