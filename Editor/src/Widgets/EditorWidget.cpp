#include "EditorWidget.h"

#include "Windows/QtWidgetWindow.h"
#include "Render/API.h"
#include "Core/Config.h"
#include "Layers/GameLayer.h"

EditorWidget::EditorWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	setFocusPolicy(Qt::ClickFocus);
}

void EditorWidget::initializeGL()
{
	engineWindow.reset(new QtWidgetWindow(*this));

	engine = new Alpha::Engine({ 600, 400, Alpha::API::OpenGL });
	engine->SetCustomWindow(engineWindow);
	engine->Initialize();
	engine->GetGameLayer().SetMode(Alpha::GameMode::Editor);
}

void EditorWidget::paintGL()
{
	engine->Update();
}

void EditorWidget::showEvent(QShowEvent* event)
{
	QOpenGLWidget::showEvent(event);


}

void EditorWidget::resizeEvent(QResizeEvent* event)
{
	QOpenGLWidget::resizeEvent(event);

	engineWindow->WindowResized(event);
}

void EditorWidget::keyPressEvent(QKeyEvent* event)
{
	QOpenGLWidget::keyPressEvent(event);

	engineWindow->KeyPressed(event);
}

void EditorWidget::keyReleaseEvent(QKeyEvent* event)
{
	QOpenGLWidget::keyReleaseEvent(event);

	engineWindow->KeyReleased(event);
}

void EditorWidget::wheelEvent(QWheelEvent* event)
{
	QOpenGLWidget::wheelEvent(event);

	engineWindow->WheelScroll(event);
}
