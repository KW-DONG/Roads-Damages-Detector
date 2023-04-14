import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Window 2.10
import QtQuick.Layouts 1.10
import QtQuick.Dialogs 1.0

Item {
    property int pathIndex: 0
    property string filePath: ""
    ScrollView {
        anchors.fill: parent
        clip: true
        visible: taskListData.size > 0

        ColumnLayout {
            anchors.fill: parent
            spacing: 7

            Text {
                color: "#ffffff"
                text: "Task"
                font.family: "Microsoft YaHei"
                font.pointSize: 24
            }
            Item {
                height:10
            }

            Text {
                color: "#ffffff"
                text: "Title"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            TextField {
                implicitWidth: 300
                text: taskListData.title
                font.family: "Microsoft YaHei"
                font.pointSize: 12
                onEditingFinished: {
                    taskListData.title = text
                    focus = false
                }
            }
            Text {
                color: "#ffffff"
                text: "Model Type"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            ComboBox {
                implicitWidth: 150
                model: ListModel {
                    ListElement { text: "YOLOV5LITE" }
                }
            }
            Text {
                color: "#ffffff"
                text: "Model Path"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            Row {
                spacing: 10
                TextField {
                    implicitWidth: 300
                    implicitHeight: 31
                    font.family: "Arial"
                    text: taskListData.modelPath
                    onTextEdited: {
                        taskListData.modelPath = text
                    }
                }
                Button {
                    text: qsTr("Select")
                    font.family: "Microsoft YaHei"
                    onClicked: {
                        pathIndex = 1
                        fds.open()
                    }
                }
            }
            Text {
                color: "#ffffff"
                text: "Weight Path"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            Row {
                spacing: 10
                TextField {
                    implicitWidth: 300
                    implicitHeight: 31
                    font.family: "Arial"
                    text: taskListData.weightPath
                    onTextEdited: {
                        taskListData.weightPath = text
                    }
                }
                Button {
                    text: qsTr("Select")
                    font.family: "Microsoft YaHei"
                    onClicked: {
                        pathIndex = 3
                        fds.open()
                    }
                }
            }
            Text {
                color: "#ffffff"
                text: "Threshold"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            TextField {
                implicitWidth: 100
                text: taskListData.threshold
                font.family: "Microsoft YaHei"
                font.pointSize: 12
                onEditingFinished: {
                    taskListData.threshold = text
                    focus = false
                }
            }

            Text {
                color: "#ffffff"
                text: "Labels"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            TextField {
                implicitWidth: 100
                text: taskListData.labels
                font.family: "Microsoft YaHei"
                font.pointSize: 12
                onEditingFinished: {
                    taskListData.labels = text
                    focus = false
                }
            }
            Item {
                implicitHeight: 30
            }
        }
    }

    Text {
        color: "#ffffff"
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 20
        font.family: "Microsoft YaHei"
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Please Add a Task")
        visible: !taskListData.size > 0
    }

    FileDialog {
        id: fds
        onAccepted: {
            if (pathIndex === 1)
                taskListData.modelPath = fds.fileUrl
            else if (pathIndex === 2)
                taskListData.classPath = fds.fileUrl
            else if (pathIndex === 3)
                taskListData.weightPath = fds.fileUrl
        }
        onRejected: {}
    }
}
