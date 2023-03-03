import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import PaintItemModule 1.0

Item {
    RowLayout {
        anchors.fill: parent
        spacing: 10
        ColumnLayout {
            Rectangle {
                id: borderImage
                color: "blue"
                implicitWidth: 400
                implicitHeight: 300
                /*
                PaintItem {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.height < parent.width / 4 * 3 ? (parent.height / 3 * 4) : (parent.width)
                    height: parent.height < parent.width / 4 * 3 ? (parent.height) : (parent.width / 4 * 3)
                    //anchors.fill: parent
                    //img: core.showImg
                }
                */
            }
            TextArea {
                implicitWidth: borderImage.width
                Layout.fillHeight: true
                enabled: false
            }
        }
        ColumnLayout {
            Layout.fillHeight: true
            Text {
                color: "#ffffff"
                text: "Result"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            Rectangle {
                implicitHeight: 100
                ScrollView {
                    anchors.fill: parent
                    ColumnLayout
                    {
                       anchors.fill: parent
                       Text {
                           color: "#ffffff"
                           text: "GNSS: "
                           font.family: "Microsoft YaHei"
                       }
                       Text {
                           color: "#ffffff"
                           text: "Confidence: "
                           font.family: "Microsoft YaHei"
                       }
                       Text {
                           color: "#ffffff"
                           text: "Classification: "
                           font.family: "Microsoft YaHei"
                       }


                    }
                }
            }

            Text {
                color: "#ffffff"
                text: "Device"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            Rectangle {
                ScrollView {
                    anchors.fill: parent
                    Text {

                    }


                }
            }
            Item {
                Layout.fillHeight: true
            }
            Text {
                color: "#ffffff"
                text: "Current Task"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            ComboBox {

            }
            Text {
                color: "#ffffff"
                text: "Select Image"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
            Row {
                spacing: 10
                TextField {
                    width: 200
                }
                Button {
                    text: "Select"
                }
            }
            Button {
                implicitHeight: 50
                implicitWidth: parent.width
                text: "Start"

            }
        }
        Item {
            Layout.fillWidth: true
        }
    }
}
