#include "salesmandashboard.h"
#include "mainwindow.h"
#include <QScrollArea>

SalesmanDashboard::SalesmanDashboard(QWidget *parent)
    : QMainWindow(parent), orderTotal(0.0), selectedMenuItem(-1), lastBillText("")
{
    setupUI();
    setTheme();
    loadMenuItems();
}

void SalesmanDashboard::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    logoLayout = new QHBoxLayout();
    contentLayout = new QHBoxLayout();
    leftLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();
    orderButtonLayout = new QHBoxLayout();

    // Logo
    logoLabel = createLogo();
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch();
    logoutButton = new QPushButton("LOGOUT", this);
    logoutButton->setFixedSize(100, 40);
    QFont buttonFont("Arial", 12, QFont::Bold);
    logoutButton->setFont(buttonFont);
    logoLayout->addWidget(logoutButton);

    // Title
    titleLabel = new QLabel("POINT OF SALE - ALSYED PAKWAN", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Arial", 20, QFont::Bold);
    titleLabel->setFont(titleFont);

    // Left side - Menu and order
    menuLabel = new QLabel("MENU ITEMS", this);
    menuLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    menuWidget = new QWidget(this);
    menuGrid = new QGridLayout(menuWidget);
    QScrollArea *menuScroll = new QScrollArea(this);
    menuScroll->setWidget(menuWidget);
    menuScroll->setWidgetResizable(true);
    menuScroll->setMinimumWidth(400);

    orderLabel = new QLabel("CURRENT ORDER", this);
    orderLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    quantitySpinBox = new QSpinBox(this);
    quantitySpinBox->setMinimum(1);
    quantitySpinBox->setMaximum(100);
    quantitySpinBox->setValue(1);
    quantitySpinBox->setFixedHeight(30);

    addButton = new QPushButton("ADD TO ORDER", this);
    removeButton = new QPushButton("REMOVE ITEM", this);
    clearButton = new QPushButton("CLEAR ORDER", this);

    addButton->setMinimumHeight(40);
    removeButton->setMinimumHeight(40);
    clearButton->setMinimumHeight(40);

    orderButtonLayout->addWidget(new QLabel("Quantity:"));
    orderButtonLayout->addWidget(quantitySpinBox);
    orderButtonLayout->addWidget(addButton);
    orderButtonLayout->addWidget(removeButton);
    orderButtonLayout->addWidget(clearButton);

    orderList = new QListWidget(this);
    orderList->setMinimumHeight(200);

    totalLabel = new QLabel("Total: Rs. 0.00", this);
    totalLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    leftLayout->addWidget(menuLabel);
    leftLayout->addWidget(menuScroll);
    leftLayout->addWidget(orderLabel);
    leftLayout->addLayout(orderButtonLayout);
    leftLayout->addWidget(orderList);
    leftLayout->addWidget(totalLabel);

    // Right side - Bill preview
    QLabel *billLabel = new QLabel("BILL PREVIEW", this);
    billLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    billPreview = new QTextEdit(this);
    billPreview->setReadOnly(true);
    billPreview->setMinimumWidth(300);

    generateBillButton = new QPushButton("GENERATE BILL", this);
    printButton = new QPushButton("PRINT BILL", this);
    generateBillButton->setMinimumHeight(40);
    printButton->setMinimumHeight(40);

    buttonLayout->addWidget(generateBillButton);
    buttonLayout->addWidget(printButton);
    buttonLayout->addStretch();

    rightLayout->addWidget(billLabel);
    rightLayout->addWidget(billPreview);
    rightLayout->addLayout(buttonLayout);

    // Content layout
    contentLayout->addLayout(leftLayout);
    contentLayout->addLayout(rightLayout);

    // Main layout
    mainLayout->addLayout(logoLayout);
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(contentLayout);

    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &SalesmanDashboard::addToOrder);
    connect(removeButton, &QPushButton::clicked, this, &SalesmanDashboard::removeFromOrder);
    connect(clearButton, &QPushButton::clicked, this, &SalesmanDashboard::clearOrder);
    connect(generateBillButton, &QPushButton::clicked, this, &SalesmanDashboard::generateBill);
    connect(printButton, &QPushButton::clicked, this, &SalesmanDashboard::printBill);
    connect(logoutButton, &QPushButton::clicked, this, &SalesmanDashboard::logout);
    connect(orderList, &QListWidget::itemClicked, this, &SalesmanDashboard::onOrderItemClicked);

    setWindowTitle("Salesman Dashboard - Alsyed Pakwan");
    resize(1000, 700);
}

void SalesmanDashboard::setTheme()
{
    setStyleSheet(
        "QMainWindow { background-color: #1a1a1a; }"
        "QLabel { color: white; }"
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    border: 2px solid #45a049;"
        "    border-radius: 8px;"
        "    color: white;"
        "    font-weight: bold;"
        "    padding: 8px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3d8b40;"
        "}"
        "QListWidget {"
        "    background-color: #2d2d2d;"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    selection-background-color: #4CAF50;"
        "}"
        "QSpinBox {"
        "    background-color: #2d2d2d;"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    padding: 5px;"
        "}"
        "QTextEdit {"
        "    background-color: #2d2d2d;"
        "    color: white;"
        "    border: 2px solid #4CAF50;"
        "    font-family: 'Courier New', monospace;"
        "}"
        "QScrollArea {"
        "    background-color: #2d2d2d;"
        "    border: 2px solid #4CAF50;"
        "}"
        );
}

