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
        color: "#C0C0C0";
        //MouseArea 对象可以附加到一个 item 上供 item 处理鼠标事件，它本身是一个不可见的 item 。
        MouseArea {
            anchors.fill: parent;
            acceptedButtons: Qt.LeftButton | Qt.RightButton;
            //onClicked 信号的参数是 MouseEvent 类型，名为 mouse ，所以你可以在信号处理器中直接使用 mouse 来查询鼠标事件的详情。
            onClicked: {
                if(mouse.button === Qt.RightButton){
                    Qt.quit();
                }
                else if(mouse.button === Qt.LeftButton){
                    rec1.color = Qt.rgba((mouse.x % 255) / 255.0, (mouse.y % 255) / 255.0, 0.6, 1);
                }
            }
            onDoubleClicked: {
                rec1.color = "gray";
            }
        }
    }
}
