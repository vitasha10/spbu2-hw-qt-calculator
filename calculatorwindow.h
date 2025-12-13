#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget *parent = nullptr);
    ~CalculatorWindow();

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onClearEntryClicked();
    void onBackspaceClicked();
    void onDecimalClicked();
    void onSignClicked();

private:
    // Calculator widgets
    QLineEdit *display;
    QPushButton *digitButtons[10];
    QPushButton *operatorButtons[4]; // +, -, *, /
    QPushButton *equalsButton;
    QPushButton *clearButton;
    QPushButton *clearEntryButton;
    QPushButton *backspaceButton;
    QPushButton *decimalButton;
    QPushButton *signButton;

    // Central widget and layouts
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QWidget *calculatorWidget;

    // Calculator state
    QString currentValue;
    QString pendingOperator;
    double firstOperand;
    bool waitingForSecondOperand;

    void setupUI();
    void setupCalculator();
    void calculate();
    void abortOperation();
};

#endif // CALCULATORWINDOW_H
