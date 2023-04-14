import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.4
import QtQuick.Controls.Universal 2.3

Window {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Monitor")

    Universal.theme: Universal.Dark
    Universal.accent: Universal.BlueGrey
    Pane {
        anchors.fill: parent
        padding: 0
        MainForm {
            anchors.fill: parent
        }
    }
}
