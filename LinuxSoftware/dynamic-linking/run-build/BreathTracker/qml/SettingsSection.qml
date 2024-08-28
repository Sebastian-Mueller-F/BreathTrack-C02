import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    property alias icon: iconSource.source
    property alias heading: headingText.text
    property alias content: contentArea.children

    width: parent.width * 0.9  // Adjust width as necessary
    anchors.horizontalCenter: parent.horizontalCenter

    // Explicitly set the height based on header and content
    height: headerRow.height + contentArea.height + 10  // 10 is the spacing

    Column {
        spacing: 10
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter

        // Header row containing the icon and heading text
        Row {
            id: headerRow
            spacing: 10
            width: parent.width * 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            height: 40  // Explicit height for the header

            Image {
                id: iconSource
                width: 24
                height: 24
                source: ""
            }

            Text {
                id: headingText
                font.pixelSize: 18
                color: "#FFFFFF"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        // Content area where settings or other elements are placed
        Rectangle {
            id: contentArea
            width: parent.width * 0.8
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter

            // Explicitly set the height
            height: 200 /*contentColumn.height*/

            Column {
                id: contentColumn
                anchors.fill: parent
                spacing: 10

                // Your dynamic content goes here
                // For example:
                // Text { text: "This is a sample content" }
            }
        }
    }
}
