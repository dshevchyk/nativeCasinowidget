import QtQuick 2.6
import QtQuick.Window 2.2

import com.playtech 1.0
import QtQuick.Window 2.2
Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property int size: Screen.desktopAvailableWidth/7
    property int margin: 50

    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            Qt.quit();
        }
    }
    Rectangle
    {
        id:parentRect
        width: childrenRect.width
        height: childrenRect.height
        x:Screen.desktopAvailableWidth/10
        y:Screen.desktopAvailableHeight/10
        color: "blue"
        SequentialAnimation {
            loops: Animation.Infinite

            running: false
            NumberAnimation {
                target: parentRect;
                property: "y";
                from: 0;
                to: Screen.desktopAvailableHeight;
                duration: 2000
            }
            NumberAnimation {
                target: parentRect;
                property: "y";
                from: Screen.desktopAvailableHeight;
                to: 0;
                duration: 2000
            }
        }
        NativeButtonsGroup
        {
            id:buttonsGroup
            NativeButton
            {
                id: leftTopWidget
                width: size
                height: size
                Rectangle
                {
                    anchors.fill: parent
                    color: "red"
                }
                onNativeClicked: {
                    console.log("onNativeClicked success")
                }
            }

            NativeButton
            {

                id: leftBottomWidget
                anchors.top: leftTopWidget.bottom
                anchors.topMargin: margin
                width: size
                height: size
                Rectangle
                {
                    anchors.fill: parent
                    color: "red"
                }
            }
            NativeButton
            {
                id: rightTopWidget
                anchors.left: leftTopWidget.right
                anchors.leftMargin: margin
                width: size
                height: size
                Rectangle
                {
                    anchors.fill: parent
                    color: "red"
                }
            }

            NativeButton
            {
                id: rightBottomWidget
                anchors.top: leftTopWidget.bottom
                anchors.left: leftBottomWidget.right
                anchors.leftMargin: margin
                anchors.topMargin: margin
                width: size
                height: size
                Rectangle
                {
                    anchors.fill: parent
                    color: "red"
                }
            }
        }
    }
}
