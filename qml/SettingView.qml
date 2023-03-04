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
                color: "#ffffff"
                text: qsTr("是否上电自启动")
                font.pointSize: 11
                font.family: "Microsoft YaHei"

            }
            Switch {
                id: sw1
                text: position === 0 ? qsTr("关") : qsTr("开")
                font.family: "Microsoft YaHei"
            }
            Item {
                height: 5
            }
            Text {
                color: "#ffffff"
                text: qsTr("需自启动的任务")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
            ComboBox {
                enabled: sw1.position === 1
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("相机分辨率")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
            ComboBox {
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("GPS通信模式")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
            ComboBox {
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("外部触发")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
            ComboBox {
                model: ListModel {
                    ListElement {
                        text: qsTr("是")
                    }
                    ListElement {
                        text: qsTr("否")
                    }
                }
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("GPIO端口号")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
             SpinBox {
                 font.pointSize: 10
                 implicitWidth: 200
             }
            Text {
                color: "#ffffff"
                text: qsTr("信号输出")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }


            ComboBox {
                model: ListModel {
                    ListElement {
                        text: qsTr("是")
                    }
                    ListElement {
                        text: qsTr("否")
                    }
                }
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("GPIO端口号")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
             SpinBox {
             font.pointSize: 10
             implicitWidth: 200
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
