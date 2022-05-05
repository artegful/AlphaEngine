#pragma once

#include <QVector>
#include <QVariant>

class EntityItem
{
public:
    explicit EntityItem(const QVector<QVariant>& data, EntityItem* parentItem = nullptr);
    ~EntityItem();

    void appendChild(EntityItem* child);

    EntityItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    EntityItem* parentItem();

private:
    QVector<EntityItem*> childItems;
    QVector<QVariant> itemData;
    EntityItem* parent;
};

