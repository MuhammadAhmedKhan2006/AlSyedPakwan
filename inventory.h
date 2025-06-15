#ifndef INVENTORY_H
#define INVENTORY_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QHeaderView>

struct InventoryItem {
    QString itemName;
    QString supplierName;
    double quantity;
    double totalAmount;
    double dueBalance;
    double paidAmount;
};

class Inventory : public QMainWindow
{
    Q_OBJECT

public:
    Inventory(QWidget *parent = nullptr);

private slots:
    void addItem();
    void addPayment();
    void addStock();
    void goBack();
    void onItemSelectionChanged();

private:
    void setupUI();
    void setTheme();
    void refreshTable();
    void loadInitialData();
    QLabel* createLogo();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *logoLayout;
    QHBoxLayout *formLayout;
    QVBoxLayout *leftFormLayout;
    QVBoxLayout *rightFormLayout;
    QHBoxLayout *buttonLayout;

    QLabel *logoLabel;
    QLabel *titleLabel;
    QTableWidget *inventoryTable;

    // Form elements
    QLineEdit *itemNameEdit;
    QLineEdit *supplierNameEdit;
    QDoubleSpinBox *quantitySpinBox;
    QDoubleSpinBox *totalAmountSpinBox;
    QDoubleSpinBox *paymentSpinBox;
    QDoubleSpinBox *stockSpinBox;

    QPushButton *addItemButton;
    QPushButton *addPaymentButton;
    QPushButton *addStockButton;
    QPushButton *backButton;

    QList<InventoryItem> inventoryItems;
    int selectedRow;
};

#endif // INVENTORY_H
