#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QFont>
#include <QPalette>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openOwnerLogin();
    void openSalesmanLogin();

private:
    void setupUI();
    void setTheme();
    QLabel* createLogo();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *logoLayout;
    QVBoxLayout *buttonLayout;
    QPushButton *ownerButton;
    QPushButton *salesmanButton;
    QLabel *logoLabel;
    QLabel *titleLabel;
};

#endif // MAINWINDOW_H
