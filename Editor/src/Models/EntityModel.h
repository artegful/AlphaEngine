#pragma once

#include <QVector>
#include <QAbstractItemModel>

namespace Alpha
{
    class Entity;
    class Scene;
}

class EntityModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit EntityModel();
    ~EntityModel();

    bool removeRows(int position, int rows, const QModelIndex& parent);
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
        const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    Alpha::Entity& GetEntity(QModelIndex index);

private:
    Alpha::Scene* currentScene;
    QVector<Alpha::Entity> entities;
};