import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: root

    readonly property int spacing: 5
    readonly property int buttonSize: 50

    width: 280
    height: 220

    color: "oldlace"

    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    visible: true
    title: qsTr("Roman Calculator")

    Label {
        id: _display

        anchors.top: parent.top
        anchors.topMargin: spacing
        anchors.left: parent.left
        anchors.leftMargin: spacing
        anchors.right: parent.right
        anchors.rightMargin: spacing

        text: ""
        font.pixelSize: 40
        horizontalAlignment: Text.AlignRight
        background: Rectangle {}
    }

    GridLayout {
        id: _operandButtonsGrid

        columns: 3

        rowSpacing: spacing
        columnSpacing: spacing

        width: columns * buttonSize + (columns - 1) * spacing
        height: 3 * buttonSize + 2 * spacing

        anchors.left: parent.left
        anchors.leftMargin: spacing
        anchors.bottom: parent.bottom
        anchors.bottomMargin: spacing

        Repeater {
            model: ["I", "V", "X", "L", "C", "D", "M"]

            Button {
                id: _operandButton
                text: modelData

                implicitHeight: buttonSize
                implicitWidth: buttonSize

                onPressed: _display.text += _operandButton.text
            }
        }
    }

    GridLayout {
        id: _operatorButtonsGrid

        columns: 2

        rowSpacing: spacing
        columnSpacing: spacing

        width: columns * buttonSize + (columns - 1) * spacing
        height: 3 * buttonSize + 2 * spacing

        anchors.right: parent.right
        anchors.rightMargin: spacing
        anchors.bottom: parent.bottom
        anchors.bottomMargin: spacing

        Repeater {
            model: ["+", "-", "x", "/", "%", "="]

            Button {
                id:  _operatorButton
                text: modelData

                implicitHeight: buttonSize
                implicitWidth: buttonSize

                onPressed: _display.text += _operatorButton.text
            }
        }
    }

//    Rectangle {
//        id: _operandButtonsFrame

//        anchors.fill: _operandButtonsGrid
//        color: "transparent"
//        border.color: "grey"
//        border.width: 1
//    }

//    Rectangle {
//        id:_operatorButtonsFrame

//        anchors.fill: _operatorButtonsGrid
//        color: "transparent"
//        border.color: "grey"
//        border.width: 1
//    }
}
