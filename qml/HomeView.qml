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
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 10
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
                anchors.top: borderImage.bottom
                anchors.right: borderImage.right
                anchors.left: borderImage.left
                Layout.fillHeight: true
                anchors.topMargin: 10
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
            Text {
                color: "#ffffff"
                text: "Device"
                font.family: "Microsoft YaHei"
                font.pointSize: 12
            }
        }
    }
}
