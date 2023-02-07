#ifndef HOME_H
#define HOME_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = nullptr);
    ~HomePage();

signals:
    void startClicked();
    void stopClicked();
    void localImgChanged();
    void taskChanged(int);


public slots:
    void onLiveChanged(QImage&);
    void onFPSChanged(QString&);
    void onResultChanged(QString&);
    void onGNSSChanged(QString&);

private:
    Ui::Home *ui;
};
#endif // HOME_H
