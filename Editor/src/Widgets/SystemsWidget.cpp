#include "SystemsWidget.h"

#include "rttr/type.h"
#include "ECS/SceneSystem.h"
#include "Models/SystemModel.h"

SystemsWidget::SystemsWidget(const QString& title, QWidget* parent) : QDockWidget(title, parent)
{
    setMinimumWidth(200);

	listView = new QListView(this);
	listView->setContextMenuPolicy(Qt::ActionsContextMenu);
	listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	setWidget(listView);

	QAction* deleteEntityAction = new QAction(tr("Delete"));
	connect(deleteEntityAction, &QAction::triggered, this, &SystemsWidget::OnRightClickDelete);
	listView->addAction(deleteEntityAction);

	QAction* createEntityAction = new QAction(tr("Create Empty"));
	connect(createEntityAction, &QAction::triggered, this, &SystemsWidget::OnRightClickCreate);
	listView->addAction(createEntityAction);
}

void SystemsWidget::InitScene(Alpha::Scene* scene)
{
	systemModel = new SystemModel(scene, this);
	listView->setModel(systemModel);
}

void SystemsWidget::SetScene(Alpha::Scene* scene)
{
	listView->selectionModel()->clearSelection();

	systemModel->ChangeScene(scene);
}

void SystemsWidget::OnRightClickCreate()
{
	std::vector<rttr::type> types = rttr::type::get<Alpha::SceneSystem>().get_derived_classes();

	QStringList list;

	for (rttr::type type : types)
	{
		list.append(QString::fromStdString(type.get_name()));
	}

	if (list.empty())
	{
		return;
	}

	bool ok;
	QString item = QInputDialog::getItem(this, tr("Select system"),
		tr("System:"), list, 0, false, &ok);

	if (ok && !item.isEmpty())
	{
		systemModel->Create(item.toStdString());
	}
}

void SystemsWidget::OnRightClickDelete()
{
	if (!listView->selectionModel() || !listView->selectionModel()->hasSelection())
	{
		return;
	}

	QModelIndexList indexes = listView->selectionModel()->selectedIndexes();

	if (!listView->selectionModel()->hasSelection())
	{
		return;
	}

	systemModel->Remove(indexes);
}
