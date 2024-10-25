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


Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: page.height

        Column {
            id: column
            spacing: Theme.paddingLarge
            width: parent.width

            PageHeader { title: "Metronom" }

            ComboBox {
                width: column.width - Theme.paddingLarge*2
                label: "Time signature"
                currentIndex: 1

                menu: ContextMenu {
                    MenuItem {
                        text: "3/4"
                        onClicked: setTimeSignature(3)
                    }
                    MenuItem {
                        text: "4/4"
                        onClicked: setTimeSignature(4)
                    }
                    MenuItem {
                        text: "7/8"
                        onClicked: setTimeSignature(7)
                    }
                }
            }

            ComboBox {
                width: column.width - Theme.paddingLarge*2
                label: "Sound"
                currentIndex: getSoundId()

                menu: ContextMenu {
                    MenuItem { text: "Cowbell" }
                    MenuItem { text: "Click" }
                }

                onValueChanged: {
                    setSound(currentIndex)
                }
            }
        }

        Label {
            id: label
            color: Theme.primaryColor
            font.family: Theme.fontFamilyHeading
            textFormat: Text.RichText
            text: "<style>a:link { color: " + Theme.highlightColor + "; }</style>" +
                  "Made by krig.<br/><br/>" +
                  "<a href=\"http://kri.gs/\">http://kri.gs</a><br/><br/>"
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
            }

            wrapMode: Text.Wrap
            width: parent.width - 2*Theme.paddingLarge
            horizontalAlignment: Text.AlignHCenter

            onLinkActivated: {
                Qt.openUrlExternally(link)
            }
        }
    }
}





