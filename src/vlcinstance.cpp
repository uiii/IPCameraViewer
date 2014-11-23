/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file (https://github.com/uiii/IPCameraViewer/LICENSE) for details.
 */

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
