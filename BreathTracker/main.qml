import QtQuick 2.15
import QtQuick.Controls 2.15



Window {
    width: 640
    height: 800
    visible: true
    title: qsTr("Hello World")

    // Import the custom components
       // RawSensorData {
       //     id: rawData
       //     anchors.top: parent.top
       //     anchors.left: parent.left
       //     anchors.right: parent.right
       //     height: parent.height * 0.3
       // }

        LiveData{
            id: liveData

    }
       DataTrends {
           id: trendDisplay

           height: 400
       }
}
