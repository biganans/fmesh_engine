#ifndef _META_H_
#define _META_H_

#define $property(type, var)                              \
private:                                                  \
    type _##var;                                          \
public:                                                   \
    const type& var() const {return _##var;}              \
    void set_##var(const type& t) {this->_##var = t;}

#define $property_readonly(type, var)                     \
private:                                                  \
    type _##var;                                          \
public:                                                   \
    const type& var() const {return _##var;}

#define $property_init(type, var, value)                  \
private:                                                  \
    type _##var = value;                                  \
public:                                                   \
    const type& var() const {return _##var;}              \
    void set_##var(const type& t) {this->_##var = t;}

#define $property_copy(type, var)                         \
private:                                                  \
    type _##var;                                          \
public:                                                   \
    type var() const {return _##var;}                     \
    void set_##var(type t) {this->_##var = t;}

#define $property_readonly_copy(type, var)                \
private:                                                  \
    type _##var;                                          \
public:                                                   \
    type var() const {return _##var;}

#define $property_init_copy(type, var, value)             \
private:                                                  \
    type _##var = value;                                  \
public:                                                   \
    type var() const {return _##var;}                     \
    void set_##var(type t) {this->_##var = t;}

#define $meta_type(cls, value)                                  \
    public:                                                     \
    virtual int get_type() const                                \
    {                                                           \
        return cls::type();                                     \
    }                                                           \
    static int type()                                           \
    {                                                           \
        return value;                                           \
    }                                                           \
    std::string type_string() {return #cls;}


#endif
