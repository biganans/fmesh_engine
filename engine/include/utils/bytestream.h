#ifndef _BYTESTREAM_H_
#define _BYTESTREAM_H_
#include <cstdlib>
#include <cstring>
#include <string>
#include <cassert>
#include <algorithm>
#include <stdexcept>

#define SBUFSIZE ((size_t)1024)
class bytestream
{
    char *_buf;
    size_t _size;
    size_t _index;
    size_t _alloc_size;
public:

    bytestream() : _buf(NULL), _size(0), _index(0), _alloc_size(0)
    {
    }

    bytestream(size_t s) : _buf((char*)malloc(s)), _size(0), _index(0), _alloc_size(s)
    {
    }

    template<typename T>
    bytestream(const T* ptr, size_t len)
        : _buf((char*)malloc(sizeof(T) * len)), _size(0), _index(0), _alloc_size(sizeof(T) * len)
    {
        this->append(ptr, len);
    }

    bytestream(const bytestream& e)
    {
        this->append((char*)e.data(), e.size());
    }

    bytestream& operator=(const bytestream& e)
    {
        if (this != &e) {
            this->clear();
            this->append((char*)e.data(), e.size());
        }
        return *this;
    }

    void move(bytestream&& e)
    {
        if (this->_buf != NULL) free(this->_buf);

        this->_buf        = e._buf;
        this->_size       = e._size;
        this->_index      = e._index;
        this->_alloc_size = e._alloc_size;

        e._buf        = NULL;
        e._size       = 0;
        e._index      = 0;
        e._alloc_size = 0;
    }

    bytestream(bytestream&& e)
    {
        this->move(std::move(e));
    }

    bytestream& operator=(bytestream&& e)
    {
        if (this != &e) {
            this->move(std::move(e));
        }
        return *this;
    }

    ~bytestream()
    {
        if (this->_buf != NULL) free(this->_buf);
    }

    const void* data() const
    {
        return (const void*)this->_buf;
    }

    void clear()
    {
        this->_size = 0;
        this->_index = 0;
    }

    bool empty() const
    {
        return this->_size == 0;
    }

    size_t size() const
    {
        return this->_size;
    }

    void resize(size_t s)
    {
        if (s == 0) return;

        if (this->_buf == NULL) {
            this->_buf = (char*)malloc(s);
        } else {
            this->_buf = (char*)realloc(this->_buf, s);
        }

        this->_alloc_size = s;
    }

    template<typename T>
    void append(const T& m)
    {
        if (this->_buf == NULL) this->resize(std::max(SBUFSIZE, sizeof(T)));

        size_t rsize = this->_size + sizeof(T);
        if (this->_alloc_size < rsize) {
            this->resize(rsize);
        }
        ::memcpy((void*)(this->_buf + this->_size), (void*)&m, sizeof(T));
        this->_size += sizeof(T);
    }

    void append(const std::string& str)
    {
        this->append(str.c_str(), str.length() + 1);
    }

    void append(const bytestream& s)
    {
        this->append((char*)s.data(), s.size());
    }

    template<typename T>
    void append(const T* ptr, size_t len)
    {
        assert(ptr);
        if (len == 0) return;
        size_t byte_len = len * sizeof(T);
        if (this->_buf == NULL) this->resize(std::max(SBUFSIZE, byte_len));

        size_t rsize = this->_size + byte_len;
        if (this->_alloc_size < rsize) {
            this->resize(rsize);
        }

        ::memcpy((void*)(this->_buf + this->_size), (void*)ptr, byte_len);
        this->_size += byte_len;
    }

    template<typename T>
    T& read(T& e)
    {
        if ((this->_index + sizeof(T)) > this->size()) throw std::out_of_range("ERROR: overflow buffer");
        ::memcpy((void*)&e, (void*)(this->_buf + this->_index), sizeof(T));
        this->_index += sizeof(T);
        return e;
    }

    std::string& read(std::string& rs)
    {
        if ((this->_index + rs.length() + 1) > this->size()) throw std::out_of_range("ERROR: overflow buffer");
        rs = this->_buf + this->_index;
        this->_index += rs.length() + 1;
        return rs;
    }

};


template<typename T>
inline bytestream& operator<<(bytestream& s, const T& e)
{
    s.append(e);
    return s;
}

template<typename T>
inline bytestream& operator>>(bytestream& s, T& e)
{
    e = s.read(e);
    return s;
}


#endif
