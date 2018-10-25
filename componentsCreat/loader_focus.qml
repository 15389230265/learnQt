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

    Component {
        id: colorComponent;
        Rectangle {
            id: colorPicker;
            width: 50;
            height: 30;
            signal colorPicked(color clr);
            //颜色选择组件定义了一个名为 loader 的属性，以便鼠标点击颜色选择组件时可以改变 Loader 对象的焦点属性
            property Item loader;
            border.width: focus ? 2 : 0;
            border.color: focus ? "#90d750" : "#808080";
            MouseArea{
                anchors.fill: parent;
                onClicked: {
                    colorPicker.colorPicked(colorPicker.color);
                    loader.focus = true;
                }
            }
            Keys.onReturnPressed: {
                colorPicker.colorPicked(colorPicker.color);
                event.accepted = true;
            }
            //空格
            Keys.onSpacePressed: {
                colorPicked(colorPicker.color);
                event.accepted = true;
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
        focus: true;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: colorComponent;
        //设置了 KeyNavigation 附加属性，指定左右键和 tab 键如何切换焦点，而当焦点变化时，同步改变颜色选择组件的焦点
        KeyNavigation.right: blueLoader;
        KeyNavigation.tab: blueLoader;
        onLoaded: {
            item.color = "red";
            item.focus = true;
            //在 Loader 的 onLoaded 信号处理器中给颜色选择组件的 loader 属性赋值
            item.loader = redLoader;
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
        sourceComponent: colorComponent;
        KeyNavigation.right: redLoader;
        KeyNavigation.tab: redLoader;
        onLoaded: {
            item.color = "blue";
            item.loader = blueLoader;
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
        }
    }
    Connections {
        target: blueLoader.item;
        onColorPicked:{
            coloredText.color = clr;
        }
    }
}
