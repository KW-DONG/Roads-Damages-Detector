#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QQuickWindow>

class FramelessPrivate;

class FramelessWindow : public QQuickWindow
{
    Q_OBJECT
public:
    explicit FramelessWindow(QWindow *parent = nullptr);
    ~FramelessWindow();

    Q_INVOKABLE void setTitleItem(QQuickItem* item);

protected:
    void showEvent(QShowEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    FramelessPrivate *d;
};

#endif // FRAMELESSWINDOW_H
