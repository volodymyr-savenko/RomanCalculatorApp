import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15 //Button
import QtQuick.Layouts 1.15 //GridLayout

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
        id: display

        anchors.top: parent.top
        anchors.topMargin: spacing
        anchors.left: parent.left
        anchors.leftMargin: spacing
        anchors.right: parent.right
        anchors.rightMargin: spacing

        text: calculatorEngine.displayText
        font.pixelSize: 40
        horizontalAlignment: Text.AlignRight
        background: Rectangle {}
    }

    GridLayout {
        id: operandButtonsGrid

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

            SquareButton {
                id: operandButton
                text: modelData
                onPressed: calculatorEngine.updateRomanLiteral(operandButton.text)
            }
        }
    }

    GridLayout {
        id: operatorButtonsGrid

        columns: 2

        rowSpacing: spacing
        columnSpacing: spacing

        width: columns * buttonSize + (columns - 1) * spacing
        height: 3 * buttonSize + 2 * spacing

        anchors.right: parent.right
        anchors.rightMargin: spacing
        anchors.bottom: parent.bottom
        anchors.bottomMargin: spacing

        SquareButton {
            id: addButton
            text: "+"
            onPressed: calculatorEngine.add();
        }

        SquareButton {
            id: substructButton
            text: "-"
            onPressed: calculatorEngine.substruct();
        }

        SquareButton {
            id: multiplyButton
            text: "*"
            onPressed: calculatorEngine.multiply();
        }

        SquareButton {
            id: divideButton
            text: "/"
            onPressed: calculatorEngine.divide();
        }

        SquareButton {
            id: clearButton
            text: "Clear"
            onPressed: calculatorEngine.clear();
        }

        SquareButton {
            id:  equalButton
            text: "="
            onPressed: calculatorEngine.evaluate();
        }
    }
}
