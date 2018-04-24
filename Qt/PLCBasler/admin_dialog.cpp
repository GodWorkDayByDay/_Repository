#include "admin_dialog.h"
#include <QString>
#include <QGridLayout>
#include <QMessageBox>

AdminDialog::AdminDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(QString::fromLocal8Bit("管理员登录"));

    m_label = new QLabel(QString::fromLocal8Bit("密码:"));
    m_lineEdit = new QLineEdit;
    m_pushButton = new QPushButton(QString::fromLocal8Bit("确定"));
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_label, 0, 0, 1, 1);
    mainLayout->addWidget(m_lineEdit, 0, 1, 1, 1);
    mainLayout->addWidget(m_pushButton, 1, 1, 1, 1);

    connect(m_pushButton, SIGNAL(clicked(bool)), SLOT(judge()));
}

void AdminDialog::judge()
{
    if (m_lineEdit->text() == "hapoa")
    {
        emit success();
        delete this;
    }
    else
        QMessageBox::critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("密码错误!"));
}
