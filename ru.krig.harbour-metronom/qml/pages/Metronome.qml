/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import QtMultimedia 5.0

Page {
    id: metronome

    property int bar: 0
    property int measure: 4
    property int bpm: 130
    property int sound: 0

    Timer {
        id: tempo
        interval: (60.0 / 130) * 1000.0
        running: false
        repeat: true
        onTriggered: metronome.tock()
    }

    function setSound(soundId) {
        tempo.stop()
        bar = 0
        sound = soundId
    }

    function setBPM(new_bpm) {
        bpm = new_bpm
        tempo.interval = (60.0 / bpm) * 1000.0
    }

    function startPlayback() {
        tempo.start()
    }

    function stopPlayback() {
        tempo.stop()
        bar = 0
        label.text = ""
    }

    function tock() {
        bar = bar + 1
        if (bar > measure)
            bar = 1
        label.text = String(bar)
        playClick(bar, measure, sound)
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        PullDownMenu {
            MenuItem {
                text: "Settings"
                onClicked: {
                    stopPlayback()
                    pageStack.push(Qt.resolvedUrl("Settings.qml"))
                }
            }
        }

        Column {
            id: column
            spacing: Theme.paddingLarge
            width: parent.width

            Item {
                width: parent.width
                height: Theme.paddingLarge*2
            }

            Rectangle {
                id: progressCircle
                width: (parent.width < parent.height ? parent.width : parent.height) - Theme.paddingLarge * 4
                height: width
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#00000000"
                border.color: Theme.secondaryColor
                border.width: Theme.paddingSmall
                radius: width * 0.5
                Label {
                    id: label
                    color: Theme.primaryColor
                    text: ""
                    font.pixelSize: parent.height / 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge*2
            }

            Row {
                id: iconButtons
                spacing: Theme.paddingLarge

                anchors.horizontalCenter: parent.horizontalCenter

                IconButton {
                    icon.source: "image://theme/icon-l-clear"
                    enabled: tempo.running
                    onClicked: stopPlayback()
                }

                IconButton {
                    icon.source: "image://theme/icon-l-play"
                    enabled: !tempo.running
                    onClicked: startPlayback()
                }
            }

            Slider {
                minimumValue: 60
                maximumValue: 240
                stepSize: 1
                value: bpm
                label: "Tempo"
                width: parent.width
                valueText: value
                onValueChanged: metronome.setBPM(value)
            }
        }
    }
}


