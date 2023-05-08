#include "QtWidgetWindow.h"

#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/MouseScrolledEvent.h"
#include "Events/WindowResizedEvent.h"
#include <Events/MouseMovedEvent.h>
#include <Events/MouseButtonPressedEvent.h>
#include <Events/MouseButtonReleasedEvent.h>

QtWidgetWindow::QtWidgetWindow(EditorWidget& widget) : 
    widget(widget)
{ }

void QtWidgetWindow::Initialize()
{
    MakeContextCurrent();

    renderContext.reset(Alpha::RenderContext::Create());
    renderContext->Initialize(nullptr);
}

void QtWidgetWindow::Update()
{ }

void QtWidgetWindow::SwapBuffers()
{ }

void QtWidgetWindow::SetEventCallback(std::function<void(Alpha::Event&)> callback)
{
    eventCallback = callback;
}

void QtWidgetWindow::MakeContextCurrent()
{
    widget.makeCurrent();
}

bool QtWidgetWindow::ShouldClose() const
{
    return false;
}

int QtWidgetWindow::GetWidth() const
{
    return widget.size().width();
}

int QtWidgetWindow::GetHeight() const
{
    return widget.size().height();
}

void QtWidgetWindow::UpdateMousePosition(QPoint position)
{
    Alpha::MouseMovedEvent mouseEvent(glm::vec2(position.x(), position.y()));
    eventCallback(mouseEvent);
}

void QtWidgetWindow::WindowResized(QResizeEvent* event)
{
    Alpha::WindowResizedEvent engineEvent(event->size().width(), event->size().height());
    eventCallback(engineEvent);
}

void QtWidgetWindow::KeyPressed(QKeyEvent* event)
{
    Alpha::KeyPressedEvent engineEvent(event->key());
    eventCallback(engineEvent);
}

void QtWidgetWindow::KeyReleased(QKeyEvent* event)
{
    Alpha::KeyReleasedEvent engineEvent(event->key());
    eventCallback(engineEvent);
}

void QtWidgetWindow::WheelScroll(QWheelEvent* event)
{
    Alpha::MouseScrolledEvent engineEvent(0, static_cast<float>(event->delta()) / 20.0f);
    eventCallback(engineEvent);
}

void QtWidgetWindow::MousePressed(QMouseEvent* event)
{
    int code = static_cast<int>(event->button());
    int targetlevel = 0;
    while (code >>= 1) ++targetlevel;

    Alpha::MouseButtonPressedEvent mouseEvent(targetlevel);
    eventCallback(mouseEvent);
}

void QtWidgetWindow::MouseReleased(QMouseEvent* event)
{
    int code = static_cast<int>(event->button());
    int targetlevel = 0;
    while (code >>= 1) ++targetlevel;

    Alpha::MouseButtonReleasedEvent mouseEvent(targetlevel);
    eventCallback(mouseEvent);
}

void QtWidgetWindow::BindEvents()
{ }
