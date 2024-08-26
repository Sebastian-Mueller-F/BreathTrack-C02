import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    visible: true
    width: 800
    height: 300

    // New properties for adjustable aspects
    property color lineStartColor: "#53BFF5"  // Start color of the line gradient (Orange)
    property color lineEndColor: "#1E90FF"    // End color of the line gradient (Blue)
    property string fillStartColor: "rgba(83, 91, 245, 0.3)"  // Start color of the fill gradient (Transparent Orange)
    property string fillEndColor: "rgba(30, 144, 255, 0.1)"   // End color of the fill gradient (Transparent Blue)
    property int lineThickness: 2
    // Line thickness
    property int gridThickness: 1  // Grid line thickness
    property color gridColor: "#AAAAAA"  // Color of the grid lines

    property var sensorData: []
    property var maxDataPoints: 50
    property var canvasHeight: 300
    property int gridSpacing: 50  // Adjust as needed

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            let newValue = Math.random() * 100;
            sensorData.push(newValue);
            if (sensorData.length > maxDataPoints) {
                sensorData.shift();
            }
            sensorCanvas.requestPaint();
        }
    }

    // Simulate Drop Shadow using a Semi-Transparent Rectangle
    Rectangle {
        width: parent.width + 10
        height: parent.height + 10
        color: "black"
        opacity: 0.2  // Semi-transparent shadow
        radius: 20 // Rounded corners for shadow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 5
        anchors.topMargin: 5
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"  // Dark background color
        radius: 15  // Adjusted corner radius for a slightly sharper look
        border.color: "#555555"  // Adding a subtle border around the graph area
        border.width: 0

        Item {
            id: sensorGraph
            x: 100
            y: 50
            width: parent.width - 150
            height: parent.height - 100
            clip: true

            Canvas {
                id: sensorCanvas
                width: parent.width
                height: canvasHeight

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect(0, 0, width, height);

                    // Grid lines
                    ctx.strokeStyle = gridColor;  // Use adjustable grid color
                    ctx.lineWidth = gridThickness;  // Use adjustable grid thickness

                    // Vertical grid lines and X-axis tick marks
                    for (var x = gridSpacing; x < width; x += gridSpacing) {
                        ctx.beginPath();
                        ctx.moveTo(x, 0);
                        ctx.lineTo(x, height);
                        ctx.stroke();

                        // Draw tick marks on X-axis
                        ctx.beginPath();
                        ctx.moveTo(x, height);
                        ctx.lineTo(x, height + 5);  // Small vertical line for tick mark
                        ctx.stroke();
                    }

                    // Horizontal grid lines and Y-axis tick marks
                    for (var y = gridSpacing; y < height; y += gridSpacing) {
                        ctx.beginPath();
                        ctx.moveTo(0, y);
                        ctx.lineTo(width, y);
                        ctx.stroke();
                    }

                    // Draw the graph line and fill area
                    if (sensorData.length > 0) {
                        var scaleX = width / Math.min(sensorData.length, maxDataPoints);
                        var scaleY = height / 100;

                        // Create gradient for the line using properties
                        var lineGradient = ctx.createLinearGradient(0, 0, width, 0);
                        lineGradient.addColorStop(0, lineStartColor);  // Start color
                        lineGradient.addColorStop(1, lineEndColor);  // End color

                        ctx.beginPath();
                        ctx.moveTo(0, height - (sensorData[0] * scaleY));

                        for (var i = 1; i < sensorData.length - 1; i++) {
                            var xc = (i * scaleX + (i + 1) * scaleX) / 2;
                            var yc = (height - (sensorData[i] * scaleY) + height - (sensorData[i + 1] * scaleY)) / 2;
                            ctx.quadraticCurveTo(i * scaleX, height - (sensorData[i] * scaleY), xc, yc);
                        }

                        ctx.lineTo((sensorData.length - 1) * scaleX, height - (sensorData[sensorData.length - 1] * scaleY));

                        // Fill the area under the curve using properties
                        ctx.lineTo(width, height);
                        ctx.lineTo(0, height);
                        ctx.closePath();

                        var fillGradient = ctx.createLinearGradient(0, 0, 0, height);
                        fillGradient.addColorStop(0, fillStartColor);  // Start color for fill
                        fillGradient.addColorStop(1, fillEndColor);  // End color for fill
                        ctx.fillStyle = fillGradient;
                        ctx.fill();

                        // Set line color and thickness using properties
                        ctx.strokeStyle = lineGradient;  // Gradient line
                        ctx.lineWidth = lineThickness;  // Adjustable line thickness

                        ctx.stroke();  // Draw the line with the new style
                    }
                }
            }
        }

        // X-Axis Labels with RowLayout and Rectangles
        RowLayout {
            id: xAxisLabels
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: sensorGraph.bottom
            anchors.topMargin: 0
            width: sensorGraph.width

            Repeater {
                model: Math.floor((sensorGraph.width) / gridSpacing)
                delegate: Rectangle {
                    color: "transparent"
                    radius: 5
                    width: 40  // Fixed width for the label container
                    height: 25
                    Layout.alignment: Qt.AlignHCenter
                    Layout.margins: 0

                    Text {
                        text: model.index * gridSpacing
                        font.pixelSize: 14  // Increased font size for better readability
                        font.family: "Arial"  // Consistent font style
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
        }

        // Y-Axis Labels with ColumnLayout and Rectangles
        ColumnLayout {
            id: yAxisLabels
            anchors.verticalCenter: sensorGraph.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10  // Increased margin for better spacing
            height: sensorGraph.height

            Repeater {
                model: Math.floor((sensorGraph.height) / gridSpacing)
                delegate: Rectangle {
                    color: "transparent"
                    radius: 5
                    width: 40  // Fixed width for the label container
                    height: 25
                    Layout.alignment: Qt.AlignVCenter
                    Layout.margins: 0

                    Text {
                        text: 100 - model.index * (100 / Math.floor((sensorGraph.height) / gridSpacing))
                        font.pixelSize: 14  // Increased font size for consistency with X-axis labels
                        font.family: "Arial"  // Consistent font style
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}
