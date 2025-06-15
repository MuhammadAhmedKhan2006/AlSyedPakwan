#include "inventory.h"
#include "ownerdashboard.h"

Inventory::Inventory(QWidget *parent)
    : QMainWindow(parent), selectedRow(-1)
{
    setupUI();
    setTheme();
    loadInitialData();
}

void Inventory::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    logoLayout = new QHBoxLayout();
    formLayout = new QHBoxLayout();
    leftFormLayout = new QVBoxLayout();
    rightFormLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    // Logo
    logoLabel = createLogo();
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch();

    // Title
    titleLabel = new QLabel("INVENTORY MANAGEMENT", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Arial", 20, QFont::Bold);
    titleLabel->setFont(titleFont);

    // Table
    inventoryTable = new QTableWidget(0, 6, this);
    QStringList headers = {"Item", "Supplier", "Quantity", "Total Amount", "Due Balance", "Paid Amount"};
    inventoryTable->setHorizontalHeaderLabels(headers);
    inventoryTable->horizontalHeader()->setStretchLastSection(true);
    inventoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    inventoryTable->setMinimumHeight(300);

    // Form elements - Left side
    itemNameEdit = new QLineEdit(this);
    leftFormLayout->addWidget(new QLabel("Item Name:", this));
    leftFormLayout->addWidget(itemNameEdit);

    supplierNameEdit = new QLineEdit(this);
    leftFormLayout->addWidget(new QLabel("Supplier Name:", this));
    leftFormLayout->addWidget(supplierNameEdit);

    quantitySpinBox = new QDoubleSpinBox(this);
    quantitySpinBox->setMaximum(99999.99);
    quantitySpinBox->setSuffix(" items");
    leftFormLayout->addWidget(new QLabel("Quantity:", this));
    leftFormLayout->addWidget(quantitySpinBox);

    // Form elements - Right side
    totalAmountSpinBox = new QDoubleSpinBox(this);
    totalAmountSpinBox->setMaximum(999999.99);
    totalAmountSpinBox->setPrefix("Rs. ");
    rightFormLayout->addWidget(new QLabel("Total Amount:", this));
    rightFormLayout->addWidget(totalAmountSpinBox);

    paymentSpinBox = new QDoubleSpinBox(this);
    paymentSpinBox->setMaximum(999999.99);
    paymentSpinBox->setPrefix("Rs. ");
    rightFormLayout->addWidget(new QLabel("Payment Amount:", this));
    rightFormLayout->addWidget(paymentSpinBox);

    stockSpinBox = new QDoubleSpinBox(this);
    stockSpinBox->setMaximum(99999.99);
    stockSpinBox->setSuffix(" items");
    rightFormLayout->addWidget(new QLabel("Add Stock:", this));
    rightFormLayout->addWidget(stockSpinBox);

    formLayout->addLayout(leftFormLayout);
    formLayout->addLayout(rightFormLayout);

    // Buttons
    addItemButton = new QPushButton("ADD NEW ITEM", this);
    addPaymentButton = new QPushButton("ADD PAYMENT", this);
    addStockButton = new QPushButton("ADD STOCK", this);
    backButton = new QPushButton("BACK", this);

    addItemButton->setMinimumHeight(40);
    addPaymentButton->setMinimumHeight(40);
    addStockButton->setMinimumHeight(40);
    backButton->setMinimumHeight(40);

    buttonLayout->addWidget(addItemButton);
    buttonLayout->addWidget(addPaymentButton);
    buttonLayout->addWidget(addStockButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(backButton);

    // Main layout
    mainLayout->addLayout(logoLayout);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(inventoryTable);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(addItemButton, &QPushButton::clicked, this, &Inventory::addItem);
    connect(addPaymentButton, &QPushButton::clicked, this, &Inventory::addPayment);
    connect(addStockButton, &QPushButton::clicked, this, &Inventory::addStock);
    connect(backButton, &QPushButton::clicked, this, &Inventory::goBack);
    connect(inventoryTable, &QTableWidget::itemSelectionChanged, this, &Inventory::onItemSelectionChanged);

    setWindowTitle("Inventory Management - Alsyed Pakwan");
    resize(1000, 700);
}

void Inventory::setTheme()
{
    setStyleSheet(
        "QMainWindow { background-color: #1a1a1a; }"
        "QLabel { color: white; font-weight: bold; }"
        "QLineEdit, QDoubleSpinBox {"
        "    background-color: #2d2d2d;"
        "    border: 2px solid #4CAF50;"
        "    border-radius: 5px;"
        "    color: white;"
        "    padding: 5px;"
        "    min-height: 25px;"
        "}"
        "QTableWidget {"
        "    background-color: #2d2d2d;"
        "    color: white;"
        "    gridline-color: #4CAF50;"
        "    selection-background-color: #4CAF50;"
        "}"
        "QHeaderView::section {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    font-weight: bold;"
        "    padding: 8px;"
        "    border: 1px solid #45a049;"
        "}"
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
        );
}

QLabel* Inventory::createLogo()
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

void Inventory::loadInitialData()
{
    InventoryItem chicken = {"Chicken", "ABC Poultry", 50.0, 15000.0, 5000.0, 10000.0};
    InventoryItem tomato = {"Tomato", "Fresh Vegetables Co", 25.0, 2500.0, 1000.0, 1500.0};
    InventoryItem onion = {"Onion", "Fresh Vegetables Co", 30.0, 1800.0, 800.0, 1000.0};
    InventoryItem garlic = {"Garlic", "Spice Mart", 10.0, 1200.0, 400.0, 800.0};
    InventoryItem potato = {"Potato", "Fresh Vegetables Co", 40.0, 2000.0, 500.0, 1500.0};

    inventoryItems.append(chicken);
    inventoryItems.append(tomato);
    inventoryItems.append(onion);
    inventoryItems.append(garlic);
    inventoryItems.append(potato);

    refreshTable();
}

void Inventory::refreshTable()
{
    inventoryTable->setRowCount(inventoryItems.size());

    for (int i = 0; i < inventoryItems.size(); ++i) {
        const InventoryItem& item = inventoryItems[i];
        inventoryTable->setItem(i, 0, new QTableWidgetItem(item.itemName));
        inventoryTable->setItem(i, 1, new QTableWidgetItem(item.supplierName));
        inventoryTable->setItem(i, 2, new QTableWidgetItem(QString::number(item.quantity, 'f', 2)));
        inventoryTable->setItem(i, 3, new QTableWidgetItem("Rs. " + QString::number(item.totalAmount, 'f', 2)));
        inventoryTable->setItem(i, 4, new QTableWidgetItem("Rs. " + QString::number(item.dueBalance, 'f', 2)));
        inventoryTable->setItem(i, 5, new QTableWidgetItem("Rs. " + QString::number(item.paidAmount, 'f', 2)));
    }
}

void Inventory::addItem()
{
    if (itemNameEdit->text().isEmpty() || supplierNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in item name and supplier name!");
        return;
    }

    InventoryItem newItem;
    newItem.itemName = itemNameEdit->text();
    newItem.supplierName = supplierNameEdit->text();
    newItem.quantity = quantitySpinBox->value();
    newItem.totalAmount = totalAmountSpinBox->value();
    newItem.dueBalance = totalAmountSpinBox->value();
    newItem.paidAmount = 0.0;

    inventoryItems.append(newItem);
    refreshTable();

    // Clear form
    itemNameEdit->clear();
    supplierNameEdit->clear();
    quantitySpinBox->setValue(0.0);
    totalAmountSpinBox->setValue(0.0);

    QMessageBox::information(this, "Success", "Item added successfully!");
}

void Inventory::addPayment()
{
    if (selectedRow < 0 || selectedRow >= inventoryItems.size()) {
        QMessageBox::warning(this, "Error", "Please select an item from the table!");
        return;
    }

    double payment = paymentSpinBox->value();
    if (payment <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid payment amount!");
        return;
    }

    InventoryItem& item = inventoryItems[selectedRow];
    if (payment > item.dueBalance) {
        QMessageBox::warning(this, "Error", "Payment amount cannot exceed due balance!");
        return;
    }

    item.paidAmount += payment;
    item.dueBalance -= payment;

    refreshTable();
    paymentSpinBox->setValue(0.0);

    QMessageBox::information(this, "Success", "Payment added successfully!");
}

void Inventory::addStock()
{
    if (selectedRow < 0 || selectedRow >= inventoryItems.size()) {
        QMessageBox::warning(this, "Error", "Please select an item from the table!");
        return;
    }

    double stock = stockSpinBox->value();
    if (stock <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid stock amount!");
        return;
    }

    inventoryItems[selectedRow].quantity += stock;
    refreshTable();
    stockSpinBox->setValue(0.0);

    QMessageBox::information(this, "Success", "Stock added successfully!");
}

void Inventory::onItemSelectionChanged()
{
    selectedRow = inventoryTable->currentRow();
}

void Inventory::goBack()
{
    OwnerDashboard *dashboard = new OwnerDashboard();
    dashboard->show();
    this->close();
}
