import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    visible: true
    width: 400
    height: 500

    property int co2Value: 50
    property int timeInterval: 30
    property string averageType: "SMA"

    // Main Container
    Rectangle {
        anchors.centerIn: parent
        width: 300
        height: 500
        radius: 20
        border.color: "gray"
        color: "transparent"

        // Background gradient
        Gradient {
            GradientStop { position: 0.0; color: "#f0f0f0" }  // Light gray at the top
            GradientStop { position: 1.0; color: "#d9d9d9" }  // Slightly darker gray at the bottom
        }

        // Title Label
        Text {
            text: "Averaged Data"
            font.pixelSize: 24
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
        }

        // Time Interval Selector
        Row {
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter

            ComboBox {
                id: timeIntervalSelector
                model: [10, 20, 30]
                onCurrentIndexChanged: timeInterval = modelData
            }

            Text {
                text: "minutes"
                font.pixelSize: 16
                anchors.verticalCenter: timeIntervalSelector.verticalCenter
            }
        }

        // Circular Gauge with Refined Border Style
        Item {
            width: 200
            height: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: timeIntervalSelector.bottom
            anchors.topMargin: 40

            // Outer Rim with Metallic Look
            Rectangle {
                width: 200
                height: 200
                radius: 100
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#b8b8b8" }  // Light metallic gray
                    GradientStop { position: 0.5; color: "#808080" }  // Mid-tone gray
                    GradientStop { position: 1.0; color: "#505050" }  // Darker gray for shadow
                }
                border.width: 2
                border.color: "transparent"
                anchors.centerIn: parent
            }

            // Inner Shadow to Enhance 3D Effect
            Rectangle {
                width: 180
                height: 180
                radius: 90
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#303030" }  // Slightly lighter inner area
                    GradientStop { position: 1.0; color: "#000000" }  // Darker towards edges
                }
                border.width: 4
                border.color: "#404040"  // Dark border to enhance depth
                anchors.centerIn: parent
            }

            // CO2 Value Text
            Text {
                text: co2Value + " CO\u2082"
                font.pixelSize: 48
                color: "white"
                anchors.centerIn: parent
            }
        }

        // Footer: Average and Raw Data
        Column {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter

            Row {
                Text {
                    text: "Averaged Value:"
                    font.pixelSize: 18
                }

                Text {
                    id: averagedValue
                    text: String(co2Value)
                    font.pixelSize: 18
                    color: "green"
                }
            }

            Row {
                Text {
                    text: "Raw Value:"
                    font.pixelSize: 18
                }

                Text {
                    id: rawValue
                    text: String(co2Value)
                    font.pixelSize: 18
                    color: "blue"
                }
            }
        }
    }
}
