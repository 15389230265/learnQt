import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: rec1;
        anchors.fill: parent;
        anchors.leftMargin: 10;
        anchors.rightMargin: 10;
        anchors.topMargin: 10;
        anchors.bottomMargin: 10;
        color: "gray";
        //一个不可视元素的集合 用于轻量数据中 string int variant
        QtObject{
            id: attrs;
            property int couter;
            Component.onCompleted: {
                attrs.couter = 10;
            }
        }

        Text {
            id: countShow;
            anchors.centerIn: parent;
            color: "blue";
            font.pixelSize: 40;
        }
        //Timer 代表定时器，使用起来也很简单，响应其 onTriggered() 信号即可，
        //interval 指定定时周期，单位是毫秒，默认值是 1000 毫秒
        //repeat 设定定时器是周期性触发还是一次性触发，默认是一次性的（好像和 QTimer 不一样嗳）
        //running 属性，设置为 true 定时器就开始工作，设置为 false 就歇菜，默认是 false
        // triggeredOnStart 属性，如果你设置这个属性为 true ，那定时器开始执行时立马先触发一次，默认值是 false 。
        Timer {
            id: countDown;
            interval: 1000;
            repeat: true;
            triggeredOnStart: true;
            onTriggered: {
                countShow.text = attrs.couter;
                attrs.couter -= 1;
                if(attrs.couter < 0){
                    countDown.stop();
                    countShow.text = "Clap Now!";
                }
            }
        }

        Button{
            id: strartButton;
            anchors.top: countShow.bottom;
            anchors.topMargin: 20;
            anchors.horizontalCenter: countShow.horizontalCenter;
            text: "Start";
            onClicked: {
                attrs.couter = 10;
                countDown.start();
            }
        }
    }
}
