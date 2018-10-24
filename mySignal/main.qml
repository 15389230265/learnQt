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
        color: "#C0C0C0";

        Text {
            id: coloredText;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 4;
            text: qsTr("Hello World!");
            font.pixelSize: 32;
        }
        //组件是可以重复利用的，一个组件可以在一个单独的 qml 文件中定义，也可以嵌入到其它 qml 文档中来定义以方便简单组件的使用。
        Component {
            id: colorComponent;
            Rectangle {
                id: colorPicker;
                width: 50;
                height: 30;
                //信号其实是个方法（函数），所以呢，它的发射，实际是通过调用以信号名为名的方法达成的
                signal colorPicked(color clr);
                MouseArea {
                    anchors.fill: parent
                    onPressed: colorPicker.colorPicked(colorPicker.color);
                }
            }
        }
        //Loader 是专门用来动态创建组件的，它可以从 qml 文件中创建组件，也可以指定 sourceComponent 来创建，
        Loader{
            id: redLoader;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 4;
            sourceComponent: colorComponent;
            //在 Loader 的 onLoaded 信号处理器内给 Rectangle 对象配置颜色。
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
        //target 指向刚才说的 Loader 对象的 item 属性， item 属性实际指向 Loader 创建的对象。
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


        Rectangle {
            id: relay;
            //  signal 对象的这种连接方式，使用起来比信号处理器更加灵活。
            //前面介绍信号处理器时，已经提到，信号处理器和信号是一对一的关系。
            //而 signal 对象的这种连接方式，使得一个信号能够连接多个方法。
            signal messageReceived(string person, string notice);
            Component.onCompleted: {
                relay.messageReceived.connect(sendToPost);
                relay.messageReceived.connect(sendToTelegraph);
                relay.messageReceived.connect(sendToEmail);
                relay.messageReceived("Tom", "Happy Birthday");
            }

            function sendToPost(person, notice) {
                console.log("Sending to post: " + person + ", " + notice);
            }
            function sendToTelegraph(person, notice) {
                console.log("Sending to telegraph: " + person + ", " + notice);
            }
            function sendToEmail(person, notice) {
                console.log("Sending to email: " + person + ", " + notice);
            }
        }

        Rectangle {
            id: forwarder;
            width: 100;
            height: 100;

            signal send();
            onSend: console.log("Send clicked");

            MouseArea {
                id: mousearea;
                anchors.fill: parent;
                onClicked: console.log("MouseArea clicked");
            }

            Component.onCompleted: {
                //signal 对象的 connect() 方法允许你连接一个信号到另外一个信号或者方法。其实没差别，信号本身也是个方法（函数）。
                //当信号发射时，连接到信号上的其它信号或方法就会被调用。
                mousearea.clicked.connect(send);
            }
        }
    }
}
