/*
 * This file is part of IPCameraViewer project (https://github.com/uiii/IPCameraViewer)
 * Copyright (c) 2014 Richard Jedlička <jedlicka.r@gmail.com> (http://uiii.cz)
 *
 * This software may be modified and distributed under the terms of the MIT license.
 * See the LICENSE file for details.
 */

#ifndef VLCINSTANCE_H
#define VLCINSTANCE_H

class libvlc_instance_t;

class VlcInstance
{
public:
    VlcInstance();
    ~VlcInstance();

    operator libvlc_instance_t *();

private:
    libvlc_instance_t* instance;
};

#endif // VLCINSTANCE_H
