#pragma once

#include <QtCore/QIdentityProxyModel>

#include <graphicsnodesocket.hpp>

class GraphicsNode;
class QReactiveProxyModel;
class GraphicsNodeScene;

class QNodeEditorSocketModelPrivate;

//TODO move to a subclass
class QNodeEditorEdgeModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit QNodeEditorEdgeModel(QNodeEditorSocketModelPrivate* parent = Q_NULLPTR); //TODO make private
    virtual ~QNodeEditorEdgeModel();

    bool canConnect(const QModelIndex& idx1, const QModelIndex& idx2) const;
    bool connectSocket(const QModelIndex& idx1, const QModelIndex& idx2);

    QNodeEditorSocketModel* socketModel() const;

private:
    QNodeEditorSocketModelPrivate* d_ptr;
};

/**
 * Keeper/factory for the nodes and socket objects. This is the only place
 * allowed to create and destroy them.
 *
 * It might seems a little abusive to use a proxy for that, but trying to keep
 * consistency across all 4 "view" classes proved to be challenging and
 * messy. Having a central entity to do it ensure a clear and simple ownership
 * pyramid for each objects.
 *
 * TODO once the model refactoring is done, turn into a private class
 */
class QNodeEditorSocketModel : public QIdentityProxyModel
{
    Q_OBJECT
public:

    explicit QNodeEditorSocketModel(
        QReactiveProxyModel* rmodel,
        GraphicsNodeScene* scene
    );

    virtual ~QNodeEditorSocketModel();

    virtual void setSourceModel(QAbstractItemModel *sourceModel) override;

    int sourceSocketCount(const QModelIndex& idx) const;
    int sinkSocketCount(const QModelIndex& idx) const;

    QNodeEditorEdgeModel* edgeModel() const;

    QVector<GraphicsNodeSocket*> getSourceSockets(const QModelIndex& idx) const;
    QVector<GraphicsNodeSocket*> getSinkSockets(const QModelIndex& idx) const;

    GraphicsNode*       getNode(const QModelIndex& idx, bool recursive = false);
    GraphicsNodeSocket* getSourceSocket(const QModelIndex& idx);
    GraphicsNodeSocket* getSinkSocket(const QModelIndex& idx);

private:
    QNodeEditorSocketModelPrivate* d_ptr;
    Q_DECLARE_PRIVATE(QNodeEditorSocketModel)
};
