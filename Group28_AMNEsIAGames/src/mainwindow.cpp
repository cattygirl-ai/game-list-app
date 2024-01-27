#include "include/mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listArea->setLayoutDirection(Qt::RightToLeft);
    currentUser = user;
    lh = new login_handler();
}

MainWindow::~MainWindow()
{
    lh->logout(currentUser);

    delete ui;
    delete gsf;
    delete currentUser;
    delete lh;
}

void MainWindow::on_addGameButton_clicked()
{
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());

    if(senderButton != NULL) {
        QWidget *senderWidget = senderButton->parentWidget();
        QPushButton *newGame = setupNewGame();
        senderWidget->layout()->addWidget(newGame);
    }
}

void MainWindow::on_removeGameButton_clicked()
{
    QPushButton *senderRemoveButton = qobject_cast<QPushButton*>(sender());

    if(senderRemoveButton != NULL) {
        QPushButton *senderButton = qobject_cast<QPushButton*>(senderRemoveButton->parentWidget());
        QWidget *senderWidget = senderButton->parentWidget();

        senderWidget->layout()->removeWidget(senderButton);
        senderButton->setVisible(false);

    }
}

QPushButton* MainWindow::setupNewGame() const
{
    int buttonHeight = 50;
    int removeButtonWidth = 15;

    QPushButton *newGame = new QPushButton();
    newGame->setMinimumHeight(buttonHeight);
    newGame->setLayout(new QVBoxLayout());

    QPushButton *removeGameButton = new QPushButton("x", newGame);
    removeGameButton->setLayout(new QVBoxLayout());
    removeGameButton->setMaximumWidth(removeButtonWidth);
    newGame->layout()->addWidget(removeGameButton);
    connect(removeGameButton, SIGNAL(clicked()), this, SLOT(on_removeGameButton_clicked()));

    QLabel *text = new QLabel("Game");
    text->setAlignment(Qt::AlignCenter);
    newGame->layout()->addWidget(text);

    connect(newGame, SIGNAL(clicked()), this, SLOT(on_gameButton_clicked()));
    return newGame;
}

void MainWindow::on_gameButton_clicked()
{
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());

    gsf = new GameSearchForm(senderButton);
    gsf->show();
}

void MainWindow::on_addListButton_clicked()
{
    /*
    if(currentUser->getLists().size() >= 20) {
        QMessageBox msg(this);
        msg.setText("Maximum number of lists reached.");
        msg.exec();
        return;
    }
    */

    QScrollArea *newList = setupList();
}

void MainWindow::on_removeListButton_clicked()
{
    QPushButton *senderRemoveListButton = qobject_cast<QPushButton*>(sender());

    if(senderRemoveListButton != NULL) {
        QWidget *senderList = senderRemoveListButton->parentWidget()->parentWidget();

        ui->listAreaWidgetContents->layout()->removeWidget(senderList);
        senderList->setVisible(false);
    }
}

void MainWindow::on_listName_edited()
{
    QLineEdit *senderLineEdit = qobject_cast<QLineEdit*>(sender());
    QString newListName = senderLineEdit->text();
    QWidget *list = senderLineEdit->parentWidget()->parentWidget();
    QString currentListName = list->property("Name").toString();

    if(newListName.length() > 0) {
        if(currentUser->hasList(currentListName.toStdString())) {
            currentUser->getList()->se
        }
        currentUser->addList(listName.toStdString());
    }
}

QScrollArea* MainWindow::setupList() const
{
    int listWidth = 250;
    int removeButtonWidth = 15;
    int gameButtonHeight = 35;

    // Full List Widget
    QWidget *newList = new QWidget();
    newList->setLayout(new QVBoxLayout());
    newList->setMinimumWidth(listWidth);
    newList->setMaximumWidth(listWidth);
    newList->setProperty("Name", "");
    ui->listAreaWidgetContents->layout()->addWidget(newList);

    // List title and remove button
    QWidget *title = new QWidget();
    title->setLayout(new QHBoxLayout());
    title->setMaximumHeight(gameButtonHeight);

    QPushButton *removeListButton = new QPushButton("x", title);
    removeListButton->setLayout(new QVBoxLayout());
    removeListButton->setMaximumWidth(removeButtonWidth);
    title->layout()->addWidget(removeListButton);
    connect(removeListButton, SIGNAL(clicked()), this, SLOT(on_removeListButton_clicked()));

    QLineEdit *listName = new QLineEdit();
    listName->setPlaceholderText("e.g. Games for Chads");
    listName->setFrame(false);
    title->layout()->addWidget(listName);
    connect(listName, SIGNAL(editingFinished()), this, SLOT(on_listName_edited()));

    newList->layout()->addWidget(title);


    // Scroll area
    QScrollArea *listScrollArea = new QScrollArea();
    newList->layout()->addWidget(listScrollArea);
    listScrollArea->setWidgetResizable(true);

    // Scroll Area Container
    QWidget *listDisplay = new QWidget();
    listDisplay->setLayout(new QBoxLayout(QBoxLayout::BottomToTop));

    QSpacerItem *verticalSpacer = new QSpacerItem(0, 1000, QSizePolicy::Expanding, QSizePolicy::Expanding);
    listDisplay->layout()->addItem(verticalSpacer);

    QPushButton *newGameButton = new QPushButton("+", listDisplay);
    newGameButton->setMinimumHeight(gameButtonHeight);
    listDisplay->layout()->addWidget(newGameButton);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(on_addGameButton_clicked()));

    listScrollArea->setWidget(listDisplay);
    return listScrollArea;
}
