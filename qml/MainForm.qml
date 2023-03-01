import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import "qrc:/qml"

Item {
    anchors.fill: parent
    property int pageStatus: 0

    CusToolBar {
        id: toolBar
        width: 48
        anchors.left: parent.left
        anchors.top: parent.top
        height: parent.height
        z: 999
    }

    HomeView {
        anchors.left: toolBar.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        z: 998
        visible: toolBar.selection === 0
    }

    TaskListView {
        id: taskListView
        anchors.left: toolBar.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 4
        z: 998
        visible: toolBar.selection === 1
    }

    ConfigView {
        anchors.left: taskListView.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.leftMargin: 30
        anchors.topMargin: 50
        z: 998
        visible: toolBar.selection === 1
    }

    ResultView {
        anchors.left: toolBar.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        z: 998
        visible: toolBar.selection === 2
    }

    SettingView {
        anchors.left: toolBar.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        visible: toolBar.selection === 3
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
