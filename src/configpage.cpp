#include "configpage.h"
#include "ui_configpage.h"

ConfigPage::ConfigPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigPage)
{
    ui->setupUi(this);
}

ConfigPage::~ConfigPage()
{
    delete ui;
}

void ConfigPage::onIndexChanged(int index)
{


}
