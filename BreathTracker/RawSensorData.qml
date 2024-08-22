
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rawDataSection
    width: parent.width
    height: 200
    color: "#f0f0f0"
    border.color: "black"

    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            text: "Current CO2 Value"
            font.pointSize: 20
            color: "black"
        }

        Text {
            id: co2Value
            text: "500 ppm"
            font.pointSize: 40
            color: "green"
        }

        Rectangle {
            id: co2Indicator
            width: 100
            height: 100
            radius: 50
            color: co2Value.color
            border.color: "black"
        }

        Text {
            id: warningMessage
            text: co2Value.text > "1000" ? "Critical Level!" : ""
            color: "red"
            font.pointSize: 16
        }
    }
}
