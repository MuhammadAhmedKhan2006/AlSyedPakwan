#ifndef SALESMANDASHBOARD_H
#define SALESMANDASHBOARD_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QSpinBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QDateTime>

struct MenuItem {
    QString name;
    double price;
    QString category;
};

struct OrderItem {
    QString name;
    double price;
    int quantity;
    double total;
};

class SalesmanDashboard : public QMainWindow
{
    Q_OBJECT

public:
    SalesmanDashboard(QWidget *parent = nullptr);

private slots:
    void addToOrder();
    void removeFromOrder();
    void clearOrder();
    void generateBill();
    void printBill();
    void logout();
    void onMenuItemClicked();
    void onOrderItemClicked();

private:
    void setupUI();
    void setTheme();
    void loadMenuItems();
    void updateOrderTotal();
    void createBillText();
    QLabel* createLogo();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *logoLayout;
    QHBoxLayout *contentLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *orderButtonLayout;

    QLabel *logoLabel;
    QLabel *titleLabel;
    QLabel *menuLabel;
    QLabel *orderLabel;
    QLabel *totalLabel;

    QGridLayout *menuGrid;
    QWidget *menuWidget;
    QListWidget *orderList;
    QSpinBox *quantitySpinBox;
    QTextEdit *billPreview;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearButton;
    QPushButton *generateBillButton;
    QPushButton *printButton;
    QPushButton *logoutButton;

    QList<MenuItem> menuItems;
    QList<OrderItem> currentOrder;
    double orderTotal;
    int selectedMenuItem;
    QString lastBillText;
};

#endif // SALESMANDASHBOARD_H
