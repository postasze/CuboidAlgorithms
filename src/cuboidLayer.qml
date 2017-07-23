import QtQuick 2.0

Item {
    id: root
    width: 500; height: 500
    property int blockSize: 10

    Repeater {
        id: grid
        model: layerModel
        anchors.centerIn: parent

        Rectangle {
            id: gridCell
            x: model.modelData.x * root.blockSize
            y: model.modelData.y * root.blockSize
            height: model.modelData.width * root.blockSize
            width: model.modelData.length * root.blockSize
            color: model.modelData.hashColor
            border { color: "black"; width: 1 }
        }
    }

    Repeater {
        id: cuboids
        model: cuboidModel
        anchors.centerIn: parent

        Rectangle {
            id: cuboid
            x: model.modelData.x * root.blockSize
            y: model.modelData.y * root.blockSize
            height: model.modelData.width * root.blockSize
            width: model.modelData.length * root.blockSize
            color: Qt.hsla(model.modelData.hashColor / 100, 1, 0.5)
            border { color: "black"; width: 1 }
        }
    }
}


