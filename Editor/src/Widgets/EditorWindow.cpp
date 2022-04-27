#include "EditorWindow.h"

#include <QtWidgets>
#include "EditorWidget.h"
#include "SceneHierarchyWidget.h"
#include "InspectorWidget.h"

#include "Core/Engine.h"
#include "Layers/GameLayer.h"
#include "Layers/GameMode.h"

EditorWindow::EditorWindow() : QMainWindow()
{
    EditorWidget* editor = new EditorWidget();

    editor->setFocus();
    setCentralWidget(editor);

    QWidget* widget = new QWidget(this);

    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    CreateAssetsExplorer();
    CreateSceneHierarchy();
    CreateInspector();
    CreateActions();
    CreateToolBar();

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
    connect(hierarchy, &SceneHierarchyWidget::SelectionCleared, inspector, &InspectorWidget::OnSelectionCleared);

    inspectorDock->setWidget(inspector);
    inspector->hide();

    inspectorDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, inspectorDock);
}

void EditorWindow::CreateActions()
{
    openSceneAction = new QAction(tr("&Open"), this);
    openSceneAction->setToolTip(tr("Open Scene(Ctrl+O)"));
    openSceneAction->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(openSceneAction, &QAction::triggered, this, &EditorWindow::OnOpenScene);

    saveAsSceneAction = new QAction(tr("&Save As"), this);
    saveAsSceneAction->setToolTip(tr("Save Scene(Ctrl+S)"));
    saveAsSceneAction->setShortcut(Qt::CTRL + Qt::Key_S);
    connect(saveAsSceneAction, &QAction::triggered, this, &EditorWindow::OnSaveAsScene);

    newSceneAction = new QAction(tr("&New"), this);
    newSceneAction->setToolTip(tr("Create New Scene(Ctrl+N)"));
    newSceneAction->setShortcut(Qt::CTRL + Qt::Key_N);
        connect(newSceneAction, &QAction::triggered, this, &EditorWindow::OnNewScene);

    sceneMenu = this->menuBar()->addMenu(tr("&Scene"));
    sceneMenu->addAction(openSceneAction);
    sceneMenu->addAction(saveAsSceneAction);
    sceneMenu->addAction(newSceneAction);
}

void EditorWindow::CreateToolBar()
{
    toolBar = addToolBar(tr("tools"));

    toolBar->addWidget(CreateSpacerWidget());

    playAction = new QAction(QIcon("icons/play.png"), tr("&Play"), toolBar);
    playAction->setShortcut(Qt::CTRL + Qt::Key_P);
    playAction->setCheckable(true);
    playAction->setStatusTip(tr("Toggle play mode"));
    connect(playAction, &QAction::triggered, this, &EditorWindow::OnPlayModeToggled);
    toolBar->addAction(playAction);

    toolBar->addWidget(CreateSpacerWidget());
}

QWidget* EditorWindow::CreateSpacerWidget()
{
    QWidget* spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);

    return spacerWidget;
}

void EditorWindow::OnOpenScene()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Scene"), 
        tr("assets/scenes"), "Scene files (*.scene)");

    if (!filePath.isEmpty())
    {
        hierarchy->OpenScene(filePath);
    }
}

void EditorWindow::OnSaveAsScene()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Scene"),
        tr("assets/scenes"), "Scene files (*.scene)");

    if (!filePath.isEmpty())
    {
        hierarchy->SaveScene(filePath);
    }
}

void EditorWindow::OnNewScene()
{
    hierarchy->CreateNewScene();
}

void EditorWindow::OnPlayModeToggled()
{
    Alpha::GameMode mode = playAction->isChecked() ? Alpha::GameMode::Game : Alpha::GameMode::Editor;

    Alpha::Engine::Get()->GetGameLayer().SetMode(mode);
}
