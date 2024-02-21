//import related modules
 import QtQuick
 import QtQuick.Controls

 //window containing the application
 ApplicationWindow {

     visible: true

     //title of the application
     title: qsTr("Hello World")
     width: 640
     height: 480

     Image{
        anchors.fill: parent;
        source: "qrc:/resource/bg.png"
     }

     //menu containing two menu items
     menuBar: MenuBar {
         Menu {
             title: qsTr("File")
             MenuItem {
                 text: qsTr("&Open")
                 onTriggered: console.log("Open action triggered")
             }
             MenuItem {
                 text: qsTr("Exit")
                 onTriggered: Qt.quit()
             }
         }
     }

     //Content Area

     //a button in the middle of the content area
     Button {
         text: qsTr("Hello World")
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.verticalCenter: parent.verticalCenter
     }

    Rectangle {
        color: "lightgray"
        width: 200
        height: 200

         property int animatedValue: 0
         SequentialAnimation on animatedValue {
             loops: Animation.Infinite
             PropertyAnimation { to: 150; duration: 1000 }
             PropertyAnimation { to: 0; duration: 1000 }
         }

         Text {
             anchors.centerIn: parent
             text: parent.animatedValue
         }
     }
 }


