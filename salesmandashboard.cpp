#include "salesmandashboard.h"
#include "mainwindow.h"
#include <QScrollArea>
#include <QDoubleValidator>
#include <QApplication>
#include <QFileInfo>
#include <QDebug>

SalesmanDashboard::SalesmanDashboard(QWidget *parent)
    : QMainWindow(parent), orderTotal(0.0), receivedAmount(0.0), changeAmount(0.0), selectedMenuItem(-1), lastBillText("")
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
    paymentLayout = new QHBoxLayout();

    // Menu Bar
    menuBar = new QMenuBar(this);
    QMenu *helpMenu = new QMenu("Help", this);
    aboutAction = new QAction("About", this);
    helpMenu->addAction(aboutAction);
    menuBar->addMenu(helpMenu);
    setMenuBar(menuBar);

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

    customerLabel = new QLabel("Customer Name:", this);
    customerNameEdit = new QLineEdit(this);
    customerNameEdit->setPlaceholderText("Enter customer name");
    customerNameEdit->setFixedHeight(30);

    receivedLabel = new QLabel("Received: Rs. 0.00", this);
    changeLabel = new QLabel("Change: Rs. 0.00", this);
    receivedLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    changeLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    receivedAmountEdit = new QLineEdit(this);
    receivedAmountEdit->setPlaceholderText("Enter amount received");
    receivedAmountEdit->setFixedHeight(30);
    receivedAmountEdit->setValidator(new QDoubleValidator(0.0, 100000.0, 2, this));

    paymentLayout->addWidget(new QLabel("Amount Received:"));
    paymentLayout->addWidget(receivedAmountEdit);

    billPreview = new QTextEdit(this);
    billPreview->setReadOnly(true);
    billPreview->setMinimumWidth(300);

    generateBillButton = new QPushButton("GENERATE BILL", this);
    printButton = new QPushButton("PRINT BILL", this);
    dailySummaryButton = new QPushButton("GENERATE DAILY SUMMARY", this);
    generateBillButton->setMinimumHeight(40);
    printButton->setMinimumHeight(40);
    dailySummaryButton->setMinimumHeight(40);

    buttonLayout->addWidget(generateBillButton);
    buttonLayout->addWidget(printButton);
    buttonLayout->addWidget(dailySummaryButton);
    buttonLayout->addStretch();

    rightLayout->addWidget(billLabel);
    rightLayout->addWidget(customerLabel);
    rightLayout->addWidget(customerNameEdit);
    rightLayout->addWidget(billPreview);
    rightLayout->addLayout(paymentLayout);
    rightLayout->addWidget(receivedLabel);
    rightLayout->addWidget(changeLabel);
    rightLayout->addLayout(buttonLayout);

    // Developer Credit
    developerLabel = new QLabel(QString("Developed by %1").arg(developerName), this);
    developerLabel->setStyleSheet("font-size: 10px; color: #888888;");
    developerLabel->setAlignment(Qt::AlignRight);

    // Content layout
    contentLayout->addLayout(leftLayout);
    contentLayout->addLayout(rightLayout);

    // Main layout
    mainLayout->addLayout(logoLayout);
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(contentLayout);
    mainLayout->addWidget(developerLabel);

    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &SalesmanDashboard::addToOrder);
    connect(removeButton, &QPushButton::clicked, this, &SalesmanDashboard::removeFromOrder);
    connect(clearButton, &QPushButton::clicked, this, &SalesmanDashboard::clearOrder);
    connect(generateBillButton, &QPushButton::clicked, this, &SalesmanDashboard::generateBill);
    connect(printButton, &QPushButton::clicked, this, &SalesmanDashboard::printBill);
    connect(dailySummaryButton, &QPushButton::clicked, this, &SalesmanDashboard::generateDailySummary);
    connect(logoutButton, &QPushButton::clicked, this, &SalesmanDashboard::logout);
    connect(orderList, &QListWidget::itemClicked, this, &SalesmanDashboard::onOrderItemClicked);
    connect(receivedAmountEdit, &QLineEdit::textChanged, this, &SalesmanDashboard::updateReceivedAmount);
    connect(aboutAction, &QAction::triggered, this, &SalesmanDashboard::showAboutDialog);

    setWindowTitle("Salesman Dashboard - Alsyed Pakwan");
    resize(1000, 700);

    // Ensure logs directory exists
    QDir dir;
    if (!dir.exists("logs")) {
        dir.mkdir("logs");
    }
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
        "QSpinBox, QLineEdit {"
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
        "QMenuBar {"
        "    background-color: #2d2d2d;"
        "    color: white;"
        "}"
        "QMenu {"
        "    background-color: #2d2d2d;"
        "    color: white;"
        "}"
        "QAction {"
        "    color: white;"
        "}"
        );
}

