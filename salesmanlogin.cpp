#include "salesmanlogin.h"
#include "salesmandashboard.h"
#include "mainwindow.h"

SalesmanLogin::SalesmanLogin(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setTheme();
}

void SalesmanLogin::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    logoLayout = new QHBoxLayout();
    formLayout = new QVBoxLayout();

    // Logo
    logoLabel = createLogo();
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch();

    // Title
    titleLabel = new QLabel("SALESMAN LOGIN", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Arial", 20, QFont::Bold);
    titleLabel->setFont(titleFont);

    // Form elements
    usernameLabel = new QLabel("Username:", this);
    usernameEdit = new QLineEdit(this);
    passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("LOGIN", this);
    backButton = new QPushButton("BACK", this);

    usernameEdit->setMinimumHeight(40);
    passwordEdit->setMinimumHeight(40);
    loginButton->setMinimumHeight(50);
    backButton->setMinimumHeight(40);

    QFont labelFont("Arial", 12, QFont::Bold);
    usernameLabel->setFont(labelFont);
    passwordLabel->setFont(labelFont);

    // Layout
    formLayout->addStretch();
    formLayout->addWidget(titleLabel);
    formLayout->addSpacing(30);
    formLayout->addWidget(usernameLabel);
    formLayout->addWidget(usernameEdit);
    formLayout->addSpacing(15);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(passwordEdit);
    formLayout->addSpacing(30);
    formLayout->addWidget(loginButton);
    formLayout->addSpacing(10);
    formLayout->addWidget(backButton);
    formLayout->addStretch();

    mainLayout->addLayout(logoLayout);
    mainLayout->addLayout(formLayout);

    // Connect signals
    connect(loginButton, &QPushButton::clicked, this, &SalesmanLogin::login);
    connect(backButton, &QPushButton::clicked, this, &SalesmanLogin::goBack);

    setWindowTitle("Salesman Login - Alsyed Pakwan");
    resize(400, 500);
}

void SalesmanLogin::setTheme()
{
    setStyleSheet(
        "QDialog { background-color: #1a1a1a; }"
        "QLabel { color: white; }"
        "QLineEdit {"
        "    background-color: #2d2d2d;"
        "    border: 2px solid #4CAF50;"
        "    border-radius: 5px;"
        "    color: white;"
        "    padding: 8px;"
        "    font-size: 14px;"
        "}"
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    border: 2px solid #45a049;"
        "    border-radius: 8px;"
        "    color: white;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3d8b40;"
        "}"
        );
}

QLabel* SalesmanLogin::createLogo()
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

void SalesmanLogin::login()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // Simple authentication (you can enhance this)
    if (username == "salesman" && password == "sales123") {
        SalesmanDashboard *dashboard = new SalesmanDashboard();
        dashboard->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
    }
}

void SalesmanLogin::goBack()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}
