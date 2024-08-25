/****************************************************************************
**
**
****************************************************************************/

import QtQuick 2.10
import BreathTracker.LiveData 1.0
import BreathTracker.FrontendTypes 1.0

//Changing values



    LiveDataBackground {
        id: background

        sensorData: BELiveData.sensorValue
        averagedData: BELiveData.averagedValue
        warningLevel: 1
        averageType : BELiveData.averageType



        ArcRight {
                id: rawSensorData
                x: 36
                y: 37
                antialiasing: true

                value: background.sensorData
            }


        ArcLeft {
            id: averagedSensorData
            x: 42
            y: 37
            strokeColor: averageType == FrontendTypes.SMA ? "#00FF00" : "#E69FFF"
            antialiasing: true
            value: background.averagedData
        }

        Connections {
            target: BELiveData
            onSensorValueChanged: {
                console.log("Sensor Value Updated: ", BELiveData.sensorValue)
            }
            onAveragedValueChanged: {
                console.log("Averaged Value Updated: ", BELiveData.averagedValue)
            }

            onAverageTypeChanged: {
                console.log("Average Type Updated: ", BELiveData.averageType)
            }
        }
    }



