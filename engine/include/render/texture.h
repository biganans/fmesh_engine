#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <string>
#include "raw_image.h"

enum texfilter {
    nearest,
    linear,
};

enum texwarp{
    repeat,
    clamp_to_edge,
    mirrored_repeat,
};

struct texparms
{
    enum texfilter filter = texfilter::linear;
    enum texwarp warp = texwarp::repeat;
};

class texture
{
public:
    virtual void bind() = 0;
    virtual void load_image2d(raw_image& ri, const texparms& parms = texparms()) = 0;
    virtual void load_tex2d(const std::string& img_file,
                            const texparms& parms = texparms()) = 0;
    virtual ~texture(){}
    static texture* alloc();
};

#endif
