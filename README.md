dependecies
===========

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

compile
=======

```
mkdir build
cd build
qmake ../src
make
```

> Note: If you have installed qt5 and qt4 together, you have to use Qt4 version of qmake (Ubuntu: `qt4-qmake`, Archlinux: `qmake-qt4`)

run
===

in build directory

```
./IPCameraViewer
```

usage
===

Enter video stream url or IP camera connection string.


tested cameras
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
