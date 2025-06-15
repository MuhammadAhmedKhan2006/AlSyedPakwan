#include "employeesalary.h"
#include "ownerdashboard.h"

EmployeeSalary::EmployeeSalary(QWidget *parent)
    : QMainWindow(parent), selectedRow(-1)
{
    setupUI();
    setTheme();
    loadInitialData();
}

void EmployeeSalary::setupUI()
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
    titleLabel = new QLabel("EMPLOYEE SALARY MANAGEMENT", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Arial", 18, QFont::Bold);
    titleLabel->setFont(titleFont);

    // Table
    employeeTable = new QTableWidget(0, 5, this);
    QStringList headers = {"Name", "Position", "Monthly Salary", "Advance Given", "Remaining Salary"};
    employeeTable->setHorizontalHeaderLabels(headers);
    employeeTable->horizontalHeader()->setStretchLastSection(true);
    employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    employeeTable->setMinimumHeight(300);

    // Form elements - Left side
    nameEdit = new QLineEdit(this);
    leftFormLayout->addWidget(new QLabel("Employee Name:", this));
    leftFormLayout->addWidget(nameEdit);

    positionEdit = new QLineEdit(this);
    leftFormLayout->addWidget(new QLabel("Position:", this));
    leftFormLayout->addWidget(positionEdit);

    // Form elements - Right side
    salarySpinBox = new QDoubleSpinBox(this);
    salarySpinBox->setMaximum(999999.99);
    salarySpinBox->setPrefix("Rs. ");
    rightFormLayout->addWidget(new QLabel("Monthly Salary:", this));
    rightFormLayout->addWidget(salarySpinBox);

    advanceSpinBox = new QDoubleSpinBox(this);
    advanceSpinBox->setMaximum(999999.99);
    advanceSpinBox->setPrefix("Rs. ");
    rightFormLayout->addWidget(new QLabel("Advance Amount:", this));
    rightFormLayout->addWidget(advanceSpinBox);

    formLayout->addLayout(leftFormLayout);
    formLayout->addLayout(rightFormLayout);

    // Buttons
    addEmployeeButton = new QPushButton("ADD EMPLOYEE", this);
    giveAdvanceButton = new QPushButton("GIVE ADVANCE", this);
    resetSalaryButton = new QPushButton("RESET MONTHLY", this);
    backButton = new QPushButton("BACK", this);

    addEmployeeButton->setMinimumHeight(40);
    giveAdvanceButton->setMinimumHeight(40);
    resetSalaryButton->setMinimumHeight(40);
    backButton->setMinimumHeight(40);

    buttonLayout->addWidget(addEmployeeButton);
    buttonLayout->addWidget(giveAdvanceButton);
    buttonLayout->addWidget(resetSalaryButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(backButton);

    // Main layout
    mainLayout->addLayout(logoLayout);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(employeeTable);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(addEmployeeButton, &QPushButton::clicked, this, &EmployeeSalary::addEmployee);
    connect(giveAdvanceButton, &QPushButton::clicked, this, &EmployeeSalary::giveAdvance);
    connect(resetSalaryButton, &QPushButton::clicked, this, &EmployeeSalary::resetSalary);
    connect(backButton, &QPushButton::clicked, this, &EmployeeSalary::goBack);
    connect(employeeTable, &QTableWidget::itemSelectionChanged, this, &EmployeeSalary::onEmployeeSelectionChanged);

    setWindowTitle("Employee Salary Management - Alsyed Pakwan");
    resize(1000, 700);
}

void EmployeeSalary::setTheme()
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

QLabel* EmployeeSalary::createLogo()
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

void EmployeeSalary::loadInitialData()
{
    Employee chef = {"Ahmad Ali", "Head Chef", 50000.0, 10000.0, 40000.0};
    Employee waiter1 = {"Muhammad Hassan", "Waiter", 25000.0, 5000.0, 20000.0};
    Employee waiter2 = {"Ali Raza", "Waiter", 25000.0, 0.0, 25000.0};
    Employee cleaner = {"Fatima Khan", "Cleaner", 20000.0, 3000.0, 17000.0};
    Employee cashier = {"Sara Ahmed", "Cashier", 35000.0, 8000.0, 27000.0};

    employees.append(chef);
    employees.append(waiter1);
    employees.append(waiter2);
    employees.append(cleaner);
    employees.append(cashier);

    refreshTable();
}

void EmployeeSalary::refreshTable()
{
    employeeTable->setRowCount(employees.size());

    for (int i = 0; i < employees.size(); ++i) {
        const Employee& emp = employees[i];
        employeeTable->setItem(i, 0, new QTableWidgetItem(emp.name));
        employeeTable->setItem(i, 1, new QTableWidgetItem(emp.position));
        employeeTable->setItem(i, 2, new QTableWidgetItem("Rs. " + QString::number(emp.monthlySalary, 'f', 2)));
        employeeTable->setItem(i, 3, new QTableWidgetItem("Rs. " + QString::number(emp.advanceAmount, 'f', 2)));
        employeeTable->setItem(i, 4, new QTableWidgetItem("Rs. " + QString::number(emp.remainingSalary, 'f', 2)));
    }
}

void EmployeeSalary::addEmployee()
{
    if (nameEdit->text().isEmpty() || positionEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill in employee name and position!");
        return;
    }

    Employee newEmployee;
    newEmployee.name = nameEdit->text();
    newEmployee.position = positionEdit->text();
    newEmployee.monthlySalary = salarySpinBox->value();
    newEmployee.advanceAmount = 0.0;
    newEmployee.remainingSalary = salarySpinBox->value();

    employees.append(newEmployee);
    refreshTable();

    // Clear form
    nameEdit->clear();
    positionEdit->clear();
    salarySpinBox->setValue(0.0);

    QMessageBox::information(this, "Success", "Employee added successfully!");
}

void EmployeeSalary::giveAdvance()
{
    if (selectedRow < 0 || selectedRow >= employees.size()) {
        QMessageBox::warning(this, "Warning", "Please select an employee from the table!");
        return;
    }

    double advance = advanceSpinBox->value();
    if (advance <= 0) {
        QMessageBox::warning(this, "Warning", "Please enter a valid advance amount!");
        return;
    }

    Employee& emp = employees[selectedRow];
    if (advance > emp.remainingSalary) {
        QMessageBox::warning(this, "Warning", "Advance amount cannot exceed remaining salary!");
        return;
    }

    emp.advanceAmount += advance;
    emp.remainingSalary -= advance;

    refreshTable();
    advanceSpinBox->setValue(0.0);

    QMessageBox::information(this, "Success", "Advance given successfully!");
}

void EmployeeSalary::resetSalary()
{
    for (Employee& emp : employees) {
        emp.advanceAmount = 0.0;
        emp.remainingSalary = emp.monthlySalary;
    }

    refreshTable();
    QMessageBox::information(this, "Success", "All salaries reset for new month!");
}

void EmployeeSalary::onEmployeeSelectionChanged()
{
    selectedRow = employeeTable->currentRow();
}

void EmployeeSalary::goBack()
{
    OwnerDashboard *dashboard = new OwnerDashboard();
    dashboard->show();
    this->close();
}
