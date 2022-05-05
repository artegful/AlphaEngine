#include "ColorEdit.h"

#include <QColorDialog>
#include "StandardEditLayout.h"

ColorEdit::ColorEdit(const rttr::instance& instance, const rttr::property& property, QWidget* parent) : BaseEdit(instance, property, parent)
{
    colorButton = new QPushButton(this);
	connect(colorButton, &QPushButton::clicked, this, &ColorEdit::OnButtonPressed);

    StandardEditLayout* layout = new StandardEditLayout(property, this);
    layout->addWidget(colorButton);

    setLayout(layout);
    Update();
}

void ColorEdit::Update()
{
    QColor currentColor = GetCurrentColor();

    SetButtonColor(currentColor);
}

void ColorEdit::OnButtonPressed()
{
    QColor currentColor = GetCurrentColor();
    QColor newColor = QColorDialog::getColor(currentColor, parentWidget(), tr("Color"), QColorDialog::ShowAlphaChannel);

    if (newColor.isValid())
    {
        glm::vec4 newEngineColor = ConvertColor(newColor);
        SetValue(newEngineColor);
        SetButtonColor(newColor);
    }
}

QColor ColorEdit::GetCurrentColor()
{
    glm::vec4 engineColor = GetValue<glm::vec4>();
    QColor editorColor = ConvertColor(engineColor);

    return editorColor;
}

void ColorEdit::SetButtonColor(const QColor& color)
{
    colorButton->setStyleSheet("background-color: " + color.name());
}

QColor ColorEdit::ConvertColor(const glm::vec4 color)
{
    return QColor(MAX_CHANNEL_VALUE * color.x, MAX_CHANNEL_VALUE * color.y,
        MAX_CHANNEL_VALUE * color.z, MAX_CHANNEL_VALUE * color.a);
}

glm::vec4 ColorEdit::ConvertColor(const QColor& color)
{
    QRgb rgba = color.rgba();

    return { static_cast<float>(qRed(rgba)) / MAX_CHANNEL_VALUE, static_cast<float>(qGreen(rgba)) / MAX_CHANNEL_VALUE, 
        static_cast<float>(qBlue(rgba)) / MAX_CHANNEL_VALUE, static_cast<float>(qAlpha(rgba)) / MAX_CHANNEL_VALUE };
}
