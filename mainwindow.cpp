#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->countryComboBox->addItem("Czech Republic");
    ui->countryComboBox->addItem("Slovakia");
    ui->countryComboBox->addItem("Germany");
    ui->countryComboBox->addItem("Poland");

    ui->currencyComboBox->addItem("USD");
    ui->currencyComboBox->addItem("CZK");
    ui->currencyComboBox->addItem("EUR");
    ui->currencyComboBox->addItem("PLN");

    ui->filterOptions->addItem("From the cheapest to the most expensive");
    ui->filterOptions->addItem("From the most expensive to the cheapest");
    ui->filterOptions->addItem("A->Z");
    ui->filterOptions->addItem("Z->A");

    ui->platformOptions->addItem("All");
    ui->platformOptions->addItem("PC Steam");
    ui->platformOptions->addItem("PC Origin");
    ui->platformOptions->addItem("Xbox Series X");
    ui->platformOptions->addItem("Xbox One");
    ui->platformOptions->addItem("Playstation 5");
    ui->platformOptions->addItem("Playstation 4");

    ui->categoryOptions->addItem("All");
    ui->categoryOptions->addItem("RPG");
    ui->categoryOptions->addItem("Strategy");
    ui->categoryOptions->addItem("Racing");
    ui->categoryOptions->addItem("Shooter");
    ui->categoryOptions->addItem("Open World");

    this->paymentMethodsModel = new QStandardItemModel(0, 3);
    this->paymentMethodsModel->setHorizontalHeaderItem(0, new QStandardItem("Card name"));
    this->paymentMethodsModel->setHorizontalHeaderItem(1, new QStandardItem("Card number"));
    this->paymentMethodsModel->setHorizontalHeaderItem(2, new QStandardItem("Expiration date"));
    this->ui->paymentMethodsTableView->setModel(this->paymentMethodsModel);


    this->gameItemModel =  new QStandardItemModel(0, 6);

    this->gameItemModel->setHorizontalHeaderItem(0, new QStandardItem(""));
    this->gameItemModel->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    this->gameItemModel->setHorizontalHeaderItem(2, new QStandardItem("Description"));
    this->gameItemModel->setHorizontalHeaderItem(3, new QStandardItem("Platform"));
    this->gameItemModel->setHorizontalHeaderItem(4, new QStandardItem("Category"));
    this->gameItemModel->setHorizontalHeaderItem(5, new QStandardItem("Price"));

    QList <QStandardItem*> gta5(6);
    QList <QStandardItem*> hoi4(6);

    QImage image(":/images/game_icon.png");
    QStandardItem* gta5ImageItem = new QStandardItem();
    QStandardItem* hoi4ImageItem = new QStandardItem();
    gta5ImageItem->setData(QVariant(QPixmap::fromImage(image).scaled(100, 50)), Qt::DecorationRole);
    hoi4ImageItem->setData(QVariant(QPixmap::fromImage(image).scaled(100, 50)), Qt::DecorationRole);

    gta5 = {gta5ImageItem, new QStandardItem("Grand Theft Auto V"),
            new QStandardItem("Grand Theft Auto V -- open world game in a huge and detalized world"),
            new QStandardItem("PC Steam"), new QStandardItem("Open World"), new QStandardItem("59")};

    hoi4 = {hoi4ImageItem, new QStandardItem("Hearts of Iron IV"),
            new QStandardItem("Hearts of Iron IV -- strategy about WW2"),
            new QStandardItem("PC Steam"), new QStandardItem("Strategy"), new QStandardItem("19")};

    this->games.push_back(gta5);
    this->games.push_back(hoi4);



    this->ui->gameTableView->setModel(this->gameItemModel);
    this->ui->gameTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->paymentMethodsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    connect(this->ui->addPaymentButton, SIGNAL(clicked(bool)), this, SLOT(showCardWindow()));
    connect(this->ui->logo, SIGNAL(clicked(bool)), this, SLOT(showStorePage()));
    connect(this->ui->myProfileButton, SIGNAL(clicked(bool)), this, SLOT(showProfilePage()));
    connect(this->ui->searchButton, SIGNAL(clicked(bool)), this, SLOT(searchResult()));

    this->showStorePage();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete paymentMethodsModel;
    delete gameItemModel;
}

void MainWindow::showCardWindow()
{
    CardDialog* cardDialog = new CardDialog();
    cardDialog->setWindowModality(Qt::ApplicationModal);
    connect(cardDialog, SIGNAL(cardCreated(Card)), this, SLOT(addCardToTable(Card)));
    cardDialog->show();
}

void MainWindow::addCardToTable(Card card)
{
    QList<QStandardItem*> item(3);

    item = {new QStandardItem(card.name.c_str()), new QStandardItem(std::to_string(card.number).c_str()), new QStandardItem((std::to_string(card.month) + "/" + std::to_string(card.year)).c_str())};

    this->paymentMethodsModel->appendRow(item);
}

void MainWindow::showProfilePage()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showStorePage()
{

    qInfo("Row counts before delete: %d", this->gameItemModel->rowCount());
    int rowCount = this->gameItemModel->rowCount();
    for(int i = 0; i < rowCount; i++){
        this->gameItemModel->takeRow(0);
    }
    qInfo("Row counts after delete: %d", this->gameItemModel->rowCount());
    for(unsigned int i = 0; i < this->games.size(); i++){
        this->gameItemModel->appendRow(this->games[i]);
    }
    qInfo("Row counts after append: %d", this->gameItemModel->rowCount());
    this->ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::searchResult()
{
    qInfo("Row counts before delete: %d", this->gameItemModel->rowCount());
    int rowCount = this->gameItemModel->rowCount();
    for(int i = 0; i < rowCount; i++){

        this->gameItemModel->takeRow(0);

    }

    qInfo("Row counts after delete: %d", this->gameItemModel->rowCount());
    for(unsigned int i = 0; i < this->games.size(); i++){
        if(games[i][1]->text().toStdString().find(this->ui->searchLineEdit->text().toStdString()) != std::string::npos){
            this->gameItemModel->appendRow(this->games[i]);
        }
    }
    qInfo("Row counts after append: %d", this->gameItemModel->rowCount());
    this->ui->stackedWidget->setCurrentIndex(1);
}
