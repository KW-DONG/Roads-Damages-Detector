import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtLocation 5.15
import QtPositioning 5.15
import PaintItemModule 1.0
import ResultListModel 1.0

Item {
    property string baseColor: "#252423"
    property string highlightColor: "#2e2f30"
    property string selectedColor2: "#1e2f31"
    property string selectedColor: "gray"
    Rectangle {
        id: resultListLabel
        width: 150
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
            text: qsTr("Result List")
            color: "#ffffff"
        }
    }

    Rectangle {
        id: resultListRect
        anchors.top: resultListLabel.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: resultListLabel.width - 2
        anchors.margins: 1
        color: baseColor

        ListView {
            id: resultView
            anchors.fill: parent
            delegate: Item {
                id: resultItem
                width: resultListRect.width
                height: 25
                MouseArea {
                    id: resultItemMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton
                    Rectangle {
                        anchors.fill: parent
                        color: resultView.currentIndex === index ? selectedColor : parent.containsMouse ? highlightColor : "black"
                        Text {
                            text: title
                            color: "#ffffff"
                            font.pointSize: 12
                            font.family: "Microsoft YaHei"
                        }
                    }
                    onClicked: {
                        console.log("result clicked")
                        resultView.currentIndex = index
                        resultListData.index = index
                    }
                }
            }
            model: ResultListModel {
                list: resultListData
            }
        }
    }

    Item {
        id: resultImgItem
        anchors.left: resultListLabel.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        ColumnLayout {
            spacing: 10
            anchors.fill: parent
            Item {
                height:10
            }

            Text {
                Layout.alignment: Qt.AlignVCenter
                ColumnLayout.leftMargin: 50
                text: resultListData.imgName
                color: "#ffffff"
                font.pointSize: 14
                font.family: "Microsoft YaHei"
            }

            RowLayout {
                MouseArea {
                    width: 40
                    height:40
                    Image {
                        anchors.fill: parent
                        source: parent.containsMouse ? "../icon/left_white.png" : "../icon/left_gray.png"
                    }
                    onClicked: {
                        if (resultListData.imgIdx > 0)
                            resultListData.imgIdx--
                    }
                }
                Rectangle {
                    id: resultImgRect
                    color: "darkslateblue"
                    Layout.fillWidth: true
                    implicitHeight: resultImgItem.height * 0.7
                    PaintItem {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.height < parent.width / 4 * 3 ? (parent.height / 3 * 4 - 4) : (parent.width - 4)
                        height: parent.height < parent.width / 4 * 3 ? (parent.height - 4) : (parent.width / 4 * 3 - 4)
                        antialiasing: true
                        img: resultListData.img
                    }
                }
                MouseArea {
                    width: 40
                    height:40
                    Image {
                        anchors.fill: parent
                        source: parent.containsMouse ? "../icon/right_white.png" : "../icon/right_gray.png"
                    }
                    onClicked: {
                        if (resultListData.imgIdx < resultListData.imgNum - 1)
                            resultListData.imgIdx++
                    }
                }
            }
            Text {
                Layout.alignment: Qt.AlignHCenter
                text: resultListData.imgShowIdx
                color: "#ffffff"
                font.pointSize: 10
                font.family: "Microsoft YaHei"
            }
            Item {
                Layout.fillHeight: true
            }
        }
    }
}
