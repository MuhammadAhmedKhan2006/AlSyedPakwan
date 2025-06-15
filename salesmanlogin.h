#ifndef SALESMANLOGIN_H
#define SALESMANLOGIN_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class SalesmanLogin : public QDialog
{
    Q_OBJECT

public:
    SalesmanLogin(QWidget *parent = nullptr);

private slots:
    void login();
    void goBack();

private:
    void setupUI();
    void setTheme();
    QLabel* createLogo();

    QVBoxLayout *mainLayout;
    QHBoxLayout *logoLayout;
    QVBoxLayout *formLayout;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *backButton;
    QLabel *logoLabel;
    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
};

#endif // SALESMANLOGIN_H
