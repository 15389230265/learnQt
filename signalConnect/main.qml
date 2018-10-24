import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Rectangle {
        anchors.fill: parent;
        anchors.leftMargin: 10;
        anchors.rightMargin: 10;
        anchors.topMargin: 10;
        anchors.bottomMargin: 10;
        color: "gray";

        Text {
            id: text1;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 20;
            text: qsTr("Text One");
            color: "blue";
            font.pixelSize: 28;
        }

        Text {
            id: text2;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: text1.bottom;
            anchors.topMargin: 20;
            text: qsTr("Text Two");
            color: "blue";
            font.pixelSize: 28;
        }

        Button {
            id: changeButton;
            anchors.top: text2.bottom;
            anchors.topMargin: 8;
            anchors.horizontalCenter: parent.horizontalCenter;
            text: "Change";
        }
        //Connections 有一个属性名为 target ，它呢，指向发出信号的对象。
        Connections {
            target: changeButton;
            onClicked: {
                //Math 是 JavaScript 语言内置的对象，有 random() / sin() / max() / min() / abs() 等等方法
                text1.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
                text2.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
            }
        }
    }
}
