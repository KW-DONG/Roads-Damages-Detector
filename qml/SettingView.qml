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
                text: qsTr("Autostart on Power On")
                font.pointSize: 11
                font.family: "Microsoft YaHei"

            }
            Switch {
                id: sw1
                text: position === 0 ? qsTr("Off") : qsTr("On")
                font.family: "Microsoft YaHei"
            }
            Item {
                height: 5
            }
            Text {
                color: "#ffffff"
                text: qsTr("Tasks to Auto-start")
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
                text: qsTr("Camera Resolution")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
            ComboBox {
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("GPS Communication Mode")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
            ComboBox {
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("External Trigger")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
            ComboBox {
                model: ListModel {
                    ListElement {
                        text: qsTr("Yes")
                    }
                    ListElement {
                        text: qsTr("No")
                    }
                }
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("GPIO Port Number")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
             SpinBox {
                 font.pointSize: 10
                 implicitWidth: 200
             }
            Text {
                color: "#ffffff"
                text: qsTr("Signal Output")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }


            ComboBox {
                model: ListModel {
                    ListElement {
                        text: qsTr("Yes")
                    }
                    ListElement {
                        text: qsTr("No")
                    }
                }
                font.pointSize: 10
                implicitWidth: 200
            }
            Text {
                color: "#ffffff"
                text: qsTr("GPIO Port Number")
                font.family: "Microsoft YaHei"
                font.pointSize: 11
            }
             SpinBox {
             font.pointSize: 10
             implicitWidth: 200
            }
            Item {
                height: 60
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
