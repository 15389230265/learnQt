import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle {
    id: rootItem;
    width: 360;
    height: 300;
    property int count: 0;
    property Component component: null;

    Text {
        id: coloredText;
        text: qsTr("Hello World!");
        anchors.centerIn: parent;
        font.pixelSize: 24;
    }

    function changeTextColor(clr){
        coloredText.color = clr;
    }

    function createColorPicker(clr){
        if(rootItem.component == null){
            //Qt 对象的 createComponent() 方法可以根据 QML 文件动态的创建一个组件。
            //一旦你拥有了组件对象，就可以调用它的 createObject() 方法创建一个组件的实例
            rootItem.component = Qt.createComponent("ColorPicker.qml");
        }
        var colorPicker;
        if(rootItem.component.status == Component.Ready){
            colorPicker = rootItem.component.createObject(rootItem, {"color" : clr, "x" : rootItem.count *55, "y" : 10});
            colorPicker.colorPicked.connect(rootItem.changeTextColor);
        }

        rootItem.count++;
    }

    Button{
        id: add;
        text: "add";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked: {
            createColorPicker(Qt.rgba(Math.random(), Math.random(), Math.random(), 1));
        }
    }
}
