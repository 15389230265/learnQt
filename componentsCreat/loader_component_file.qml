import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle {
    width: 320;
    height: 240;
    color: "#EEEEEE";

    Text {
        id: coloredText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        text: qsTr("Hello World!");
        font.pixelSize: 32;
    }

    //对于定义在一个独立文件中的 Component ，同样可以使用 Loader 来加载，只要指定 Loader 的 source 属性即可
    Loader{
        id: redLoader;
        //没有加载 Component 的 Loader 对象是不可见的
        //一旦你加载了一个 Component ， Loader 的大小、位置等属性却可以影响它所加载的 Component
        width: 80;
        height: 60;
        focus: true;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        source: "ColorPicker.qml";
        //设置了 KeyNavigation 附加属性，指定左右键和 tab 键如何切换焦点，而当焦点变化时，同步改变颜色选择组件的焦点
        KeyNavigation.right: blueLoader;
        KeyNavigation.tab: blueLoader;
        onLoaded: {
            item.color = "red";
            item.focus = true;
        }
        onFocusChanged: {
            item.focus = focus;
        }
    }

    Loader{
        id: blueLoader;
        anchors.left: redLoader.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        source: "ColorPicker.qml";
        KeyNavigation.right: redLoader;
        KeyNavigation.tab: redLoader;
        onLoaded: {
            item.color = "blue";
        }
        onFocusChanged: {
            item.focus = focus;
        }
    }
    //对于信号的访问，我们则可以使用 Connections 对象
    Connections {
        target: redLoader.item;
        onColorPicked:{
            coloredText.color = clr;
            if(!redLoader.focus){
                redLoader.focus = true;
                blueLoader.focus = false;
            }
        }
    }
    Connections {
        target: blueLoader.item;
        onColorPicked:{
            coloredText.color = clr;
            if(!blueLoader.focus){
                blueLoader.focus = true;
                redLoader.focus = false;
            }
        }
    }
}
