import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: trendDisplaySection
    width: parent.width
    height: 300
    color: "#333333"  // Dark background color similar to the image
    radius: 10
    border.color: "#555555"  // Lighter border color
    border.width: 2

    // Define min and max values for the graph
    property real minValue: 400  // Set according to your data's minimum expected value
    property real maxValue: 700  // Set according to your data's maximum expected value

    // Mocked data as properties
    property var sensorData: [
        { "time": 0, "value": 400 },
        { "time": 10, "value": 450 },
        { "time": 20, "value": 460 },
        { "time": 30, "value": 480 },
        { "time": 40, "value": 490 },
        { "time": 50, "value": 510 },
        { "time": 60, "value": 530 },
        { "time": 70, "value": 540 },
        { "time": 80, "value": 560 },
        { "time": 90, "value": 570 },
        { "time": 100, "value": 590 },
        { "time": 110, "value": 600 },
        { "time": 120, "value": 620 },
        { "time": 130, "value": 630 },
        { "time": 140, "value": 640 },
        { "time": 150, "value": 650 },
        { "time": 160, "value": 660 },
        { "time": 170, "value": 670 },
        { "time": 180, "value": 680 },
        { "time": 190, "value": 690 },
        { "time": 200, "value": 700 }
    ]

    property var averagedData: [
        { "time": 0, "value": 405 },
        { "time": 10, "value": 455 },
        { "time": 20, "value": 465 },
        { "time": 30, "value": 475 },
        { "time": 40, "value": 485 },
        { "time": 50, "value": 505 },
        { "time": 60, "value": 525 },
        { "time": 70, "value": 535 },
        { "time": 80, "value": 555 },
        { "time": 90, "value": 565 },
        { "time": 100, "value": 585 },
        { "time": 110, "value": 595 },
        { "time": 120, "value": 615 },
        { "time": 130, "value": 625 },
        { "time": 140, "value": 635 },
        { "time": 150, "value": 645 },
        { "time": 160, "value": 655 },
        { "time": 170, "value": 665 },
        { "time": 180, "value": 675 },
        { "time": 190, "value": 685 },
        { "time": 200, "value": 695 }
    ]

    Canvas {
        id: customGraph
        anchors.fill: parent
        anchors.margins: 20
        antialiasing: true

        onPaint: {
            var ctx = getContext("2d");

            // Clear the canvas
            ctx.clearRect(0, 0, width, height);

            // Draw the grid lines
            ctx.strokeStyle = "#666666";  // Darker grid line color
            ctx.lineWidth = 1;

            // Draw vertical and horizontal grid lines
            for (var i = 0; i <= 10; i++) {
                var x = width / 10 * i;
                var y = height / 10 * i;

                // Vertical grid lines
                ctx.beginPath();
                ctx.moveTo(x, 0);
                ctx.lineTo(x, height);
                ctx.stroke();

                // Horizontal grid lines
                ctx.beginPath();
                ctx.moveTo(0, y);
                ctx.lineTo(width, y);
                ctx.stroke();
            }

            // Helper function to normalize data points between minValue and maxValue
            function normalize(value) {
                return (value - minValue) / (maxValue - minValue);
            }

            // Draw the filled area for the sensor data
            ctx.fillStyle = "#E0E0E0";  // Light gray fill color
            ctx.beginPath();
            ctx.moveTo(0, height);  // Start at the bottom left
            ctx.lineTo(0, height * (1 - normalize(sensorData[0].value)));  // Move to the first data point

            for (var j = 1; j < sensorData.length; j++) {
                var x = width * (sensorData[j].time / 200);
                var y = height * (1 - normalize(sensorData[j].value));
                ctx.lineTo(x, y);
            }

            ctx.lineTo(width, height);  // Finish at the bottom right
            ctx.closePath();
            ctx.fill();

            // Draw the sensor data line
            ctx.strokeStyle = "#E0E0E0";  // Light gray line color
            ctx.lineWidth = 3;
            ctx.beginPath();

            ctx.moveTo(0, height * (1 - normalize(sensorData[0].value)));  // Start point

            for (var j = 1; j < sensorData.length; j++) {
                var x = width * (sensorData[j].time / 200);
                var y = height * (1 - normalize(sensorData[j].value));
                ctx.lineTo(x, y);
            }

            ctx.stroke();

            // Draw the filled area for the averaged data
            ctx.fillStyle = "#A0A0A0";  // Darker gray fill color
            ctx.beginPath();
            ctx.moveTo(0, height);  // Start at the bottom left
            ctx.lineTo(0, height * (1 - normalize(averagedData[0].value)));  // Move to the first data point

            for (var k = 1; k < averagedData.length; k++) {
                var x = width * (averagedData[k].time / 200);
                var y = height * (1 - normalize(averagedData[k].value));
                ctx.lineTo(x, y);
            }

            ctx.lineTo(width, height);  // Finish at the bottom right
            ctx.closePath();
            ctx.fill();

            // Draw the averaged data line
            ctx.strokeStyle = "#A0A0A0";  // Darker gray line color
            ctx.lineWidth = 3;
            ctx.beginPath();

            ctx.moveTo(0, height * (1 - normalize(averagedData[0].value)));  // Start point

            for (var k = 1; k < averagedData.length; k++) {
                var x = width * (averagedData[k].time / 200);
                var y = height * (1 - normalize(averagedData[k].value));
                ctx.lineTo(x, y);
            }

            ctx.stroke();

            // Draw the circular markers for the averaged data
            ctx.fillStyle = "#A0A0A0";

            for (var m = 0; m < averagedData.length; m += 5) {
                var x = width * (averagedData[m].time / 200);
                var y = height * (1 - normalize(averagedData[m].value));
                ctx.beginPath();
                ctx.arc(x, y, 8, 0, 2 * Math.PI);
                ctx.fill();
            }

            // Draw the legend
            ctx.fillStyle = "#CCCCCC";
            ctx.font = "bold 14px sans-serif";
            ctx.fillText("Sensor", 10, 20);
            ctx.fillText("Averaged", 10, 40);

            // Draw the legend indicators
            ctx.fillStyle = "#E0E0E0";  // Color for the sensor data
            ctx.beginPath();
            ctx.arc(60, 15, 5, 0, 2 * Math.PI);
            ctx.fill();

            ctx.fillStyle = "#A0A0A0";  // Color for the averaged data
            ctx.beginPath();
            ctx.arc(60, 35, 5, 0, 2 * Math.PI);
            ctx.fill();

            // Draw the x-axis labels (time)
            for (var i = 0; i <= 10; i++) {
                var x = width / 10 * i;
                var timeLabel = (i * 20).toString();  // Adjust according to your time scale
                ctx.fillStyle = "#CCCCCC";
                ctx.font = "bold 12px sans-serif";
                ctx.fillText(timeLabel, x - 10, height + 15);
            }

            // Draw the y-axis labels (values)
            for (var i = 0; i <= 10; i++) {
                var y = height - (height / 10 * i);
                var valueLabel = (minValue + i * (maxValue - minValue) / 10).toFixed(0);
                ctx.fillStyle = "#CCCCCC";
                ctx.font = "bold 12px sans-serif";
                ctx.fillText(valueLabel, -30, y + 5);
            }
        }
    }
}
