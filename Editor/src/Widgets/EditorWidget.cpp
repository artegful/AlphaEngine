#include "EditorWidget.h"

#include "Windows/QtWidgetWindow.h"
#include "Render/API.h"
#include "Core/Config.h"
#include "Layers/GameLayer.h"

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data)
{
    const char* _source;
    const char* _type;
    const char* _severity;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

    default:
        _source = "UNKNOWN";
        break;
    }

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

    default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

    default:
        _severity = "UNKNOWN";
        break;
    }

    qCritical() << _type << _severity << _source  << msg;
}

EditorWidget::EditorWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	setFocusPolicy(Qt::ClickFocus);
}

void EditorWidget::initializeGL()
{
	engineWindow.reset(new QtWidgetWindow(*this));

	engine = new Alpha::Engine({ 600, 400, Alpha::API::OpenGL, Alpha::GameMode::Editor });
	engine->SetCustomWindow(engineWindow);
	engine->Initialize();

    QOpenGLExtraFunctions functions(this->context());
    functions.glDebugMessageCallback(GLDebugMessageCallback, NULL);
}

void EditorWidget::paintGL()
{
    makeCurrent();
	QPoint globalCursorPos = QCursor::pos();
	engineWindow->UpdateMousePosition(globalCursorPos);

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

void EditorWidget::mousePressEvent(QMouseEvent* eventPress)
{
	QOpenGLWidget::mousePressEvent(eventPress);

	engineWindow->MousePressed(eventPress);
}

void EditorWidget::mouseReleaseEvent(QMouseEvent* releaseEvent)
{
	QOpenGLWidget::mouseReleaseEvent(releaseEvent);

	engineWindow->MouseReleased(releaseEvent);
}
