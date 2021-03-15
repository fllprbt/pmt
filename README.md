# PMT (Personal Music Tutor)

###### Digital Sound Processing Utilities built with [Qt](https://github.com/qt), [PortAudio](https://github.com/PortAudio/portaudio), [Aubio](https://github.com/aubio/aubio)

## To quickly test pitch detection on Linux (Requires Docker)

`docker build . -t fll:pmt`
`docker run -it --init --device /dev/snd fll:pmt` the init is important so that your container stops with CTRL-C

## Dev Guide (Mac & Linux)

Compilation requires versions of c++14 and on. There is a temporary issue with a missing public key while running `make` on aubio. As a temporary fix, please commend out the `gpg --verify` (line 30) step in `aubio/scripts/get_waf.sh` which blocks the build.

* Clone repo: `git clone https://github.com/fllprbt/pmt.git --recurse-submodules && cd pmt`.
* Install Qt5: for Mac, install through `brew install qt` or refer to [qt5 on mac](https://doc.qt.io/qt-5/macos.html). For Linux, install as ubuntu pkg `sudo apt-get install qt5-default` or refer to [qt5 on linux](https://wiki.qt.io/Install_Qt_5_on_Ubuntu). Note that in Mac you should add the path of _qmake_ to your terminal profile. For example, if you installed qt5 with brew it is in `/usr/local/opt/qt5/bin`.
* PortAudio dependency check: before building the PortAudio submodule, ensure that you comply with the [linux](http://files.portaudio.com/docs/v19-doxydocs/compile_linux.html) or [mac](http://files.portaudio.com/docs/v19-doxydocs/compile_mac_coreaudio.html) dependencies.
* Build PortAudio: `cd portaudio && ./configure && make && cd ..`
* Build Aubio: `cd aubio && make && cd ..`
* Build project: on project root run `qmake src/pmt.pro && make`.

You are done! For Mac run `./pmt.app/Contents/MacOS/pmt` and for Linux `./pmt`

## Key considerations

The current version of pitch detection has not been optimized for different environments/input contexts. Thus, for best results it is advised to use the app in noise-free environments with the sound producing mediums close to the input sources. 
