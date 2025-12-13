#include <QApplication>
#include "logindialog.h"
#include "calculatorwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create login dialog
    LoginDialog *loginDialog = new LoginDialog();
    
    // Create calculator window but don't show it yet
    CalculatorWindow *calculator = new CalculatorWindow();
    calculator->setAttribute(Qt::WA_DeleteOnClose);
    
    // Store the rejected connection so we can disconnect it on success
    QMetaObject::Connection rejectedConnection;
    
    // Connect login success signal to show calculator and close login dialog
    QObject::connect(loginDialog, &LoginDialog::loginSuccessful, [loginDialog, calculator, &rejectedConnection]() {
        // Disconnect the rejected signal to prevent app quit on login dialog close
        QObject::disconnect(rejectedConnection);
        calculator->show();
        loginDialog->close();
        loginDialog->deleteLater();
    });
    
    // If login dialog is closed without successful login, exit the application
    rejectedConnection = QObject::connect(loginDialog, &QDialog::rejected, [calculator]() {
        calculator->deleteLater();
        QApplication::quit();
    });
    
    // Show login dialog
    loginDialog->show();
    
    return app.exec();
}
