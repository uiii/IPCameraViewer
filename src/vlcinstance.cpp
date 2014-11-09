#include "vlcinstance.h"

#include <iostream>

#include <vlc/vlc.h>

VlcInstance::VlcInstance()
{
    instance = libvlc_new(0, NULL);
}

VlcInstance::~VlcInstance()
{
    libvlc_release(instance);
}

VlcInstance::operator libvlc_instance_t*()
{
    return instance;
}
