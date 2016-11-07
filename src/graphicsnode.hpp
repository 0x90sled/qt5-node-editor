/* See LICENSE file for copyright and license details. */

#ifndef GRAPHICS_NODE_H
#define GRAPHICS_NODE_H

#include <QtCore/QRectF>
#include <QtCore/QPointF>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include "graphicsnodedefs.hpp"

class QWidget;
class QGraphicsSceneMouseEvent;
class QGraphicsTextItem;
class GraphicsDirectedEdge;
class GraphicsNodeSocket;
class QAbstractItemModel;

class QNodeEditorSocketModel;

class GraphicsNodePrivate;

class GraphicsNode : public QObject
{
    friend class QNodeEditorSocketModelPrivate; // For creating GraphicsNodes
    Q_OBJECT

public:
    QGraphicsItem *graphicsItem() const;

    QSizeF size() const;

    void setTitle(const QString &title);

    void setSize(const qreal width, const qreal height);
    void setSize(const QSizeF size);
    void setSize(const QPointF size);

    QModelIndex index() const;
    QAbstractItemModel* model() const;

    /**
        * set a regular QWidget as central widget
        */
    void setCentralWidget(QWidget *widget);

private:
    explicit GraphicsNode(QNodeEditorSocketModel* model, const QPersistentModelIndex& index, QGraphicsItem *parent = nullptr);
    virtual ~GraphicsNode();

    void update();

    GraphicsNodePrivate* d_ptr;
    Q_DECLARE_PRIVATE(GraphicsNode)
};

Q_DECLARE_METATYPE(GraphicsNode*)


#endif //GRAPHICS_NODE_H

