#ifndef LOGIN_H
#define LOGIN_H

#include<QtGui>
#include<QGridLayout>
#include<string>

class Login : public QWidget
{
    Q_OBJECT
public:
    Login();
private:
    QLabel *titleLabel;
    QLabel *nameLabel;
    QLabel *pwdLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;
private slots:
    void on_loginPushButton_clicked();
};

#endif // LOGIN_H
