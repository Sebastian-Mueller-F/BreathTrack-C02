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

                Behavior on value {
                           NumberAnimation {
                               duration: 800  // Duration of 800ms for a smooth transition
                               easing.type: Easing.InOutQuad  // Easing function for smoothness
                           }
                       }
            }


        ArcLeft {
            id: averagedSensorData
            x: 42
            y: 37
            strokeColor: averageType == FrontendTypes.SMA ? "#00FF00" : "#E69FFF"
            antialiasing: true
            value: background.averagedData

            Behavior on value {
                       NumberAnimation {
                           duration: 800  // Duration of 800ms for a smooth transition
                           easing.type: Easing.InOutQuad  // Easing function for smoothness
                       }
                   }
        }


    }



