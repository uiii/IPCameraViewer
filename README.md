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

run
===

in build directory

```
./IPCameraViewer
```