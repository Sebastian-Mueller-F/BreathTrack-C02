import QtQuick 2.15
import QtQuick.Controls 2.15
import BreathTracker.TrendData 1.0


Window {
    width: 768
    height: 1024
    visible: true
    title: qsTr("Hello World")
    Rectangle {
        anchors.fill: parent
        color: "#191E26"
    }

    // Import the custom components
       // RawSensorData {
       //     id: rawData
       //     anchors.top: parent.top
       //     anchors.left: parent.left
       //     anchors.right: parent.right
       //     height: parent.height * 0.3
       // }

    Column {
        spacing : 10

        LiveData{
            id: liveData
            color: "#191E26"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        DataTrends {
            id: rawTrend

            height: 250
            width: 750

            sensorData1: BETrendData.raw
        }

        DataTrends {
            id: averagedTrend

            height: 250
            width: 750
            hasTwoDataSets: true

            sensorData1: BETrendData.sma
            lineStartColor: "#00FF57"
            lineEndColor: "#00FFAD"
            fillStartColor: "rgba(0, 255, 87, 0.4)"
            fillEndColor: "rgba(0, 255, 173, 0.2)"

            sensorData2: BETrendData.ema
            line2StartColor: "#E79EFF"
            line2EndColor: "#C79EFF"
            fill2StartColor: "rgba(231, 158, 255, 0.4)"
            fill2EndColor: "rgba(199, 158, 255, 0.2)"

        }
    }


}
