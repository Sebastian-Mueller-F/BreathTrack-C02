/****************************************************************************
**
**
****************************************************************************/

import QtQuick 2.10
import BreathTracker.LiveData 1.0

//Changing values



LiveDataBackground {
    id: root

    sensorData: BELiveData.sensorValue
    averagedData: BELiveData.averagedValue
    warningLevel: 1
    averageType : 0


    ArcRight {
        id: rawSensorData
        x: 36
        y: 37
        antialiasing: true

        value: root.sensorData
    }

    ArcLeft {
        id: averagedSensorData
        x: 42
        y: 37
        strokeColor: "#11d388"
        antialiasing: true
        value: root.averagedData
    }

    Connections {
        target: BELiveData
        onSensorValueChanged: {
            console.log("Sensor Value Updated: ", BELiveData.sensorValue)
        }
        onAveragedValueChanged: {
            console.log("Averaged Value Updated: ", BELiveData.averagedValue)
        }
    }
}
