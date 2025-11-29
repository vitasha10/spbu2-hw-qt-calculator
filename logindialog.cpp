#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setWindowTitle("Авторизация");
    setFixedSize(350, 200);
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::setupUI()
{
    // Create widgets
    titleLabel = new QLabel("Вход в систему", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    usernameLabel = new QLabel("Имя пользователя:", this);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Введите имя пользователя");

    passwordLabel = new QLabel("Пароль:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Введите пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Войти", this);
    loginButton->setDefault(true);

    // Create layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QHBoxLayout *usernameLayout = new QHBoxLayout();
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);

    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addStretch();

    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);

    // Connect signals and slots
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);
}

void LoginDialog::onLoginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (validateCredentials(username, password)) {
        accept(); // Close dialog with QDialog::Accepted result
    } else {
        QMessageBox::warning(this, "Ошибка входа", 
                           "Неверное имя пользователя или пароль.\n"
                           "Попробуйте снова.");
        passwordEdit->clear();
        passwordEdit->setFocus();
    }
}

bool LoginDialog::validateCredentials(const QString &username, const QString &password)
{
    // Expected credentials
    const QString expectedUsername = "Илья Владимирович";
    const QString expectedPassword = "ЛУЧШИЙ";

    return (username == expectedUsername && password == expectedPassword);
}
