#pragma once

#include <QMainWindow>

namespace Alpha
{
	class Scene;
}

class SceneHierarchyWidget;
class InspectorWidget;
class SystemsWidget;
class EditorWidget;

class EditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	EditorWindow();

private:
	EditorWidget* editor;
	SceneHierarchyWidget* hierarchy;
	InspectorWidget* inspector;
	SystemsWidget* systems;
	QAction* openSceneAction;
	QAction* saveAsSceneAction;
	QAction* newSceneAction;
	QAction* playAction;
	QMenu* sceneMenu;
	QToolBar* toolBar;

	QString currentScenePath;
	Alpha::Scene* currentScene;

	void CreateAssetsExplorer();
	void CreateSceneHierarchy();
	void CreateInspector();
	void CreateActions();
	void CreateToolBar();
	void CreateSystemsEditor();
	void showEvent(QShowEvent* event);

	void OpenScene(const std::string& path);
	void SaveScene(const std::string& path);
	QWidget* CreateSpacerWidget();

private slots:
	void OnOpenScene();
	void OnSaveAsScene();
	void OnNewScene();
	void OnPlayModeToggled();
};

