import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import PaintItemModule 1.0

Item {
    id: homeItem
    RowLayout {
        anchors.fill: parent
        spacing: 20
        ColumnLayout {
            spacing: 10
            Rectangle {
                id: borderImage
                color: "darkslateblue"
                implicitWidth: homeItem.width > 580 ? homeItem.width - 280 : 300
                implicitHeight: homeItem.height * 0.95
                PaintItem {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.height < parent.width / 4 * 3 ? (parent.height / 3 * 4 - 4) : (parent.width - 4)
                    height: parent.height < parent.width / 4 * 3 ? (parent.height - 4) : (parent.width / 4 * 3 - 4)
                    img: monitor.img
                    antialiasing: true
                }
            }
        }
        ColumnLayout {
            Layout.fillHeight: true
            spacing: 10
            Text {
                color: "#ffffff"
                text: "Result"
                font.family: "Microsoft YaHei"
                font.pointSize: 20
            }
            Rectangle {
                implicitHeight: 100
                ScrollView {
                    anchors.fill: parent
                    ColumnLayout
                    {
                        anchors.fill: parent
                        Row {
                            spacing: 10
                            Text {
                                color: "#ffffff"
                                text: "GNSS: "
                                font.family: "Microsoft YaHei"
                                font.pointSize: 12
                            }
                            Text {
                                color: "#ffffff"
                                text: monitor.currentGNSSStr
                                font.family: "Microsoft YaHei"
                                font.pointSize: 12
                            }
                        }
                        Row {
                            spacing: 10
                            Text {
                                color: "#ffffff"
                                text: "Confidence: "
                                font.family: "Microsoft YaHei"
                                font.pointSize: 12
                            }
                            Text {
                                color: "#ffffff"
                                text: monitor.currentConfidenceStr
                                font.family: "Microsoft YaHei"
                                font.pointSize: 12
                            }
                        }
                        Row {
                            spacing: 10
                            Text {
                                color: "#ffffff"
                                text: "Classification: "
                                font.family: "Microsoft YaHei"
                                font.pointSize: 12
                            }
                            Text {
                                color: "#ffffff"
                                text: monitor.currentClassificationStr
                                font.family: "Microsoft YaHei"
                                font.pointSize: 12
                            }
                        }
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
                id: taskComboBox
                implicitWidth: 200
                model: monitor.taskList
                enabled: !monitor.run
                onCurrentIndexChanged: {
                    monitor.currentTask = currentIndex
                }
            }

            Button {
                implicitHeight: 50
                implicitWidth: parent.width
                text: monitor.run ? qsTr("Stop") : qsTr("Start")
                enabled: taskComboBox.currentIndex != -1
                onClicked: {
                    monitor.runButton()
                }
            }
        }
    }
}
