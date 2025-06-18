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
#include <QLineEdit>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QMenuBar>
#include <QAction>

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
    void updateReceivedAmount();
    void generateDailySummary();
    void showAboutDialog();

private:
    void setupUI();
    void setTheme();
    void loadMenuItems();
    void updateOrderTotal();
    void createBillText();
    QLabel* createLogo();
    void saveBillToDailyLog();
    void createDailySummaryText(QString &summaryText);

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *logoLayout;
    QHBoxLayout *contentLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *orderButtonLayout;
    QHBoxLayout *paymentLayout;

    QLabel *logoLabel;
    QLabel *titleLabel;
    QLabel *menuLabel;
    QLabel *orderLabel;
    QLabel *totalLabel;
    QLabel *receivedLabel;
    QLabel *changeLabel;
    QLabel *customerLabel;
    QLabel *developerLabel;

    QGridLayout *menuGrid;
    QWidget *menuWidget;
    QListWidget *orderList;
    QSpinBox *quantitySpinBox;
    QLineEdit *receivedAmountEdit;
    QLineEdit *customerNameEdit;
    QTextEdit *billPreview;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearButton;
    QPushButton *generateBillButton;
    QPushButton *printButton;
    QPushButton *dailySummaryButton;
    QPushButton *logoutButton;

    QMenuBar *menuBar;
    QAction *aboutAction;

    QList<MenuItem> menuItems;
    QList<OrderItem> currentOrder;
    double orderTotal;
    double receivedAmount;
    double changeAmount;
    int selectedMenuItem;
    QString lastBillText;
    QString customerName;

    QString developerName = "MAK Software Developments";
    QString developerContact = "03331232042";
    QString developerFacebook = "facebook.com/makSoftwareDevelopments";
};

#endif // SALESMANDASHBOARD_H
