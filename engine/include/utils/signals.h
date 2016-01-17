#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <string>
#include <tuple>
#include <set>
#include <list>
#include <type_traits>



struct slot_less {
    template<typename ...T>
    bool operator()(const std::tuple<T...>& x, const std::tuple<T...>& y) const
    {
        return std::get<0>(x) < std::get<0>(y);
    }
};

typedef unsigned int slot_handle;


template
<
    typename F,
    typename ID = unsigned int,
    typename SLOT = std::function<F>,
    typename SLOT_TUPLE = std::tuple<slot_handle, ID, SLOT>,
    typename CMP = slot_less
>
class signals
{
    unsigned int _index = 0;
    std::set<SLOT_TUPLE, CMP> _slots;
    std::list<slot_handle> _disable;

    void remove(slot_handle h)
    {
        this->_slots.erase(find_if(this->_slots.begin(),
                                    this->_slots.end(),
                                    [=](const SLOT_TUPLE& st) {
                                        return h == std::get<0>(st);
                                    }), this->_slots.end());
    }

    void remove_disable()
    {
        if (this->_disable.empty()) return;

        for (auto& h : this->_disable) {
            this->remove(h);
        }

        this->_disable.clear();
    }

public:

    void clear()
    {
        this->_index = 0;
        this->_slots.clear();
        this->remove_disable();
    }

    std::size_t size() const
    {
        return this->_slots.size();
    }

    bool empty() const
    {
        return this->_slots.empty();
    }

    slot_handle connect(const SLOT& slot)
    {
        static_assert(std::is_integral<ID>::value, "ERROR: ID must be int");

        slot_handle h = ++this->_index;

        SLOT_TUPLE st = std::make_tuple(h, h, slot);
        this->_slots.insert(st);
        return h;
    }

    slot_handle connect(const ID& ids, const SLOT& slot)
    {
        slot_handle h = ++this->_index;

        SLOT_TUPLE st = std::make_tuple(h, ids, slot);
        this->_slots.insert(st);
        return h;
    }

    void disconnect(slot_handle h)
    {
        this->_disable.push_back(h);
    }


    template<typename... ARGS>
    void send(const ID& ids, ARGS... args)
    {
        this->remove_disable();
        for (auto& e : this->_slots) {
            if (std::get<1>(e) == ids) {
                std::get<2>(e)(args...);
            }
        }
    }


    template<typename... ARGS>
    void send(ARGS... arg)
    {
        this->remove_disable();
        for (auto& e : this->_slots) {
            std::get<2>(e)(arg...);
        }
    }

};


#endif
