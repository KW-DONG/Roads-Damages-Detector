#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>

namespace Ui {
class NavigationBar;
}

class NavigationBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar();

signals:
    void homeClicked();
    void taskClicked();
    void resultClicked();
    void settingClicked();

private:
    Ui::NavigationBar *ui;
};

#endif // NAVIGATIONBAR_H
