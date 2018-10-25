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

    function setTextColor(clr){
        coloredText.color = clr;
    }
    //使用 ColorPicker 组件的方式与使用 Rectangle 、 Button 、 Text 等标准 Qt Quick 组件完全一致
    //自定义的组件和 Qt Quick 组件并无本质不同,组件实例的 id 和组成组件的顶层 item 的 id 是各自独立的
    ColorPicker {
        id: redColor;
        color: "red";
        focus: true;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.right: blueColor;
        KeyNavigation.tab: buleColor;
        onColorPicked: {
            coloredText.color = clr;
        }
    }
    ColorPicker {
        id: blueColor;
        color: "blue";
        focus: true;
        anchors.left: redColor.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: redColor;
        KeyNavigation.right: pinkColor;
        KeyNavigation.tab: pinkColor;
    }
    ColorPicker {
        id: pinkColor;
        color: "pink";
        focus: true;
        anchors.left: blueColor.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: blueColor;
        KeyNavigation.tab: redColor;
    }
    //组件初始化后触发
    Component.onCompleted: {
        blueColor.colorPicked.connect(setTextColor);
        pinkColor.colorPicked.connect(setTextColor);
    }
}
