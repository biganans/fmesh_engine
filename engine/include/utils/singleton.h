#ifndef _SINGLETON_H_
#define _SINGLETON_H_


template<typename T>
class singleton
{
private:
    singleton(const singleton&);
    singleton& operator=(const singleton&);
public:
    static T& ref()
    {
        static T object;
        return object;
    }

    static T* ptr()
    {
        return &ref();
    }

protected:
    singleton() {};
    virtual ~singleton() {};
};


#endif
