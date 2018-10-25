import QtQuick 2.0
import QtQuick.Controls 2.4

//我们定义 Component 时要遵守的一个约定：组件名字必须和 qml 文件名一致
//在单独文件内定义组件，不需要 Component 对象，只有在其它 QML 文档中嵌入式定义组件时才需要 Component 对象
Rectangle {
    id: colorPicker;
    width: 50;
    height: 30;
    signal colorPicked(color clr);

    function configureBorder(){
        colorPicker.border.width = colorPicker.focus ? 2 : 0;
        colorPicker.border.color = colorPicker.focus ? "#90D750" : "#808080";
    }

    MouseArea{
        anchors.fill: parent;
        onClicked: {
            colorPicker.colorPicked(colorPicker.color);
            mouse.accepted = true;
            colorPicker.focus = true;
        }
    }
    //回车
    Keys.onReturnPressed: {
        colorPicked(colorPicker.color);
        event.accepted = true;
    }
    //空格
    Keys.onSpacePressed: {
        colorPicked(colorPicker.color);
        event.accepted = true;
    }

    onFocusChanged: {
        //重新设置边框的宽度和颜色
        configureBorder();
    }

    Component.onCompleted: {
        configureBorder();
    }
}
