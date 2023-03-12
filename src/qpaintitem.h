#ifndef QPAINTITEM_H
#define QPAINTITEM_H

#include <QQuickPaintedItem>
#include <QSGNode>
#include <QSGSimpleRectNode>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QImage>
#include <QPainter>
#include <QTimer>

class PaintItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage img WRITE updateImage)
    Q_PROPERTY(int imgWidth READ getWidth NOTIFY widthChanged)
    Q_PROPERTY(int imgHeight READ getHeight NOTIFY heightChanged)

public:
    explicit PaintItem(QQuickPaintedItem *parent = nullptr);
    ~PaintItem();
signals:
    void widthChanged();
    void heightChanged();

public slots:
    void updateImage(const QImage &);
    int getWidth();
    int getHeight();

protected:
    QSGNode* updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void paint(QPainter *painter) override;
private:
    QImage m_imageThumb;
    QTimer* m_timer;
};





#endif
