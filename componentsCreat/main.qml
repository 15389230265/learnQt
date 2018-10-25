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
        color: "#c0c0c0";

        Text {
            id: coloredText;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 4;
            text: qsTr("Hello World!");
            font.pixelSize: 32;
        }

        Component {
            id: colorComponent;
            Rectangle {
                id: colorPicker;
                width: 50;
                height: 30;
                signal colorPicked(color clr);
                MouseArea{
                    anchors.fill: parent;
                    onPressed: colorPicker.colorPicked(colorPicker.color);
                }
            }
        }
        //Loader 用来动态加载 QML 组件
        //Loader 可以使用其 source 属性加载一个 qml 文档，也可以通过其 sourceComponent 属性加载一个 Component 对象
        // Loader 的 item 属性指向它加载的组件的顶层 item
        Loader{
            id: redLoader;
            //没有加载 Component 的 Loader 对象是不可见的
            //一旦你加载了一个 Component ， Loader 的大小、位置等属性却可以影响它所加载的 Component
            width: 80;
            height: 60;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 4;
            sourceComponent: colorComponent;
            onLoaded: {
                item.color = "red";
            }
        }

        Loader{
            id: blueLoader;
            anchors.left: redLoader.right;
            anchors.leftMargin: 4;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 4;
            sourceComponent: colorComponent;
            onLoaded: {
                item.color = "blue";
            }
        }
        //对于信号的访问，我们则可以使用 Connections 对象
        Connections {
            target: redLoader.item;
            onColorPicked:{
                coloredText.color = clr;
            }
        }
        Connections {
            target: blueLoader.item;
            onColorPicked:{
                coloredText.color = clr;
            }
        }
    }


}
