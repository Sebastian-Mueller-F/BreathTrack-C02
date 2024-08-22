import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: averageDataSection
    width: parent.width
    height: 200
    color: "#e0e0e0"
    border.color: "black"

    Column {
        anchors.centerIn: parent
        spacing: 10

        Row {
            spacing: 10

            Text {
                text: "Average CO2 Value"
                font.pointSize: 20
                color: "black"
            }

            ComboBox {
                id: averageType
                model: ["SMA", "EMA"]
                currentIndex: 0
            }
        }

        Text {
            id: averageValue
            text: "480 ppm"
            font.pointSize: 40
            color: "green"
        }

        Rectangle {
            id: averageIndicator
            width: 100
            height: 100
            radius: 50
            color: averageValue.color
            border.color: "black"
        }

        Slider {
            id: averageDuration
            from: 10
            to: 30
            stepSize: 5
            value: 15
            width: 200
        }

        Text {
            text: "Duration: " + averageDuration.value + " sec"
            font.pointSize: 16
            color: "black"
        }

        Text {
            id: averageWarning
            text: averageValue.text > "1000" ? "Critical Level!" : ""
            color: "red"
            font.pointSize: 16
        }
    }
}
