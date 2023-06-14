#include "carddialog.h"
#include "ui_carddialog.h"

CardDialog::CardDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CardDialog)
{
    ui->setupUi(this);
    this->ui->cardNumberLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,16}"),this));
    this->ui->cardYearLineEdit->setValidator(new QIntValidator(0, 9999, this));
    this->ui->cardCVVLineEdit->setValidator(new QIntValidator(0, 9999, this));

    connect(this->ui->addCardButton, SIGNAL(clicked(bool)), this, SLOT(createCard()));
}

CardDialog::~CardDialog()
{
    delete this->ui->cardNumberLineEdit->validator();
    delete this->ui->cardYearLineEdit->validator();
    delete this->ui->cardCVVLineEdit->validator();
    delete ui;
}

void CardDialog::createCard()
{

    if(this->ui->cardNameLineEdit->text().toStdString() == "" ||
       this->ui->cardNumberLineEdit->text().toStdString() == "" ||
       this->ui->cardYearLineEdit->text().toStdString() == "" ||
       this->ui->cardCVVLineEdit->text().toStdString() == "")
    {


        QMessageBox::critical(this,"Not complete card data", "Please fill all fields in form");
        return;
    }

    if(this->ui->cardNumberLineEdit->text().toStdString().length() != 16){

        QMessageBox::critical(this,"Incorrect card number", "Card number must have 16 signs");
        return;
    }



    std::string name = this->ui->cardNameLineEdit->text().toStdString();
    long number = this->ui->cardNumberLineEdit->text().toLong();

    int month = this->ui->cardMonthSpinBox->value();

    int year = this->ui->cardYearLineEdit->text().toInt();

    int cvv = this->ui->cardCVVLineEdit->text().toInt();

    Card card(name, number, month, year, cvv);

    emit this->cardCreated(card);

    this->close();
    this->destroy(true, true);
}
