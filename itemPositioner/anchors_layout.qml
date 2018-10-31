import QtQuick 2.0
import QtQuick.Controls 2.4

//anchors(锚)布局
//锚布局是最灵活的一种 Qt Quick 布局方式，使用它你可以随意摆布界面上那些可见元素，
//不过，如果你的界面元素很多，它也将是代码量最大的一种布局方式。
Rectangle {
    width: 320;
    height: 240;
    color: "#EEEEEE";
    id: rootItem;

    Text {
        id: centerText
        text: qsTr("A Single Text.");
        anchors.centerIn: parent;
        font.pixelSize: 24;
        font.bold: true;
    }

    function setTextColor(clr){
        centerText.color = clr;
    }

    ColorPicker{
        id: topColor1;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: topColor2;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.left: topColor1.right;
        anchors.leftMargin: 4;
        anchors.top: topColor1.top;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: topColor3;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.right: parent.right;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: topColor4;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.right: topColor3.left;
        anchors.leftMargin: 4;
        anchors.top: topColor3.top;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: bottomColor1;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.topMargin: 4;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: bottomColor2;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.left: bottomColor1.right;
        anchors.leftMargin: 4;
        anchors.bottom: bottomColor1.bottom;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: bottomColor3;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.right: parent.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.topMargin: 4;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: bottomColor4;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.right: bottomColor3.left;
        anchors.leftMargin: 4;
        anchors.bottom: bottomColor3.bottom;
        anchors.topMargin: 4;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: leftVCenterColor;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: rightVCenterColor;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.right: parent.right;
        anchors.leftMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: topHCenterColor;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.top: parent.top;
        anchors.leftMargin: 4;
        anchors.horizontalCenter: parent.horizontalCenter;
        onColorPicked: setTextColor(clr);
    }

    ColorPicker{
        id: bottomHCenterColor;
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0);
        anchors.bottom: parent.bottom;
        anchors.leftMargin: 4;
        anchors.horizontalCenter: parent.horizontalCenter;
        onColorPicked: setTextColor(clr);
    }
}
