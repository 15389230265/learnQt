import QtQuick 2.0
import QtQuick.Controls 2.4


//动态创建的对象，特指使用 Qt.createComponent() 或 Qt.createQmlObject() 方法创建的对象，
//使用 Loader 创建的对象，应当通过将 source 设置为空串或将 sourceComponent 设置为 undefined 触发 Loader 销毁它们
Rectangle {
    id: rootItem;
    width: 360;
    height: 300;
    property int count: 0;
    property Component component: null;
    property var dynamicObjects: new Array();

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
            colorPicker = rootItem.component.createObject(rootItem, {"color" : clr, "x" : rootItem.dynamicObjects.length *55, "y" : 10});
            colorPicker.colorPicked.connect(rootItem.changeTextColor);
            rootItem.dynamicObjects[rootItem.dynamicObjects.length] = colorPicker;
            console.log("add, rootItem.dynamicObject.length = ", rootItem.dynamicObjects.length);
            }
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

    Button{
        id: del;
        text: "del";
        anchors.left: add.right;
        anchors.leftMargin: 4;
        anchors.bottom: add.bottom;
        onClicked: {
            console.log("rootItem.dynamicObject.length = ", rootItem.dynamicObjects.length);
            if(rootItem.dynamicObjects.length > 0){
                var deleted = rootItem.dynamicObjects.splice(-1, 1);
                deleted[0].destroy();
            }
        }
    }
}
