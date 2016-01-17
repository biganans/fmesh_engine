#ifndef _MATHS_H_
#define _MATHS_H_
#include <iostream>
#include <cmath>

#define USE_GLM //todo
#if defined(USE_GLM)
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define constexpr
#endif
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/fwd.hpp>

using glm::vec4;
using glm::vec3;
using glm::vec2;
using glm::mat4;
using glm::mat3;
using glm::rotate;
using glm::scale;
using glm::translate;
using glm::ortho;
using glm::frustum;
using glm::lookAt;
using glm::length;
using glm::normalize;
using glm::dot;
using glm::cross;
using glm::mat3_cast;
using glm::mat4_cast;
using glm::quat_cast;
using glm::inverse;
using glm::row;
using glm::column;
using glm::distance;
using glm::squad;
using glm::toMat3;
using glm::toMat4;
using glm::toQuat;
using glm::shortMix;
using glm::fastMix;
using glm::quat;
using glm::value_ptr;
#endif

static inline std::ostream& operator<<(std::ostream& os, const vec2& v)
{
    return os << "[" << v.x << ", " << v.y << "]";
}

static inline std::ostream& operator<<(std::ostream& os, const vec3& v)
{
    return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

static inline std::ostream& operator<<(std::ostream& os, const vec4& v)
{
    return os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
}

static inline std::istream& operator>>(std::istream& is, vec2& v)
{
    char c;
    return is >> c >> v.x >> c >> v.y;
}

#undef M_PI
#define M_PI 3.14159265358979323846264338327950288


#define RADIAN(x) \
        ((x)*(M_PI)/(180.0))

#define DEGREES(x) \
        ((x)*(180.0)/(M_PI))

#define M_RI(ru) \
        ((ru) / 2.0 / tan(RADIAN(30)))


#undef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#undef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))



#undef CLAMP
#define CLAMP(_x, _min, _max) \
        (MAX((_min), MIN((_x), (_max))))

#define ACCU 0.00001
static inline bool eq_zero(float x)
{
    return (x >= -ACCU) && (x <= ACCU);
}



template <typename T, typename T2, typename T3>
static inline auto mix2(const T& x,
                        const T2& y,
                        const T3& factor)->decltype(x + y)
{
    return (y - x) * pow(factor, 2) + x;
}


template <typename T, typename T2, typename T3>
static inline auto mix(const T& x,
                       const T2& y,
                       const T3& factor)->decltype(x + y)
{
    return (y - x) * factor + x;
}

static inline float invsqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f-xhalf*x*x);
    return x;
}



#endif
