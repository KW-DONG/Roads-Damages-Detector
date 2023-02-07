#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

enum
{
    INIT,
    HOME,
    TASK,
    RESULT,
    SETTING
};

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

public slots:
    void onHomeClicked();
    void onTaskClicked();
    void onResultClicked();
    void onSettingClicked();

private:
    Ui::Window *ui;
    int iPageIndex;
};

#endif // WINDOW_H
