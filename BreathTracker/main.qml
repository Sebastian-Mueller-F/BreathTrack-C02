import QtQuick 2.15
import QtQuick.Controls 2.15
import BreathTracker.TrendData 1.0
import BreathTracker.LiveData 1.0

Window {
    width: 768
    height: 1024
    visible: true
    title: qsTr("CO2 Breath Tracker")

    Rectangle {
        anchors.fill: parent
        color: "#191E26"
    }

    // Import and instantiate the settings drawer
    SettingsDrawer {
        id: settingsDrawer
        smaPeriod: BELiveData.smaPeriod
        emaPeriod: BELiveData.emaPeriod

        onSmaPeriodChanged: {
               BELiveData.setSmaPeriod(smaPeriod) // Update backend whenever smaPeriod changes
           }

           onEmaPeriodChanged: {
               BELiveData.setEmaPeriod(emaPeriod)  // Update backend whenever emaPeriod changes
        }

        onCloseDrawer: {
            BELiveData.smaPeriod = settingsDrawer.smaPeriod
            BELiveData.emaPeriod = settingsDrawer.emaPeriod
        }
        z: 10  // Ensure it's on top of other components
    }

    // Settings button
    Button {
        id: settingsButton
        text: "Settings"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        onClicked: settingsDrawer.open()
        z: 1  // Ensure button is still above the background
    }

    Column {
        spacing: 10
        z: 0  // Set a lower z value for the Column and its children

        LiveData {
            id: liveData
            color: "#191E26"
            anchors.horizontalCenter: parent.horizontalCenter
            z: 0  // Ensure it's below the overlay
        }

        DataTrends {
            id: rawTrend
            height: 250
            width: 750
            sensorData1: BETrendData.raw
            z: 0  // Ensure it's below the overlay
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
            z: 0  // Ensure it's below the overlay
        }
    }
}
