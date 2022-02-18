#include "EditorWindow.h"

#include <QtWidgets>
#include "EditorWidget.h"
#include "SceneHierarchyWidget.h"
#include "InspectorWidget.h"

EditorWindow::EditorWindow() : QMainWindow()
{
    EditorWidget* editor = new EditorWidget();
    editor->setFocus();
    setCentralWidget(editor);

    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    CreateAssetsExplorer();
    CreateSceneHierarchy();
    CreateInspector();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, editor, static_cast<void (EditorWidget::*)()>(&EditorWidget::repaint));
    timer->start(10);

    QTimer::singleShot(0, editor, SLOT(setFocus()));
}

void EditorWindow::CreateAssetsExplorer()
{
    QDockWidget* assets = new QDockWidget(tr("Assets"), this);

    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    QTreeView* tree = new QTreeView(assets);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath() + "/assets"));

    assets->setWidget(tree);

    addDockWidget(Qt::BottomDockWidgetArea, assets);
}

void EditorWindow::CreateSceneHierarchy()
{
    hierarchy = new SceneHierarchyWidget(tr("Scene Hierarchy"), this);

    hierarchy->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, hierarchy);
}

void EditorWindow::CreateInspector()
{
    QDockWidget* inspectorDock = new QDockWidget(tr("Inspector"), this);
    inspectorDock->setMinimumWidth(300);

    inspector = new InspectorWidget(this);
    connect(hierarchy, &SceneHierarchyWidget::SelectedEntityChanged, inspector, &InspectorWidget::OnSelectedEntityChanged);

    inspectorDock->setWidget(inspector);
    inspector->hide();

    inspectorDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, inspectorDock);
}
