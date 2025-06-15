#ifndef EMPLOYEESALARY_H
#define EMPLOYEESALARY_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QHeaderView>

struct Employee {
    QString name;
    QString position;
    double monthlySalary;
    double advanceAmount;
    double remainingSalary;
};

class EmployeeSalary : public QMainWindow
{
    Q_OBJECT

public:
    EmployeeSalary(QWidget *parent = nullptr);

private slots:
    void addEmployee();
    void giveAdvance();
    void resetSalary();
    void goBack();
    void onEmployeeSelectionChanged();

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
    QTableWidget *employeeTable;

    QLineEdit *nameEdit;
    QLineEdit *positionEdit;
    QDoubleSpinBox *salarySpinBox;
    QDoubleSpinBox *advanceSpinBox;

    QPushButton *addEmployeeButton;
    QPushButton *giveAdvanceButton;
    QPushButton *resetSalaryButton;
    QPushButton *backButton;

    QList<Employee> employees;
    int selectedRow;
};

#endif // EMPLOYEESALARY_H