QLabel* SalesmanDashboard::createLogo()
{
    QLabel* logo = new QLabel(this);
    logo->setFixedSize(60, 60);
    logo->setStyleSheet(
        "QLabel {"
        "    background-color: #4CAF50;"
        "    border: 3px solid white;"
        "    border-radius: 30px;"
        "    color: white;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "}"
        );
    logo->setText("AP");
    logo->setAlignment(Qt::AlignCenter);
    return logo;
}

void SalesmanDashboard::loadMenuItems()
{
    // Clear existing menu
    menuItems.clear();

    // Add sample menu items
    menuItems.append({"Chicken Biryani", 250.0, "Main Course"});
    menuItems.append({"Chicken Qorma", 200.0, "Main Course"});
    menuItems.append({"Chicken Karahi", 300.0, "Main Course"});
    menuItems.append({"Mutton Biryani", 350.0, "Main Course"});
    menuItems.append({"Beef Nihari", 280.0, "Main Course"});
    menuItems.append({"Naan", 30.0, "Bread"});
    menuItems.append({"Roti", 20.0, "Bread"});
    menuItems.append({"Cold Drink", 50.0, "Beverages"});
    menuItems.append({"Tea", 40.0, "Beverages"});
    menuItems.append({"Lassi", 80.0, "Beverages"});

    // Populate menu grid
    int row = 0, col = 0;
    for (int i = 0; i < menuItems.size(); ++i) {
        QPushButton *itemButton = new QPushButton(menuItems[i].name + "\nRs. " + QString::number(menuItems[i].price, 'f', 2), this);
        itemButton->setMinimumHeight(60);
        itemButton->setProperty("index", i);
        connect(itemButton, &QPushButton::clicked, this, &SalesmanDashboard::onMenuItemClicked);
        menuGrid->addWidget(itemButton, row, col);
        col++;
        if (col >= 3) {
            col = 0;
            row++;
        }
    }
    menuWidget->setLayout(menuGrid);
}

void SalesmanDashboard::addToOrder()
{
    if (selectedMenuItem < 0 || selectedMenuItem >= menuItems.size()) {
        QMessageBox::warning(this, "Error", "Please select a menu item!");
        return;
    }

    int quantity = quantitySpinBox->value();
    const MenuItem& menuItem = menuItems[selectedMenuItem];

    // Check if item already exists in order
    for (OrderItem& orderItem : currentOrder) {
        if (orderItem.name == menuItem.name) {
            orderItem.quantity += quantity;
            orderItem.total = orderItem.quantity * orderItem.price;
            updateOrderTotal();
            return;
        }
    }

    // Add new item to order
    OrderItem newItem;
    newItem.name = menuItem.name;
    newItem.price = menuItem.price;
    newItem.quantity = quantity;
    newItem.total = quantity * menuItem.price;
    currentOrder.append(newItem);

    updateOrderTotal();
}

void SalesmanDashboard::removeFromOrder()
{
    int selectedRow = orderList->currentRow();
    if (selectedRow < 0 || selectedRow >= currentOrder.size()) {
        QMessageBox::warning(this, "Error", "Please select an order item to remove!");
        return;
    }

    currentOrder.removeAt(selectedRow);
    updateOrderTotal();
}

void SalesmanDashboard::clearOrder()
{
    currentOrder.clear();
    updateOrderTotal();
    billPreview->clear();
    lastBillText = "";
}

void SalesmanDashboard::updateOrderTotal()
{
    orderList->clear();
    orderTotal = 0.0;

    for (const OrderItem& item : currentOrder) {
        orderList->addItem(item.name + " x" + QString::number(item.quantity) + " = Rs. " + QString::number(item.total, 'f', 2));
        orderTotal += item.total;
    }

    totalLabel->setText("Total: Rs. " + QString::number(orderTotal, 'f', 2));
}

void SalesmanDashboard::generateBill()
{
    if (currentOrder.isEmpty()) {
        QMessageBox::warning(this, "Error", "No items in the order to generate a bill!");
        return;
    }

    createBillText();
    billPreview->setText(lastBillText);
}

void SalesmanDashboard::createBillText()
{
    QString billText = "=============================\n";
    billText += "      ALSYED PAKWAN\n";
    billText += "      RESTAURANT BILL\n";
    billText += "=============================\n";
    billText += "Date: " + QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss") + "\n";
    billText += "-----------------------------\n";
    billText += "Item            Qty    Total\n";
    billText += "-----------------------------\n";

    for (const OrderItem& item : currentOrder) {
        billText += item.name.leftJustified(15, ' ');
        billText += QString::number(item.quantity).rightJustified(4, ' ');
        billText += QString::number(item.total, 'f', 2).rightJustified(10, ' ') + "\n";
    }

    billText += "-----------------------------\n";
    billText += "Total: Rs. " + QString::number(orderTotal, 'f', 2) + "\n";
    billText += "=============================\n";
    billText += "Thank you for dining with us!\n";

    lastBillText = billText;
}

void SalesmanDashboard::printBill()
{
    if (lastBillText.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please generate a bill first!");
        return;
    }

    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QTextDocument doc;
        doc.setPlainText(lastBillText);
        doc.print(&printer);
        QMessageBox::information(this, "Success", "Bill printed successfully!");
    }
}

void SalesmanDashboard::onMenuItemClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        selectedMenuItem = button->property("index").toInt();
    }
}

void SalesmanDashboard::onOrderItemClicked()
{
    // No specific action needed, just ensure selection is updated
}

void SalesmanDashboard::logout()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}
