#include "homepage.h"
#include "./ui_homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, [=](){emit HomePage::startClicked();});
    connect(ui->stopButton, &QPushButton::clicked, this, [=](){emit HomePage::stopClicked();});
    connect(ui->readPathButton, &QPushButton::clicked, this, [=](){emit HomePage::startClicked();});
    connect(ui->taskIndex, QOverload<int>::of(&QComboBox::activated), this, [=](int index){emit HomePage::taskChanged(index);});

}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::onLiveChanged(QImage& img)
{
    ui->live->setPixmap(QPixmap::fromImage(img));
}

void HomePage::onFPSChanged(QString& str)
{
    ui->fps->setText(str);
}

void HomePage::onResultChanged(QString& str)
{
    ui->result->setText(str);
}

void HomePage::onGNSSChanged(QString& str)
{
    ui->gnss->setText(str);
}




