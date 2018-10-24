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
        // Keys 对象是 Qt Quick 提供的，专门供 Item 处理按键事件的对象。
        //enabled 属性控制是否处理按键。
        // forwardTo 属性是列表类型，它表示传递按键事件给列表内的对象，如果某个对象 accept 了某个按键，那位列其后的对象就不会收到该按键事件。
        //priority 属性允许你设置 Keys 附加属性的优先级，有两种，在 Item 之前处理按键，这是默认行为，在 Item 之后处理按键。
        //如果你想某个元素处理按键，需要把焦点给它，这通过 Item 的 focus 属性来控制，置 true 即可。
        focus: true;
        Keys.enabled: true;
        Keys.onEscapePressed: {
            Qt.quit();
        }
        Keys.forwardTo: [moveText, likeQt];

        Text {
            id: moveText;
            x: 20;
            y: 20;
            width: 200;
            height: 30;
            text: qsTr("Moving Text");
            color: "blue";
            font { bold: true; pixelSize: 24;}
            Keys.enabled: true;
            Keys.onPressed: {
                switch(event.key){
                case Qt.Key_Left:
                    x -=10;
                    break;
                case Qt.Key_Right:
                    x +=10;
                    break;
                case Qt.Key_Down:
                    y +=10;
                    break;
                case Qt.Key_Up:
                    y -=10;
                    break;
                default:
                    return;
                }
                //KeyEvent 代表一个按键事件，如果一个按键被处理， event.accepted 应该被设置为 true 以免它被继续传递；
                event.accepted = true;
            }
        }
        //Qt Quick 提供的一些元素本身会处理按键，比如 CheckBox ，它响应空格键来选中或取消选中。
        CheckBox {
            id: likeQt;
            text: "Like Qt Quick";
            anchors.left: parent.left;
            anchors.leftMargin: 10;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 10;
            z: 1;
        }
    }
}
