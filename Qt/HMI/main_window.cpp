#include "main_window.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_stackedWidget = new QStackedWidget;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QGridLayout *gLayout;

    // 主菜单界面 - 0
    m_mainPageWidget = new QWidget;
    m_stackedWidget->addWidget(m_mainPageWidget);
    m_getPNPushButton = new QPushButton(tr("获取 PN 码"));
    connect(m_getPNPushButton, &QPushButton::clicked, this, &MainWindow::getPN);
    gLayout = new QGridLayout;
    gLayout->addWidget(m_getPNPushButton, 0, 0, 1, 1);
    m_mainPageWidget->setLayout(gLayout);

    // PN 码界面 - 1
    m_pnWidget = new QWidget;
    m_stackedWidget->addWidget(m_pnWidget);

    //
    m_rightWidget = new QWidget;
    m_backPushButon = new QPushButton(tr("返回"));
    connect(m_backPushButon, &QPushButton::clicked, this, &MainWindow::backToMainPage);
    vLayout = new QVBoxLayout(m_rightWidget);
    vLayout->addWidget(m_backPushButon);
    vLayout->addStretch();
    m_backPushButon->setEnabled(false);

    m_centralWidget = new QWidget;
    hLayout = new QHBoxLayout(m_centralWidget);
    hLayout->addWidget(m_stackedWidget, 8);
    hLayout->addWidget(m_rightWidget, 2);
    setCentralWidget(m_centralWidget);
}

/**
 * 回到主界面菜单栏
 **/
void MainWindow::backToMainPage()
{
    m_stackedWidget->setCurrentIndex(0);
}

/**
 * 显示PN码
 **/
void MainWindow::getPNCode()
{

}