QLabel* SalesmanDashboard::createLogo()
{
    QLabel *logo = new QLabel(this);
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
    menuItems.clear();
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

    for (OrderItem& orderItem : currentOrder) {
        if (orderItem.name == menuItem.name) {
            orderItem.quantity += quantity;
            orderItem.total = orderItem.quantity * orderItem.price;
            updateOrderTotal();
            return;
        }
    }

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
    customerNameEdit->clear();
    receivedAmountEdit->clear();
    receivedAmount = 0.0;
    changeAmount = 0.0;
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
    updateReceivedAmount();
}

void SalesmanDashboard::updateReceivedAmount()
{
    bool ok;
    receivedAmount = receivedAmountEdit->text().toDouble(&ok);
    if (!ok) {
        receivedAmount = 0.0;
    }
    changeAmount = receivedAmount - orderTotal;
    receivedLabel->setText("Received: Rs. " + QString::number(receivedAmount, 'f', 2));
    changeLabel->setText("Change: Rs. " + QString::number(changeAmount < 0 ? 0.0 : changeAmount, 'f', 2));
}

void SalesmanDashboard::generateBill()
{
    if (currentOrder.isEmpty()) {
        QMessageBox::warning(this, "Error", "No items in the order to generate a bill!");
        return;
    }

    customerName = customerNameEdit->text().isEmpty() ? "Guest" : customerNameEdit->text();
    createBillText();
    billPreview->setText(lastBillText);
    saveBillToDailyLog();
}

void SalesmanDashboard::createBillText()
{
    QString billText = "================================\n";
    billText += "         ALSYED PAKWAN\n";
    billText += "         RESTAURANT BILL\n";
    billText += "================================\n";
    billText += QString("Date: %1\n").arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss"));
    billText += QString("Customer: %1\n").arg(customerName.left(23));
    billText += "--------------------------------\n";
    billText += "Item               Qty  Total\n";
    billText += "--------------------------------\n";

    for (const OrderItem& item : currentOrder) {
        QString name = item.name.left(18);
        billText += name.leftJustified(18);
        billText += QString::number(item.quantity).rightJustified(6);
        billText += QString::number(item.total, 'f', 2).rightJustified(8);
        billText += "\n";
    }

    billText += "--------------------------------\n";
    billText += QString("Total: Rs %1\n").arg(QString::number(orderTotal, 'f', 2).rightJustified(8));
    billText += QString("Received: Rs %1\n").arg(QString::number(receivedAmount, 'f', 2).rightJustified(8));
    billText += QString("Change: Rs %1\n").arg(QString::number(changeAmount < 0 ? 0.0 : changeAmount, 'f', 2).rightJustified(8));
    billText += "================================\n";
    billText += "Thank you for dining with us!\n";
    billText += QString("%1\n").arg(developerName);
    billText += QString("%1\n").arg(developerContact);
    billText += QString("%1\n\n").arg(developerFacebook);

    lastBillText = billText;
}

void SalesmanDashboard::saveBillToDailyLog()
{
    QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");
    QString filePath = QString("logs/daily_log_%1.txt").arg(dateStr);
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Preview", "Error", "Unable to save bill to daily log!");
        return;
    }

    QTextStream out(&file);
    out << "===== Bill Generated at " << QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss") << " =====\n";
    out << "Customer: " << customerName << "\n";
    for (const OrderItem& item : currentOrder) {
        out << item.name << "," << item.quantity << "," << item.total << "\n";
    }
    out << "Total: " << orderTotal << "\n";
    out << "Received: " << receivedAmount << "\n";
    out << "Change: " << (changeAmount < 0 ? 0.0 : changeAmount) << "\n";
    out << "====================================\n\n";
    file.close();
}

