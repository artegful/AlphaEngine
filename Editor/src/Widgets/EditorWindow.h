#pragma once

#include <QMainWindow>

class SceneHierarchyWidget;
class InspectorWidget;

class EditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	EditorWindow();

private:
	SceneHierarchyWidget* hierarchy;
	InspectorWidget* inspector;
	QAction* openSceneAction;
	QAction* saveAsSceneAction;
	QAction* newSceneAction;
	QAction* playAction;
	QMenu* sceneMenu;
	QToolBar* toolBar;

	void CreateAssetsExplorer();
	void CreateSceneHierarchy();
	void CreateInspector();
	void CreateActions();
	void CreateToolBar();

	QWidget* CreateSpacerWidget();

private slots:
	void OnOpenScene();
	void OnSaveAsScene();
	void OnNewScene();
	void OnPlayModeToggled();
};

