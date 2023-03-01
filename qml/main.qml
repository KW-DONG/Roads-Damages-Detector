import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Universal 2.15

Window {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Universal.theme: Universal.Dark
    Universal.accent: Universal.BlueGrey
    Pane {
        anchors.fill: parent
        padding: 0
        MainForm {
            anchors.fill: parent
        }
    }


/*
    CusTitleBar {
        id: titleBar
        anchors.top: parent.top
        anchors.topMargin: Window.visibility === Window.Maximized ? 5 : 0
        anchors.left: parent.left
        anchors.leftMargin: Window.visibility === Window.Maximized ? 5 : 0
        height: 32
        width: Window.visibility === Window.Maximized ? parent.width - 10 : parent.width
        z: 99
    }
    Pane {
        x: Window.visibility === Window.Maximized ? 6 : 0
        y: Window.visibility === Window.Maximized ? 37 : 32
        height: Window.visibility === Window.Maximized ? parent.height - 42 : parent.height - 32
        padding: 0
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        topPadding: 0
        width: Window.visibility === Window.Maximized ? parent.width - 10 : parent.width


        MainForm {
            anchors.fill: parent
        }
    }
    Component.onCompleted: {
        root.setTitleItem(titleBar.blankItem)
    }
*/
}
