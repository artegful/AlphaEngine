#pragma once

#include "BaseEdit.h"
#include <QColor>
#include "glm/glm.hpp"

class ColorEdit : public BaseEdit
{
public:
	ColorEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent);

    void Update() override;
    void SetColor(const QColor& color);
    void SetColor(const glm::vec4& color);

public slots:
    void OnColorUpdate();
    void OnButtonPressed();

private:
    static constexpr int MAX_CHANNEL_VALUE = 255;

    QPushButton* colorButton;

    QColor GetCurrentColor();
    void SetButtonColor(const QColor& color);
    QColor ConvertColor(const glm::vec4 color);
    glm::vec4 ConvertColor(const QColor& color);
};

