#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window),
    iPageIndex(INIT)
{
    ui->setupUi(this);
    connect(ui->NavBar, &NavigationBar::homeClicked, this, &Window::onHomeClicked);
    connect(ui->NavBar, &NavigationBar::taskClicked, this, &Window::onTaskClicked);
    connect(ui->NavBar, &NavigationBar::resultClicked, this, &Window::onResultClicked);
    connect(ui->NavBar, &NavigationBar::settingClicked, this, &Window::onSettingClicked);
    onHomeClicked();
}

Window::~Window()
{
    delete ui;
}

void Window::onHomeClicked()
{
    if (iPageIndex != HOME)
    {
        iPageIndex = HOME;
        ui->homePage->show();
        ui->taskList->hide();
        ui->configPage->hide();
        ui->resultPage->hide();
        ui->settingPage->hide();
    }
}

void Window::onTaskClicked()
{
    if (iPageIndex != TASK)
    {
        iPageIndex = TASK;
        ui->homePage->hide();
        ui->taskList->show();
        ui->configPage->show();
        ui->resultPage->hide();
        ui->settingPage->hide();
    }
}

void Window::onResultClicked()
{
    if (iPageIndex != RESULT)
    {
        iPageIndex = RESULT;
        ui->homePage->hide();
        ui->taskList->hide();
        ui->configPage->hide();
        ui->resultPage->show();
        ui->settingPage->hide();
    }
}

void Window::onSettingClicked()
{
    if (iPageIndex != SETTING)
    {
        iPageIndex = SETTING;
        ui->homePage->hide();
        ui->taskList->hide();
        ui->configPage->hide();
        ui->resultPage->hide();
        ui->settingPage->show();
    }
}
