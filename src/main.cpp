#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "tasklistmodel.h"
#include "resultlistmodel.h"
#include "qpaintitem.h"
#include "monitor.h"
#include "cusncnn.h"
#include "rtcam.h"
#include "gtu7.h"

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
    qmlRegisterType<ResultListModel>("ResultListModel", 1, 0, "ResultListModel");
    qmlRegisterType<PaintItem>("PaintItemModule",1,0,"PaintItem");

    TaskListData taskListData;
    ResultListData resultListData;
    CusNCNN imgRecog;
    Monitor monitor;
    RtCam camera;
    GTU7 gnss;
    monitor.registerResultListData(&resultListData);
    monitor.registerTaskListData(&taskListData);
    monitor.registerImgRecog(&imgRecog);
    monitor.registerCamera(&camera);
    monitor.registerGNSS(&gnss);

    QQmlApplicationEngine engine;
    QQmlContext *root = engine.rootContext();
    root->setContextProperty("taskListData",&taskListData);
    root->setContextProperty("resultListData", &resultListData);
    root->setContextProperty("monitor", &monitor);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                    &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.load(url);
    return app.exec();
}
