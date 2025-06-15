#ifndef OWNERDASHBOARD_H
#define OWNERDASHBOARD_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class OwnerDashboard : public QMainWindow
{
    Q_OBJECT

public:
    void doOwnerDashboard();

    OwnerDashboard(QWidget *parent = nullptr);

private slots:
    void openInventory();
    void openEmployeeSalary();
    void openSalesman();
    void logout();

private:
    void setupUI();
    void setTheme();
    QLabel* createLogo();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *logoLayout;
    QVBoxLayout *buttonLayout;

    QLabel *logoLabel;
    QLabel *titleLabel;
    QLabel *welcomeLabel;

    QPushButton *inventoryButton;
    QPushButton *salaryButton;
    QPushButton *salesmanButton;
    QPushButton *logoutButton;
};

#endif // OWNERDASHBOARD_H
