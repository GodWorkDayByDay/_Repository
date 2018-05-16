#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);

private slots:

    /**
     * 回到主界面菜单栏
     **/
    void backToMainPage();

    /**
     * 显示PN码
     **/
    void getPNCode();


private:

    QWidget*        m_centralWidget;
    QStackedWidget* m_stackedWidget;
    QWidget*        m_rightWidget;

    QWidget*        m_mainPageWidget;
    QWidget*        m_pnWidget;

    QPushButton*    m_getPNPushButton;
    QPushButton*    m_backPushButon;
    QLabel*         m_pnLabel;
    QLabel*         m_pnResultLabel;
};

#endif // MAIN_WINDOW_H
