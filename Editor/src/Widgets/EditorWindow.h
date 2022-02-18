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

	void CreateAssetsExplorer();
	void CreateSceneHierarchy();
	void CreateInspector();
};

