#pragma once

#include "Widgets/EditorWidget.h"
#include "Core/Window.h"
#include "Render/RenderContext.h"
#include "Events/Event.h"

class QtWidgetWindow : public Alpha::Window
{
public:
	QtWidgetWindow(EditorWidget& widget);

	void Initialize() override;
	void Update() override;
	void SwapBuffers() override;
	void SetEventCallback(std::function<void(Alpha::Event&)> callback) override;

	bool ShouldClose() const override;
	int GetWidth() const override;
	int GetHeight() const override;

	void UpdateMousePosition(QPoint position);

	void WindowResized(QResizeEvent* event);
	void KeyPressed(QKeyEvent* event);
	void KeyReleased(QKeyEvent* event);
	void WheelScroll(QWheelEvent* event);
	void MousePressed(QMouseEvent* event);
	void MouseReleased(QMouseEvent* event);


private:
	EditorWidget& widget;
	std::function<void(Alpha::Event&)> eventCallback;
	std::unique_ptr<Alpha::RenderContext> renderContext;

	int width;
	int height;

	void MakeContextCurrent();
	void BindEvents();
};

