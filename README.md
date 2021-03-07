# PMT (Personal Music Tutor)

###### Digital Sound Processing Toolkit built with [Qt](https://github.com/qt) and [PortAudio](https://github.com/PortAudio/portaudio)

## Setup Guide (Mac & Linux)

* Clone repo: `git clone https://github.com/fllprbt/pmt.git --recurse-submodules && cd pmt`.
* Install Qt: for Mac, install through `brew install qt` or refer to [qt5 on mac](https://doc.qt.io/qt-5/macos.html). For Linux, install as ubuntu pkg `sudo apt-get install qt5-default` or refer to [qt5 on linux](https://wiki.qt.io/Install_Qt_5_on_Ubuntu). Note that in Mac you should add the path of _qmake_ to your terminal profile. For example, if you installed qt5 with brew it is in `/usr/local/opt/qt5/bin`.
* PortAudio dependency check: before building the PortAudio submodule, ensure that you comply with the [linux](http://files.portaudio.com/docs/v19-doxydocs/compile_linux.html) or [mac](http://files.portaudio.com/docs/v19-doxydocs/compile_mac_coreaudio.html) dependencies.
* Build PortAudio: `cd portaudio && ./configure && make && make install` (on linux you may need to `sudo make install` instead).
* Build project: on project root run `qmake src/pmt.pro && make`.

You are done! For Mac run `./pmt.app/Contents/MacOS/pmt` and for Linux `./pmt`
