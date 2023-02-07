#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

#include <QWidget>

namespace Ui {
class ConfigPage;
}

class ConfigPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigPage(QWidget *parent = nullptr);
    ~ConfigPage();

public slots:
    void onIndexChanged(int);



private:
    Ui::ConfigPage *ui;
    int index;
};

#endif // CONFIGPAGE_H
