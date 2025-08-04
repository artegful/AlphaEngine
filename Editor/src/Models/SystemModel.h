#pragma once

#include <QVector>
#include <QAbstractItemModel>

namespace Alpha
{
    class SceneSystem;
    class Scene;
}

class SystemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SystemModel(Alpha::Scene* scene, QWidget* parent);
    ~SystemModel();

    void ChangeScene(Alpha::Scene* scene);
    bool removeRows(int position, int rows, const QModelIndex& parent);
    QVariant data(const QModelIndex& index, int role) const override;
    QModelIndex index(int row, int column,
        const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    void Remove(QModelIndexList& indexes);
    void Create(const std::string& name);

    Alpha::Scene* GetCurrentScene() const;

private:
    Alpha::Scene* currentScene;
    QVector<Alpha::SceneSystem*> systems;
    QWidget* widgetParent;
};