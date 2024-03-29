import QtQuick 2.10
import QtQuick.Controls 2.4

Item {

    property int selection: 0
    property int rectWidth: 3
    property int rectHeight: 48
    property int imgWidth: 23
    property int imgHeight: 23

    function resetRect(){
        homeRect.visible = false
        expandRect.visible = false
        dataRect.visible = false
    }

    Rectangle {
        color: "indigo"
        anchors.fill: parent
        visible: true

        Rectangle {
            id: homeRect
            width: rectWidth
            height: rectHeight
            anchors.top: parent.top
            anchors.left: parent.left
        }
        MouseArea {
            id: homeMouseArea
            width: 48
            height: rectHeight
            hoverEnabled: true
            anchors.top: homeRect.top
            anchors.left: parent.left

            Image {
                width: imgWidth
                height: imgHeight
                anchors.centerIn: parent
                source: parent.containsMouse ? "../icon/home_white.png" : "../icon/home_gray.png"
            }
            onClicked: {
                resetRect();
                homeRect.visible = true;
                selection = 0
            }
        }

        Rectangle {
            id: expandRect
            width: rectWidth
            height: rectHeight
            anchors.top: homeRect.bottom
            anchors.left: parent.left
        }
        MouseArea {
            id: expandMouseArea
            width: 48
            height: rectHeight
            hoverEnabled: true
            anchors.top: expandRect.top
            anchors.left: parent.left

            Image {
                width: imgWidth
                height: imgHeight
                anchors.centerIn: parent
                source: parent.containsMouse ? "../icon/expand_white.png" : "../icon/expand_gray.png"
            }
            onClicked: {
                resetRect();
                expandRect.visible = true;
                selection = 1
            }
        }

        Rectangle {
            id: dataRect
            width: rectWidth
            height: rectHeight
            anchors.top: expandRect.bottom
            anchors.left: parent.left
        }
        MouseArea {
            id: dataMouseArea
            width: 48
            height: rectHeight
            hoverEnabled: true
            anchors.top: dataRect.top
            anchors.left: parent.left

            Image {
                width: imgWidth
                height: imgHeight
                anchors.centerIn: parent
                source: parent.containsMouse ? "../icon/data_white.png" : "../icon/data_gray.png"
            }
            onClicked: {
                resetRect();
                dataRect.visible = true;
                selection = 2
                resultListData.imgIdx = 0
                resultListData.index = 0
            }
        }

        MouseArea {
            id: settingMouseArea
            width: 48
            height: rectHeight
            hoverEnabled: true
            anchors.bottom: parent.bottom
            anchors.left: parent.left

            Image {
                width: imgWidth
                height: imgHeight
                anchors.centerIn: parent
                source: parent.containsMouse ? "../icon/setting_white.png" : "../icon/setting_gray.png"
            }
            onClicked: {
                resetRect()
                selection = 3
            }
        }

        Component.onCompleted: {
            homeRect.visible = true
            expandRect.visible = false
            dataRect.visible = false
        }
    }
}




