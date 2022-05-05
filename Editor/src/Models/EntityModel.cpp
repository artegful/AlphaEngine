#include "EntityModel.h"

#include "Scene/Scene.h"
#include "ECS/Entity.h"
#include "Components/NameComponent.h"

EntityModel::EntityModel(Alpha::Scene* scene) :
    currentScene(scene)
{ 
    entities = QVector<Alpha::Entity>::fromStdVector(currentScene->GetAllEntities());
}

EntityModel::~EntityModel()
{ }

void EntityModel::ChangeScene(Alpha::Scene* scene)
{
    currentScene = scene;

    beginResetModel();
    entities = QVector<Alpha::Entity>::fromStdVector(currentScene->GetAllEntities());
    endResetModel();
}

bool EntityModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    beginInsertRows(parent, position, position + rows - 1);

    for (int row = 0; row < rows; ++row) 
    {
        currentScene->DestroyEntity(entities[position]);
        entities.removeAt(position);
    }

    endInsertRows();
    return true;
}

QVariant EntityModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= entities.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return QString::fromStdString(entities[index.row()].GetComponent<Alpha::NameComponent>().Name);
    }

    return QVariant();
}

bool EntityModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        entities[index.row()].GetComponent<Alpha::NameComponent>().Name = value.toString().toStdString();
        dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags EntityModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant EntityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex EntityModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    return createIndex(row, column, (void*) &entities[row]);
}

QModelIndex EntityModel::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int EntityModel::rowCount(const QModelIndex& parent) const
{
    if (parent == QModelIndex())
    {
       return entities.size();
    }

    return 0;
}

int EntityModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

void EntityModel::Remove(QModelIndexList& indexes)
{
    qSort(indexes.begin(), indexes.end(), qGreater<QModelIndex>());

    beginRemoveRows(indexes.first().parent(), indexes.last().row(), indexes.first().row());
    for (auto it = indexes.begin(); it != indexes.end(); it++)
    {
        currentScene->DestroyEntity(entities[it->row()]);
        entities.erase(entities.begin() + it->row());
    }
    endRemoveRows();
}

void EntityModel::Create()
{
    beginInsertRows(QModelIndex(), entities.size(), entities.size());

    Alpha::Entity entity = currentScene->CreateEntity();
    entities.push_back(entity);

    endInsertRows();
}

Alpha::Entity& EntityModel::GetEntity(QModelIndex index)
{
    return entities[index.row()];
}

Alpha::Scene* EntityModel::GetCurrentScene() const
{
    return currentScene;
}
