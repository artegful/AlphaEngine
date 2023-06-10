#include <QApplication>
#include <QtWidgets>

#include "Widgets/EditorWindow.h"
#include "rttr/property.h"

void ApplyStyles(QApplication& application)
{
    QFile file(":/dark/stylesheet.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    application.setStyleSheet(stream.readAll());
    application.setWindowIcon(QIcon(":/icons/icon.png"));
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
    ApplyStyles(application);

    EditorWindow window;
    window.setWindowState(Qt::WindowMaximized);
	window.show();

	return application.exec();
}
