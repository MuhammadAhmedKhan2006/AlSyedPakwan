#ifndef OWNERLOGIN_H
#define OWNERLOGIN_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class OwnerLogin : public QDialog
{
    Q_OBJECT

public:
    OwnerLogin(QWidget *parent = nullptr);

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
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *backButton;
    QLabel *logoLabel;
    QLabel *titleLabel;
    QLabel *emailLabel;
    QLabel *passwordLabel;
};

#endif // OWNERLOGIN_H
