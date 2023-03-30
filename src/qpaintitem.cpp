#include "qpaintitem.h"
#include <iostream>
#include <QTimer>
#include <QThread>

PaintItem::PaintItem(QQuickPaintedItem *parent) : QQuickPaintedItem(parent)
{
    setFlag(ItemHasContents, true);
}

PaintItem::~PaintItem()
{
    std::cout << "paint item destroyed" << std::endl;
}

void PaintItem::updateImage(const QImage &image)
{
    m_imageThumb = image;
    emit widthChanged();
    emit heightChanged();
    update();

    //std::cout << "paint item update" << std::endl;
}

/*
QSGNode * PaintItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    auto node = dynamic_cast<QSGSimpleTextureNode *>(oldNode);

    if(!node){
        node = new QSGSimpleTextureNode();
    }

    QSGTexture *m_texture = window()->createTextureFromImage(m_imageThumb, QQuickWindow::TextureIsOpaque);
    node->setOwnsTexture(true);
    node->setRect(boundingRect());
    node->markDirty(QSGNode::DirtyForceUpdate);
    node->setTexture(m_texture);
    return node;
}
*/

void PaintItem::paint(QPainter *painter)
{
    painter->drawImage(this->boundingRect(), m_imageThumb);
}

int PaintItem::getHeight()
{
    return m_imageThumb.height();
}

int PaintItem::getWidth()
{
    return m_imageThumb.width();
}


