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
