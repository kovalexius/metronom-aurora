# metronome

A simple metronome app for the Jolla / Sailfish OS.

## TODO

* use libaudioresource to acquire audio permissions
* use libpulse-simple to play the sound
* draw some nice visualization of the click


## Notes

* OpenGL ES 2.0 is supported

    http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html

* SDL 2.0 will be supported soon

    https://github.com/nemomobile-packages/libsdl/tree/nemo
    https://github.com/search?q=%40nemomobile-packages+libsdl

    Until then, can link statically against SDL 2.0.

    For portability:

    https://github.com/p3/regal

* Use libaudioresource-qt for sound?

    https://github.com/nemomobile/libaudioresource-qt/
    https://github.com/nemomobile/libaudioresource


