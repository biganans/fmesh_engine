#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <deque>
#include <utils/singleton.h>


namespace fmesh {



template<typename T>
class input_manager
{
    std::deque<T> _inputs;
public:

    void clear()
    {
        this->_inputs.clear();
    }

    bool empty() const
    {
        return this->_inputs.empty();
    }

    size_t size() const
    {
        return this->_inputs.size();
    }

    void add(const T& e)
    {
        this->_inputs.push_back(e);
    }

    T get()
    {
        T e = this->_inputs.front();
        this->_inputs.pop_front();
        return e;
    }

    void uget(const T& e)
    {
        this->_inputs.push_front(e);
    }

    T get_back()
    {
        T e = this->_inputs.back();
        this->_inputs.pop_back();
        return e;
    }
};

typedef singleton<input_manager<int> > g_input_manager;

}

#endif
