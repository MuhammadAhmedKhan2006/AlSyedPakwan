#include "ownerlogin.h"
#include "ownerdashboard.h"
#include "mainwindow.h"

OwnerLogin::OwnerLogin(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setTheme();
}

void OwnerLogin::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    logoLayout = new QHBoxLayout();
    formLayout = new QVBoxLayout();

    // Logo
    logoLabel = createLogo();
    logoLayout->addWidget(logoLabel);
    logoLayout->addStretch();

    // Title
    titleLabel = new QLabel("OWNER LOGIN", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont("Arial", 20, QFont::Bold);
    titleLabel->setFont(titleFont);

    // Form elements
    emailLabel = new QLabel("Email:", this);
    emailEdit = new QLineEdit(this);
    passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("LOGIN", this);
    backButton = new QPushButton("BACK", this);

    emailEdit->setMinimumHeight(40);
    passwordEdit->setMinimumHeight(40);
    loginButton->setMinimumHeight(50);
    backButton->setMinimumHeight(40);

    QFont labelFont("Arial", 12, QFont::Bold);
    emailLabel->setFont(labelFont);
    passwordLabel->setFont(labelFont);

    // Layout
    formLayout->addStretch();
    formLayout->addWidget(titleLabel);
    formLayout->addSpacing(30);
    formLayout->addWidget(emailLabel);
    formLayout->addWidget(emailEdit);
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
    connect(loginButton, &QPushButton::clicked, this, &OwnerLogin::login);
    connect(backButton, &QPushButton::clicked, this, &OwnerLogin::goBack);

    setWindowTitle("Owner Login - Alsyed Pakwan");
    resize(400, 500);
}

void OwnerLogin::setTheme()
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

QLabel* OwnerLogin::createLogo()
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

void OwnerLogin::login()
{
    QString email = emailEdit->text();
    QString password = passwordEdit->text();

    // Simple authentication (you can enhance this)
    if (email == "owner@alsyedpakwan.com" && password == "owner123") {
        OwnerDashboard *dashboard = new OwnerDashboard();
        dashboard->doOwnerDashboard();
        dashboard->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid email or password!");
    }
}

void OwnerLogin::goBack()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}
