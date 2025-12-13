#include "calculatorwindow.h"
#include <QMessageBox>
#include <cmath>

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QMainWindow(parent)
    , currentValue("0")
    , pendingOperator("")
    , firstOperand(0.0)
    , waitingForSecondOperand(false)
{
    setupUI();
    setWindowTitle("Калькулятор");
    setFixedSize(300, 450);
}

CalculatorWindow::~CalculatorWindow()
{
}

void CalculatorWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    setupCalculator();

    mainLayout->addWidget(calculatorWidget);
}

void CalculatorWindow::setupCalculator()
{
    calculatorWidget = new QWidget(centralWidget);
    QVBoxLayout *calcLayout = new QVBoxLayout(calculatorWidget);
    calcLayout->setSpacing(5);

    // Title label
    QLabel *titleLabel = new QLabel("Калькулятор", calculatorWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    // Display
    display = new QLineEdit(calculatorWidget);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setText("0");
    QFont displayFont = display->font();
    displayFont.setPointSize(20);
    display->setFont(displayFont);
    display->setMinimumHeight(50);

    // Create buttons
    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = new QPushButton(QString::number(i), calculatorWidget);
        digitButtons[i]->setMinimumSize(60, 50);
        connect(digitButtons[i], &QPushButton::clicked, this, &CalculatorWindow::onDigitClicked);
    }

    QString operators[] = {"+", "-", "*", "/"};
    for (int i = 0; i < 4; ++i) {
        operatorButtons[i] = new QPushButton(operators[i], calculatorWidget);
        operatorButtons[i]->setMinimumSize(60, 50);
        connect(operatorButtons[i], &QPushButton::clicked, this, &CalculatorWindow::onOperatorClicked);
    }

    equalsButton = new QPushButton("=", calculatorWidget);
    equalsButton->setMinimumSize(60, 50);
    connect(equalsButton, &QPushButton::clicked, this, &CalculatorWindow::onEqualsClicked);

    clearButton = new QPushButton("C", calculatorWidget);
    clearButton->setMinimumSize(60, 50);
    connect(clearButton, &QPushButton::clicked, this, &CalculatorWindow::onClearClicked);

    clearEntryButton = new QPushButton("CE", calculatorWidget);
    clearEntryButton->setMinimumSize(60, 50);
    connect(clearEntryButton, &QPushButton::clicked, this, &CalculatorWindow::onClearEntryClicked);

    backspaceButton = new QPushButton("←", calculatorWidget);
    backspaceButton->setMinimumSize(60, 50);
    connect(backspaceButton, &QPushButton::clicked, this, &CalculatorWindow::onBackspaceClicked);

    decimalButton = new QPushButton(".", calculatorWidget);
    decimalButton->setMinimumSize(60, 50);
    connect(decimalButton, &QPushButton::clicked, this, &CalculatorWindow::onDecimalClicked);

    signButton = new QPushButton("±", calculatorWidget);
    signButton->setMinimumSize(60, 50);
    connect(signButton, &QPushButton::clicked, this, &CalculatorWindow::onSignClicked);

    // Create button grid layout
    QGridLayout *buttonLayout = new QGridLayout();
    buttonLayout->setSpacing(5);

    // Row 0: C, CE, ←, /
    buttonLayout->addWidget(clearButton, 0, 0);
    buttonLayout->addWidget(clearEntryButton, 0, 1);
    buttonLayout->addWidget(backspaceButton, 0, 2);
    buttonLayout->addWidget(operatorButtons[3], 0, 3); // /

    // Row 1: 7, 8, 9, *
    buttonLayout->addWidget(digitButtons[7], 1, 0);
    buttonLayout->addWidget(digitButtons[8], 1, 1);
    buttonLayout->addWidget(digitButtons[9], 1, 2);
    buttonLayout->addWidget(operatorButtons[2], 1, 3); // *

    // Row 2: 4, 5, 6, -
    buttonLayout->addWidget(digitButtons[4], 2, 0);
    buttonLayout->addWidget(digitButtons[5], 2, 1);
    buttonLayout->addWidget(digitButtons[6], 2, 2);
    buttonLayout->addWidget(operatorButtons[1], 2, 3); // -

    // Row 3: 1, 2, 3, +
    buttonLayout->addWidget(digitButtons[1], 3, 0);
    buttonLayout->addWidget(digitButtons[2], 3, 1);
    buttonLayout->addWidget(digitButtons[3], 3, 2);
    buttonLayout->addWidget(operatorButtons[0], 3, 3); // +

    // Row 4: ±, 0, ., =
    buttonLayout->addWidget(signButton, 4, 0);
    buttonLayout->addWidget(digitButtons[0], 4, 1);
    buttonLayout->addWidget(decimalButton, 4, 2);
    buttonLayout->addWidget(equalsButton, 4, 3);

    calcLayout->addWidget(titleLabel);
    calcLayout->addWidget(display);
    calcLayout->addLayout(buttonLayout);

}

void CalculatorWindow::onDigitClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    QString digit = button->text();

    if (waitingForSecondOperand) {
        currentValue = digit;
        waitingForSecondOperand = false;
    } else {
        if (currentValue == "0" && digit != "0") {
            currentValue = digit;
        } else if (currentValue != "0") {
            currentValue += digit;
        }
    }

    display->setText(currentValue);
}

void CalculatorWindow::onOperatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    QString clickedOperator = button->text();

    if (!pendingOperator.isEmpty()) {
        calculate();
    }

    firstOperand = currentValue.toDouble();
    pendingOperator = clickedOperator;
    waitingForSecondOperand = true;
}

void CalculatorWindow::onEqualsClicked()
{
    if (pendingOperator.isEmpty())
        return;

    calculate();
    pendingOperator.clear();
    waitingForSecondOperand = true;
}

void CalculatorWindow::onClearClicked()
{
    currentValue = "0";
    pendingOperator.clear();
    firstOperand = 0.0;
    waitingForSecondOperand = false;
    display->setText("0");
}

void CalculatorWindow::onClearEntryClicked()
{
    currentValue = "0";
    display->setText("0");
}

void CalculatorWindow::onBackspaceClicked()
{
    if (currentValue.length() > 1) {
        currentValue.chop(1);
    } else {
        currentValue = "0";
    }
    display->setText(currentValue);
}

void CalculatorWindow::onDecimalClicked()
{
    if (waitingForSecondOperand) {
        currentValue = "0.";
        waitingForSecondOperand = false;
    } else if (!currentValue.contains('.')) {
        currentValue += '.';
    }
    display->setText(currentValue);
}

void CalculatorWindow::onSignClicked()
{
    double value = currentValue.toDouble();
    if (value != 0.0) {
        value = -value;
        currentValue = QString::number(value, 'g', 15);
        display->setText(currentValue);
    }
}

void CalculatorWindow::calculate()
{
    double secondOperand = currentValue.toDouble();
    double result = 0.0;

    if (pendingOperator == "+") {
        result = firstOperand + secondOperand;
    } else if (pendingOperator == "-") {
        result = firstOperand - secondOperand;
    } else if (pendingOperator == "*") {
        result = firstOperand * secondOperand;
    } else if (pendingOperator == "/") {
        if (secondOperand == 0.0) {
            abortOperation();
            return;
        }
        result = firstOperand / secondOperand;
    }

    currentValue = QString::number(result, 'g', 15);
    display->setText(currentValue);
    firstOperand = result;
}

void CalculatorWindow::abortOperation()
{
    QMessageBox::warning(this, "Ошибка", "Деление на ноль невозможно!");
    onClearClicked();
}
