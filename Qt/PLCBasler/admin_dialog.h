#ifndef ADMIN_DIALOG_H
#define ADMIN_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = Q_NULLPTR);

signals:
    void success();

private slots:
    void judge();

private:
    QLabel      *m_label;
    QLineEdit   *m_lineEdit;
    QPushButton *m_pushButton;
};

#endif // ADMIN_DIALOG_H
