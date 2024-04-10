import QtQuick 2.0
import StyleSettings 1.0
Rectangle {
    id: root
    color: Style.backgroundColor
    //нажал ли пользователь на наше делегат:
    opacity: _delegateArea.pressed ? Style.secondaryOpacity
                                   : Style.emphasisOpacity
    MouseArea {
        id: _delegateArea
        anchors.fill: root
    }
}
