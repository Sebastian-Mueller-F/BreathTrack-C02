import QtQuick 2.15
import QtQuick.Controls 2.15



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

            height: 300
            width: 750

        }

        DataTrends {
            id: averagedTrend

            height: 300
            width: 750
        }
    }


}