void SalesmanDashboard::generateDailySummary()
{
    QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");
    QString logFilePath = QString("logs/daily_log_%1.txt").arg(dateStr);
    QFile logFile(logFilePath);

    if (!logFile.exists()) {
        QMessageBox::warning(this, "Error", "No bills generated today!");
        return;
    }

    if (!logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open daily log file!");
        return;
    }

    QString summaryText;
    createDailySummaryText(summaryText);

    logFile.close(); // Ensure file is closed before saving

    // Save summary to file
    QString summaryFilePath = QString("logs/daily_summary_%1.txt").arg(dateStr);
    QFile summaryFile(summaryFilePath);
    if (!summaryFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to save daily summary!");
        return;
    }

    QTextStream out(&summaryFile);
    out << summaryText;
    summaryFile.close();

    // Display summary in bill preview
    billPreview->setText(summaryText);
    QMessageBox::information(this, "Success", QString("Daily summary saved to %1").arg(summaryFilePath));
}

void SalesmanDashboard::createDailySummaryText(QString &summaryText)
{
    QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");
    QString logFilePath = QString("logs/daily_log_%1.txt").arg(dateStr);
    QFile logFile(logFilePath);

    if (!logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        summaryText = "Error: Unable to read daily log!";
        return;
    }

    QTextStream in(&logFile);
    QMap<QString, QPair<int, double>> itemSummary; // Item -> (Quantity, Total)
    double totalSales = 0.0;
    int billCount = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("===== Bill Generated")) {
            billCount++;
            continue;
        }
        if (line.startsWith("Total: ")) {
            totalSales += line.mid(7).toDouble();
            continue;
        }
        if (!line.contains(",") || line.startsWith("Customer:") || line.startsWith("Received:") || line.startsWith("Change:") || line.isEmpty()) {
            continue;
        }

        QStringList parts = line.split(",");
        if (parts.size() == 3) {
            QString itemName = parts[0];
            int quantity = parts[1].toInt();
            double total = parts[2].toDouble();
            itemSummary[itemName].first += quantity;
            itemSummary[itemName].second += total;
        }
    }
    logFile.close();

    summaryText = "====================================\n";
    summaryText += "         ALSYED PAKWAN\n";
    summaryText += "      DAILY SUMMARY REPORT\n";
    summaryText += "====================================\n";
    summaryText += QString("Date: %1\n").arg(QDate::currentDate().toString("dd-MM-yyyy"));
    summaryText += QString("Total Bills: %1\n").arg(billCount);
    summaryText += QString("Total Sales: Rs %1\n").arg(QString::number(totalSales, 'f', 2).rightJustified(8));
    summaryText += "------------------------------------\n";
    summaryText += "Item               Qty  Total\n";
    summaryText += "------------------------------------\n";

    for (auto it = itemSummary.constBegin(); it != itemSummary.constEnd(); ++it) {
        QString name = it.key().left(18);
        summaryText += name.leftJustified(18);
        summaryText += QString::number(it.value().first).rightJustified(6);
        summaryText += QString::number(it.value().second, 'f', 2).rightJustified(8);
        summaryText += "\n";
    }

    summaryText += "====================================\n";
    summaryText += QString("%1\n").arg(developerName);
    summaryText += QString("%1\n").arg(developerContact);
    summaryText += QString("%1\n\n").arg(developerFacebook);
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

void SalesmanDashboard::showAboutDialog()
{
    QString aboutText = QString(
                            "Alsyed Pakwan Point of Sale System\n"
                            "Version 1.0\n"
                            "Developed by %1\n"
                            "%2\n"
                            "%3\n"
                            "This software is provided free of charge for Alsyed Pakwan.\n"
                            ).arg(developerName, developerContact, developerFacebook);

    QMessageBox::about(this, "About Alsyed Pakwan POS", aboutText);
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
