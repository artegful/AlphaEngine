#pragma once

#include <QtWidgets>
#include "Core/Engine.h"

class QtWidgetWindow;

class EditorWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    EditorWidget(QWidget *parent = Q_NULLPTR);

    void initializeGL() override;
    void paintGL() override;

protected:
    void showEvent(QShowEvent* event);

    void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* eventPress);
    void mouseReleaseEvent(QMouseEvent* releaseEvent);

private:
    std::shared_ptr<QtWidgetWindow> engineWindow;
    Alpha::Engine *engine;
};
