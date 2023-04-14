import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Window 2.10
import QtQuick.Layouts 1.10
import TaskListModel 1.0

Item {
    property string baseColor: "#252423"
    property string highlightColor: "#2e2f30"
    property string selectedColor2: "#1e2f31"
    property string selectedColor: "gray"

    Rectangle {
        id: titleRect
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        height: 40
        color: baseColor
        border.width: 1
        z: 999
        Text {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.pointSize: 12
            font.family: "Microsoft YaHei"
            text: qsTr("Task List")
            color: "#ffffff"
        }
    }

    Rectangle {
        id: addRect
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width
        height: 50
        color: "#000000"

        MouseArea {
            id: addProcessArea
            anchors.fill: parent
            anchors.margins: 1
            Rectangle {
                anchors.fill: parent
                color: parent.containsMouse? highlightColor: baseColor
                Text {
                    text: "+ Add Task"
                    font.bold: true
                    font.pointSize: 12
                    font.family: "Microsoft YaHei"
                    anchors.centerIn: parent
                    color: "#ffffff"
                }
            }
            onClicked: {
                taskListData.addTask()
            }
        }
    }

    Rectangle {
        id: listRect
        width: parent.width
        color: "#000000"
        anchors.top: titleRect.bottom
        anchors.left: parent.left
        anchors.bottom: addRect.top

        Rectangle {
            id: taskListRect
            anchors.fill: parent
            anchors.margins: 1
            color: baseColor

            ListView {
                id: taskView
                anchors.fill: parent
                delegate: Item {
                    id: taskItem
                    width: taskListRect.width
                    height: 40
                    MouseArea {
                        id: taskItemMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton
                        Rectangle {
                            id: taskElementRect
                            anchors.fill: parent
                            color: taskView.currentIndex === index ? selectedColor : parent.containsMouse ? highlightColor : "black"
                            Text {
                                anchors.fill: parent
                                text: title
                                color: "#ffffff"
                                font.pointSize: 12
                                font.family: "Microsoft YaHei"
                            }
                            MouseArea {
                                anchors.right: parent.right
                                anchors.top: parent.top
                                width: parent.height / 2
                                height: parent.height / 2
                                visible: taskItemMouseArea.containsMouse
                                hoverEnabled: true
                                Image {
                                    anchors.fill: parent
                                    anchors.margins: 2
                                    source: parent.containsMouse ? "../icon/delete_white.png" : "../icon/delete_gray.png"
                                }
                                onClicked: {
                                    taskListData.removeTask(index)
                                }
                            }
                        }

                        onClicked: {
                            taskView.currentIndex = index
                            taskListData.index = index
                        }
                    }
                }
                model: TaskListModel {
                    id: taskListModel
                    list: taskListData
                }
            }
        }
    }
}


