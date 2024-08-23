import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 400
    title: "CO2 Sensor Visualization"

    property var sensorData: []
    property var maxDataPoints: 100
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

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#333333"  // Dark background color
        radius: 20 // Rounded corners

        Item {
            id: sensorGraph
            x: 100
            y: 50
            width: parent.width - 150
            height: parent.height - 150
            clip: true

            Canvas {
                id: sensorCanvas
                width: parent.width
                height: canvasHeight

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect(0, 0, width, height);

                    // Grid lines
                    ctx.strokeStyle = "#AAAAAA";  // Light gray grid lines
                    ctx.lineWidth = 2;  // Thicker grid lines

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

                        // Step 1: Adjust the line style
                        ctx.beginPath();
                        ctx.moveTo(0, height - (sensorData[0] * scaleY));

                        for (var i = 1; i < sensorData.length - 1; i++) {
                            var xc = (i * scaleX + (i + 1) * scaleX) / 2;
                            var yc = (height - (sensorData[i] * scaleY) + height - (sensorData[i + 1] * scaleY)) / 2;
                            ctx.quadraticCurveTo(i * scaleX, height - (sensorData[i] * scaleY), xc, yc);
                        }

                        ctx.lineTo((sensorData.length - 1) * scaleX, height - (sensorData[sensorData.length - 1] * scaleY));

                        // Fill the area under the curve
                        ctx.lineTo(width, height);
                        ctx.lineTo(0, height);
                        ctx.closePath();

                        var gradient = ctx.createLinearGradient(0, 0, 0, height);
                        gradient.addColorStop(0, "rgba(255, 255, 255, 0.3)");  // Lighter fill gradient
                        gradient.addColorStop(1, "rgba(255, 255, 255, 0.1)");  // Fade to transparent
                        ctx.fillStyle = gradient;
                        ctx.fill();

                        // Step 2: Set line color and thickness
                        ctx.strokeStyle = "#FFFFFF";  // Solid white line
                        ctx.lineWidth = 3;  // Thicker line for better visibility

                        // Optional: Add shadow for a 3D effect
                        ctx.shadowColor = "rgba(0, 0, 0, 0.7)";
                        ctx.shadowBlur = 10;

                        ctx.stroke();  // Draw the line with the new style
                    }
                }
            }

            // Sensor title
            Text {
                text: "SENSOR"
                font.pixelSize: 24
                color: "white"
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 10
            }
        }

        // X-Axis Labels with RowLayout and Rectangles
        RowLayout {
            id: xAxisLabels
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: sensorGraph.bottom
            anchors.topMargin: 5
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
                        font.pixelSize: 12
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
            anchors.leftMargin: 5
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
                        font.pixelSize: 12
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}
