#include <QApplication>
#include "logindialog.h"
#include "calculatorwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Show login dialog first
    LoginDialog loginDialog;
    
    // If login is successful (accepted), show the calculator
    if (loginDialog.exec() == QDialog::Accepted) {
        CalculatorWindow *calculator = new CalculatorWindow();
        calculator->setAttribute(Qt::WA_DeleteOnClose);
        calculator->show();
        
        return app.exec();
    }
    
    // If login was cancelled or failed, exit
    return 0;
}
