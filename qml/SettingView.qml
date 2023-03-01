import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Item {
    property int index: 0
    property string filePath: ""

    ScrollView {
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 20
        width: parent.width
        height: parent.height
        clip: true

        ColumnLayout {
            anchors.fill: parent
            spacing: 5
            Text {
                text: qsTr("Setting")
                color: "#ffffff"
                font.pointSize: 18
                font.family: "Microsoft YaHei"
            }
            Item {
                height: 10
            }
            Text {
                text: qsTr("Path")
                font.pointSize: 14
                color: "#ffffff"
                font.family: "Microsoft YaHei"
            }
            Item {
                height: 5
            }

            Text {
                text: qsTr("Log path")
                font.pointSize: 11
                color: "#ffffff"
                font.family: "Microsoft YaHei"
            }
            Row {
                spacing: 10
                TextField {
                    implicitWidth: 300
                    implicitHeight: 31
                    font.family: "Arial"
                }
                Button {
                    text: qsTr("Select")
                    font.family: "Microsoft YaHei"
                    onClicked: {
                        index = 1
                        fds.open()
                    }
                }
            }
            Item {
                height: 5
            }
            Text {
                color: "#ffffff"
                text: qsTr("图片路径")
                font.pointSize: 11
                font.family: "Microsoft YaHei"
            }
            Row {
                spacing: 10
                TextField {
                    implicitWidth: 300
                    implicitHeight: 31
                    font.family: "Arial"
                    text: jobList.imgPath
                    onEditingFinished: {
                        jobList.imgPath = text
                        focus = true
                    }
                }
                Button {
                    text: qsTr("选择")
                    font.family: "Microsoft YaHei"
                    onClicked: {
                        index = 2
                        fds.open()
                    }
                }
            }
            Item {
                height: 5
            }
            Text {
                color: "#ffffff"
                text: qsTr("结果路径")
                font.pointSize: 11
                font.family: "Microsoft YaHei"
            }
            Row {
                spacing: 10
                TextField {
                    implicitWidth: 300
                    implicitHeight: 31
                    font.family: "Arial"
                    text: jobList.resultPath
                    onEditingFinished: {
                        jobList.resultPath = text
                        focus = true;
                    }
                }

                Button {
                    text: qsTr("选择")
                    font.family: "Microsoft YaHei"
                    onClicked: {
                        index = 3
                        fds.open()
                    }
                }
            }
            Item {
                height: 20
            }
            Text {
                color: "#ffffff"
                text: qsTr("数据格式设置")
                font.pointSize: 14
                font.family: "Microsoft YaHei"
            }
            Item {
                height: 5
            }
            Text {
                color: "#ffffff"
                text: qsTr("Long")
                font.pointSize: 11
                font.family: "Microsoft YaHei"
            }
            ComboBox {
                model: ListModel {
                    ListElement {
                        text: qsTr("AB CD")
                    }
                    ListElement {
                        text: qsTr("CD AB")
                    }
                    ListElement {
                        text: qsTr("BA DC")
                    }
                    ListElement {
                        text: qsTr("DC BA")
                    }
                }
            }

            Item {
                height: 5
            }
            Text {
                color: "#ffffff"
                text: qsTr("Float")
                font.pointSize: 11
                font.family: "Microsoft YaHei"
            }
            ComboBox {
                model: ListModel {
                    ListElement {
                        text: qsTr("AB CD")
                    }
                    ListElement {
                        text: qsTr("CD AB")
                    }
                    ListElement {
                        text: qsTr("BA DC")
                    }
                    ListElement {
                        text: qsTr("DC BA")
                    }
                }
            }
            Item {
                height: 5
            }
            Text {
                color: "#ffffff"
                text: qsTr("Double")
                font.pointSize: 11
                font.family: "Microsoft YaHei"
            }
            ComboBox {
                implicitWidth: 150
                implicitHeight: 30
                model: ListModel {
                    ListElement {
                        text: qsTr("AB CD EF GH")
                    }
                    ListElement {
                        text: qsTr("GH EF CD AB")
                    }
                    ListElement {
                        text: qsTr("BA DC FE HG")
                    }
                    ListElement {
                        text: qsTr("HG FE DC BA")
                    }
                }
            }

        }
    }
    FileDialog {
        id: fds
        selectFolder: true
        onAccepted: {
            if (index === 1)
            {
                filePath = fds.folder
                jobList.setLogPath(filePath.substring(8, fds.folder.length))
            }
            else if (index === 2)
            {
                filePath = fds.folder
                jobList.setImgPath(filePath.substring(8, fds.folder.length))
            }
            else if (index === 3)
            {
                filePath = fds.folder
                jobList.setResultPath(filePath.substring(8, fds.folder.length))
            }
        }
        onRejected: {

        }
    }
}
