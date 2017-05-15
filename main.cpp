#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "controller.h"

int main(int argc, char *argv[])
{


    QGuiApplication app(argc, argv);

    QScopedPointer<controller> connection(new controller);

    QQmlApplicationEngine engine;

    controller ctr;



    engine.rootContext()->setContextProperty( "crtObj", &ctr);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));





    return app.exec();
}
