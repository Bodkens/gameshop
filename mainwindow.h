#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <carddialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStandardItemModel* paymentMethodsModel;
    QStandardItemModel* gameItemModel;
    std::vector<QList <QStandardItem*>
                > games;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void showCardWindow();
    void addCardToTable(Card card);
    void showProfilePage();
    void showStorePage();
    void searchResult();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
