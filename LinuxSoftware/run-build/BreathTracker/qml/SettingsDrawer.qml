import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: settingsDrawerComponent
    property real smaPeriod: 15
    property real emaPeriod: 15

    signal closeDrawer()

    width: parent.width
    height: parent.height

    Drawer {
        id: drawer
        width: parent.width * 0.5
        height: parent.height
        edge: Qt.RightEdge

        Rectangle {
            id: drawerContent
            color: "#2E2F3A"
            width: parent.width
            height: parent.height

            // Header
            Item {
                id: header
                width: parent.width
                height: 70

                Rectangle {
                    width: parent.width * 0.8
                    height: 50
                    color: "#3A3F4B"
                    radius: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 10

                    Text {
                        text: "Settings"
                        font.pixelSize: 24
                        color: "#FFFFFF"
                        anchors.centerIn: parent
                    }
                }
            }

            // Sections Container
            Column {
                id: settingsColumn
                spacing: 20
                width: parent.width
                height: drawerContent.height - header.height - 20  // Deduct header height and spacing
                anchors.top: parent.top
                anchors.topMargin: 90
                anchors.horizontalCenter: parent.horizontalCenter

                // SMA & EMA Period Section
                SettingsSection {
                    id: periodSettings
                    icon: "images/speed.png" // Replace with your icon path
                    heading: "Period Settings"
                    width: parent.width * 0.9
                    height: settingsColumn.height * 0.2

                    content: Column {
                        spacing: 10

                        // SMA period slider
                        Label {
                            text: "SMA Period (seconds)"
                            color: "#FFFFFF"
                        }
                        Row {
                            spacing: 10
                            anchors.horizontalCenter: parent.horizontalCenter

                            Slider {
                                id: smaSlider
                                from: 10
                                to: 30
                                stepSize: 5
                                value: smaPeriod
                                onValueChanged: {
                                    console.log("smaSlider changing value = ", value)
                                    settingsDrawerComponent.smaPeriod = value
                                }
                                width: parent.width * 0.8  // Adjust width as necessary
                            }

                            Text {
                                text: String(smaSlider.value)  // Display the current slider value
                                color: "#FFFFFF"
                                anchors.verticalCenter: smaSlider.verticalCenter
                            }
                        }

                        // EMA period slider
                        Label {
                            text: "EMA Period (seconds)"
                            color: "#FFFFFF"
                        }
                        Row {
                            spacing: 10
                            anchors.horizontalCenter: parent.horizontalCenter

                            Slider {
                                id: emaSlider
                                from: 10
                                to: 30
                                stepSize: 5
                                value: emaPeriod
                                onValueChanged: settingsDrawerComponent.emaPeriod = value
                                width: parent.width * 0.8  // Adjust width as necessary
                            }

                            Text {
                                text: String(emaSlider.value)  // Display the current slider value
                                color: "#FFFFFF"
                                anchors.verticalCenter: emaSlider.verticalCenter
                            }
                        }
                    }
                }

                // Another Section Example
                SettingsSection {
                    id: otherSettings
                    icon: "images/calories.png"  // Replace with your icon path
                    heading: "Other Settings"
                    width: parent.width * 0.9
                    height: settingsColumn.height * 0.2

                    content: Column {
                        spacing: 10

                        // Other settings components go here
                        // For example, toggle buttons, input fields, etc.
                    }
                }

                // Add more sections as needed
            }
        }
    }

    // Overlay
    Rectangle {
        id: overlay
        anchors.fill: parent
        color: "black"
        opacity: 0.4
        visible: drawer.opened
        z: 10
        MouseArea {
            anchors.fill: parent
            onClicked: drawer.close()
        }
    }

    function open() {
        drawer.open();
    }

    function close() {
        drawer.close();
    }

    onCloseDrawer: close()
}
