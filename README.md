About project
===

IPCameraViewer the QT frontend for displaying multiple video streams on the screen.
The program supports tiled display windows and multiple tabs. Configuration can be imported or exported as a JSON file.

Dependecies
===

- make
- g++
- qt4.8
- libVLC
- VLC
- QJson

> On Ubuntu:
> `sudo apt-get install g++ qt4-default libvlc-dev vlc libqjson-dev`
>
> On Archlinux:
> `pacman -S gcc-multilib qt4 libvlc vlc qjson`

Compile
===

```
mkdir build
cd build
qmake ../src
make
```

> Note: If you have installed qt5 and qt4 together, you have to use Qt4 version of qmake (Ubuntu: `qt4-qmake`, Archlinux: `qmake-qt4`)

Run
===

in build directory

```
./IPCameraViewer
```

Usage
===

Create window and enter video stream url or IP camera connection string.

Export JSON configuration file can be loaded at application startup.
```
./IPCameraViewer /path/to/config.json
```

Tested cameras
===

Apexis APM-J0233-POE-IRC
```
http://IPADDRESS/videostream.asf?user=USERNAME&pwd=PASSWORD&rolution=640*480
```

Apexis APM-J011-WS-IRC
```
http://IPADDRESS/videostream.asf?user=USERNAME&pwd=PASSWORD&rolution=640*480
```

Apexis APM-J012-WS
```
http://IPADDRESS/videostream.asf?user=USERNAME&pwd=PASSWORD
```
