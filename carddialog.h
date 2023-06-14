#ifndef CARDDIALOG_H
#define CARDDIALOG_H

#include <QMainWindow>
#include <QMessageBox>
class Card{

public:

    std::string name;
    long number;
    int month;
    int year;
    int cvv;

    Card(std::string name, long number, int month, int year, int cvv){

        this->name = name;
        this->number = number;
        this->month = month;
        this->year = year;
        this->cvv = cvv;
    }

};

namespace Ui {
class CardDialog;
}

class CardDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardDialog(QWidget *parent = nullptr);
    ~CardDialog();

signals:

    void cardCreated(Card card);

public slots:

    void createCard();


private:
    Ui::CardDialog *ui;
};

#endif // CARDDIALOG_H
