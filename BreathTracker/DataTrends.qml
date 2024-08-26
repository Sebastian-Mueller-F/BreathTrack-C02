import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    visible: true
    width: 800
    height: 300

    // Graph Dataset 1
     property var sensorData1: []
    property color lineStartColor: "#53BFF5"
    property color lineEndColor: "#1E90FF"
    property string fillStartColor: "rgba(83, 91, 245, 0.3)"
    property string fillEndColor: "rgba(30, 144, 255, 0.1)"
    property int lineThickness: 2

    //Graph Dataset 2
    property var sensorData2: []
    property color line2StartColor: "#FFA500"
    property color line2EndColor: "#FF4500"
    property string fill2StartColor: "rgba(255, 165, 0, 0.3)"
    property string fill2EndColor: "rgba(255, 69, 0, 0.1)"
    property int line2Thickness: 2

    property bool hasTwoDataSets: false
    property int gridThickness: 1
    property color gridColor: "#AAAAAA"

    property int maxDataPoints: 50
    property int canvasHeight: 300
    property int gridSpacing: 50

    onSensorData1Changed: {
        sensorCanvas.requestPaint();
    }
    onSensorData2Changed: {
        sensorCanvas.requestPaint();
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
        color: "transparent"
        radius: 15
        border.color: "#555555"
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

                    // Draw the first dataset's graph line and fill area
                    if (sensorData1.length > 0) {
                        var scaleX = width / Math.min(sensorData1.length, maxDataPoints);
                        var scaleY = height / 100;

                        // Create gradient for the line using properties
                        var lineGradient1 = ctx.createLinearGradient(0, 0, width, 0);
                        lineGradient1.addColorStop(0, lineStartColor);  // Start color
                        lineGradient1.addColorStop(1, lineEndColor);  // End color

                        ctx.beginPath();
                        ctx.moveTo(0, height - (sensorData1[0] * scaleY));

                        for (var i = 1; i < sensorData1.length - 1; i++) {
                            var xc = (i * scaleX + (i + 1) * scaleX) / 2;
                            var yc = (height - (sensorData1[i] * scaleY) + height - (sensorData1[i + 1] * scaleY)) / 2;
                            ctx.quadraticCurveTo(i * scaleX, height - (sensorData1[i] * scaleY), xc, yc);
                        }

                        ctx.lineTo((sensorData1.length - 1) * scaleX, height - (sensorData1[sensorData1.length - 1] * scaleY));

                        // Fill the area under the curve using properties
                        ctx.lineTo(width, height);
                        ctx.lineTo(0, height);
                        ctx.closePath();

                        var fillGradient1 = ctx.createLinearGradient(0, 0, 0, height);
                        fillGradient1.addColorStop(0, fillStartColor);  // Start color for fill
                        fillGradient1.addColorStop(1, fillEndColor);  // End color for fill
                        ctx.fillStyle = fillGradient1;
                        ctx.fill();

                        // Set line color and thickness using properties
                        ctx.strokeStyle = lineGradient1;  // Gradient line
                        ctx.lineWidth = lineThickness;  // Adjustable line thickness

                        ctx.stroke();  // Draw the line with the new style
                    }

                    // Draw the second dataset's graph line and fill area if enabled
                    if (hasTwoDataSets && sensorData2.length > 0) {
                        var scaleX2 = width / Math.min(sensorData2.length, maxDataPoints);
                        var scaleY2 = height / 100;

                        // Create gradient for the line using properties
                        var lineGradient2 = ctx.createLinearGradient(0, 0, width, 0);
                        lineGradient2.addColorStop(0, line2StartColor);  // Start color
                        lineGradient2.addColorStop(1, line2EndColor);  // End color

                        ctx.beginPath();
                        ctx.moveTo(0, height - (sensorData2[0] * scaleY2));

                        for (var j = 1; j < sensorData2.length - 1; j++) {
                            var xc2 = (j * scaleX2 + (j + 1) * scaleX2) / 2;
                            var yc2 = (height - (sensorData2[j] * scaleY2) + height - (sensorData2[j + 1] * scaleY2)) / 2;
                            ctx.quadraticCurveTo(j * scaleX2, height - (sensorData2[j] * scaleY2), xc2, yc2);
                        }

                        ctx.lineTo((sensorData2.length - 1) * scaleX2, height - (sensorData2[sensorData2.length - 1] * scaleY2));

                        // Fill the area under the curve using properties
                        ctx.lineTo(width, height);
                        ctx.lineTo(0, height);
                        ctx.closePath();

                        var fillGradient2 = ctx.createLinearGradient(0, 0, 0, height);
                        fillGradient2.addColorStop(0, fill2StartColor);  // Start color for fill
                        fillGradient2.addColorStop(1, fill2EndColor);  // End color for fill
                        ctx.fillStyle = fillGradient2;
                        ctx.fill();

                        // Set line color and thickness using properties
                        ctx.strokeStyle = lineGradient2;  // Gradient line
                        ctx.lineWidth = line2Thickness;  // Adjustable line thickness

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
