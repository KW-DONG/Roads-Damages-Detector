import QtQuick 2.15
import QtQuick.Window 2.15

Item {
    property alias blankItem: blankItem

    Rectangle {
        id: touchBar
        height: parent.height
        width: parent.width - 3 * parent.height
        color: "#c1d2d5"
        anchors.top: parent.top
        anchors.left: parent.left
        Text {
            id: titleText
            text: qsTr("Monitor")
            font.family: "Arial"
            anchors.centerIn: parent
        }

        Item {
            id: blankItem
            anchors.fill: parent
        }
    }

    //close button
    MouseArea {
        id: imgWinClose
        hoverEnabled: true
        anchors.top: parent.top
        anchors.right: parent.right
        width: parent.height
        height: parent.height

        Rectangle {
            anchors.fill: parent
            color: parent.containsMouse ? "red" : "#c1d2d5"
            Image {
                anchors.centerIn: parent
                height: parent.height / 2
                width: parent.width / 2
                source: "qrc:/icon/close_white.png"
            }
        }

        onClicked: {
            console.log("close window==============")
            close()
        }
    }

    //max button
    MouseArea {
        id: imgWinMax
        hoverEnabled: true
        anchors.top: parent.top
        anchors.right: imgWinClose.left
        width: parent.height
        height: parent.height
        visible: Window.visibility !== Window.Maximized

        Rectangle {
            anchors.fill: parent
            color: parent.containsMouse ? "#CFD2DC" : "#c1d2d5"
            Image {
                anchors.centerIn: parent
                height: parent.height / 2
                width: parent.width / 2
                source: "qrc:/icon/max_white.png"
            }
        }
        onClicked: {
            console.log("max window==============")
            showMaximized()
        }
    }


    //normal button
    MouseArea {
        id: imgWinNorm
        hoverEnabled: true
        anchors.top: parent.top
        anchors.right: imgWinClose.left
        width: parent.height
        height: parent.height
        visible: Window.visibility === Window.Maximized

        Rectangle {
            anchors.fill: parent
            color: parent.containsMouse ? "#CFD2DC" : "#c1d2d5"
            Image {
                anchors.centerIn: parent
                height: parent.height / 2
                width: parent.width / 2
                source: "qrc:/icon/norm_white.png"
            }
        }
        onClicked: {
            console.log("max window==============")
            showNormal()
            //isMaxed = false
        }
    }

    //minimize button
    MouseArea {
        id: imgWinMini
        hoverEnabled: true
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 2 * parent.height
        width: parent.height
        height: parent.height

        Rectangle {
            anchors.fill: parent
            color: parent.containsMouse ? "#CFD2DC" : "#c1d2d5"
            Image {
                anchors.centerIn: parent
                height: parent.height / 2
                width: parent.width / 2
                source: "qrc:/icon/min_white.png"
            }
        }

        onClicked: {
            console.log("min window=================")
            showMinimized()
        }

    }





}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
