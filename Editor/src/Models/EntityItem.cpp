#include "EntityItem.h"

EntityItem::EntityItem(const QVector<QVariant>& data, EntityItem* parentItem) :
	itemData(data), parent(parentItem)
{ }

EntityItem::~EntityItem()
{
	qDeleteAll(childItems);
}

void EntityItem::appendChild(EntityItem* child)
{
	childItems.append(child);
}

EntityItem* EntityItem::child(int row)
{
	if (row < 0 || row >= childItems.size())
		return nullptr;
	return childItems.at(row);
}

int EntityItem::childCount() const
{
	return childItems.count();
}

int EntityItem::columnCount() const
{
	return itemData.count();
}

QVariant EntityItem::data(int column) const
{
	return QVariant();
}

int EntityItem::row() const
{
	if (parent)
		return parent->childItems.indexOf(const_cast<EntityItem*>(this));

	return 0;
}

EntityItem* EntityItem::parentItem()
{
	return parent;
}
