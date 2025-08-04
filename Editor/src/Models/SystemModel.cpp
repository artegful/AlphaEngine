#include "SystemModel.h"

#include "rttr/type.h"
#include "rttr/variant.h"
#include "Scene/Scene.h"
#include "ECS/SceneSystem.h"
#include "Components/NameComponent.h"
#include "ECS/SceneSystem.h"
#include <QtWidgets>

SystemModel::SystemModel(Alpha::Scene* scene, QWidget* parent) :
    currentScene(scene), widgetParent(parent)
{
    systems = QVector<Alpha::SceneSystem*>::fromStdVector(currentScene->GetAllSystems());
}

SystemModel::~SystemModel()
{
}

void SystemModel::ChangeScene(Alpha::Scene* scene)
{
    currentScene = scene;

    beginResetModel();
    systems = QVector<Alpha::SceneSystem*>::fromStdVector(currentScene->GetAllSystems());
    endResetModel();
}

bool SystemModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    beginInsertRows(parent, position, position + rows - 1);

    for (int row = 0; row < rows; row++)
    {
        currentScene->RemoveSystem(position);
        systems.removeAt(position);
    }

    endInsertRows();
    return true;
}

QVariant SystemModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= systems.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        Alpha::SceneSystem& system = *systems[index.row()];
        return QString::fromStdString(rttr::type::get(system).get_name());
    }

    return QVariant();
}

QModelIndex SystemModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    return createIndex(row, column, (void*)&systems[row]);
}

QModelIndex SystemModel::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int SystemModel::rowCount(const QModelIndex& parent) const
{
    if (parent == QModelIndex())
    {
        return systems.size();
    }

    return 0;
}

int SystemModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

void SystemModel::Remove(QModelIndexList& indexes)
{
    qSort(indexes.begin(), indexes.end(), qGreater<QModelIndex>());

    beginRemoveRows(indexes.first().parent(), indexes.last().row(), indexes.first().row());
    for (auto it = indexes.begin(); it != indexes.end(); it++)
    {
        currentScene->RemoveSystem(it->row());
        systems.erase(systems.begin() + it->row());
    }
    endRemoveRows();
}

void SystemModel::Create(const std::string& name)
{
    rttr::type newType = rttr::type::get_by_name(name.c_str());

    for (Alpha::SceneSystem* system : systems)
    {
        if (rttr::type::get(system) == newType)
        {
            return;
        }
    }

    rttr::variant instance = newType.create({ currentScene });
    Alpha::SceneSystem* newSystem = instance.get_value<Alpha::SceneSystem*>();

    beginInsertRows(QModelIndex(), systems.size(), systems.size());

    systems.push_back(newSystem);
    currentScene->AddSystem(newSystem);

    endInsertRows();
}

Alpha::Scene* SystemModel::GetCurrentScene() const
{
    return currentScene;
}
