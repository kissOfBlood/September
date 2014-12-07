#ifndef LISTFILEMODEL_H
#define LISTFILEMODEL_H

#include "assistant/coreEditor/coreeditor.h"
#include <QObject>
#include <QAbstractListModel>
#include <QVariant>
#include <QModelIndex>
#include <QString>
#include <QList>
#include <QGraphicsScene>
#include <tuple>

#include <QtCore>

class ListFileModel : public QAbstractListModel
{
    Q_OBJECT

    using SceneStyle    = QGraphicsScene;
    using SceneUI       = QGraphicsScene;
public:
    explicit ListFileModel(QObject* parent = nullptr);
    ~ListFileModel() override = default;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    void addItem(const QString& file, CoreEditor* coreEditor, SceneStyle* sceneStyle, SceneUI* sceneUI);
    void removeItem(int row);
    std::tuple<CoreEditor*, SceneStyle*, SceneUI*> getItem(int row) const;
    QModelIndex getModelIndex(int row) const;

private:
    struct Item
    {
        Item() = default;

        QString         file;
        CoreEditor      *coreEditor = nullptr;
        SceneStyle      *sceneStyle = nullptr;
        SceneUI         *sceneUI    = nullptr;
    };
    QList<Item>     m_item_;
};

#endif // LISTFILEMODEL_H
