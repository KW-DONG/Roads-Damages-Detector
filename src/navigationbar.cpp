#include "navigationbar.h"
#include "ui_navigationbar.h"

NavigationBar::NavigationBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationBar)
{
    ui->setupUi(this);
    connect(ui->HomeButton, &QPushButton::clicked, this, [=](){emit homeClicked();});
    connect(ui->TaskButton, &QPushButton::clicked, this, [=](){emit taskClicked();});
    connect(ui->ResultButton, &QPushButton::clicked, this, [=](){emit resultClicked();});
    connect(ui->SettingButton, &QPushButton::clicked, this, [=](){emit settingClicked();});
}

NavigationBar::~NavigationBar()
{
    delete ui;
}
