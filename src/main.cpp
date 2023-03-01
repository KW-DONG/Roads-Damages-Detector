#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "tasklistmodel.h"
#include "resultlistmodel.h"
#include "qpaintitem.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QCoreApplication::setOrganizationName("Some organization");
    //QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Universal");
    qmlRegisterType<TaskListModel>("TaskListModel", 1, 0, "TaskListModel");
    qmlRegisterType<TaskListModel>("ResultListModel", 1, 0, "ResultListModel");
    qmlRegisterType<PaintItem>("PaintItemModule",1,0,"PaintItem");

    TaskListData taskListData;
    ResultListData resultListData;

    QQmlApplicationEngine engine;
    QQmlContext *root = engine.rootContext();
    root->setContextProperty("taskListData",&taskListData);
    root->setContextProperty("resultListData", &resultListData);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                    &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
