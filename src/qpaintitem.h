#ifndef QPAINTITEM_H
#define QPAINTITEM_H

#include <QQuickPaintedItem>
#include <QSGNode>
#include <QSGSimpleRectNode>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QImage>
#include <QPainter>


class PaintItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QImage img WRITE updateImage)
    Q_PROPERTY(int imgWidth READ getWidth NOTIFY widthChanged)
    Q_PROPERTY(int imgHeight READ getHeight NOTIFY heightChanged)

public:
    explicit PaintItem(QQuickItem *parent = nullptr);
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
    //void paint(QPainter *painter);
private:
    QImage m_imageThumb;
};





#endif
