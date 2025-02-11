#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>

namespace lab_13 {
    const int BYTE_SIZE = 8;
class proxy{
    public:
        proxy(uint8_t& byte, uint8_t mask) : _byte(byte), _mask(mask) {}
        operator bool() const{
            return _byte & _mask;
        }
        proxy& operator=(bool val){
            if (val){
                _byte |= _mask;
            }
            else{
                _byte &= ~(_mask);
            }
            return *this;
        }
        proxy& operator=(proxy& p){
            if (p == *this){
                return *this;
            }
            if (p){
                _byte |= _mask;
            }
            else{
                _byte &= ~(_mask);
            }
            return *this;
        }
    private:
       uint8_t& _byte;
       uint8_t _mask;
    };
template<typename T, std::size_t N>
class my_array {
public:
    T& at(std::size_t index){
        if (index < 0 || index > N - 1){
            throw std::out_of_range("Index is out of range");
        }
        return _data[index];
    }
    const T& at(std::size_t index) const {
        if (index < 0 || index > N - 1){
            throw std::out_of_range("Index is out of range");
        }
        return _data[index];
    }

    T& operator[](std::size_t index){
        return _data[index];
    }
    const T& operator[](std::size_t index) const {
        return _data[index];
    }

    bool empty() const{
        return N == 0;
    }
    size_t size() const{
        return N;
    }

    void fill(T val){
        for (size_t i = 0; i < N; ++i){
            _data[i] = val;
        }
    }
private:
    T _data[N];

};

template<std::size_t N>
class my_array<bool, N>{
public:
    proxy at(std::size_t index){
        if (index < 0 || index > N - 1){
            throw std::out_of_range("Index is out of range");
        }
        return proxy(_data[index / BYTE_SIZE], msk(index));
    }

    const bool at(std::size_t index) const {
        if (index < 0 || index > N - 1){
            throw std::out_of_range("Index is out of range");
        }
        return _data[index / BYTE_SIZE ] & msk(index);
    }

    proxy operator[](std::size_t index){
        return proxy(_data[index / BYTE_SIZE], msk(index));
    }

    const bool operator[](std::size_t index) const {
        return _data[index / BYTE_SIZE] & msk(index);
    }

    void fill(bool val){
        for (size_t i = 0; i < (N + BYTE_SIZE - 1) / BYTE_SIZE; ++i){
            _data[i] = val ? -1 : 0;
        }
    }
    bool empty() const{
        return N == 0;
    }
    size_t size() const{
        return N;
    }
    
private:
    uint8_t _data[(N + BYTE_SIZE - 1) / BYTE_SIZE];
    uint8_t msk(size_t index) const {
        return (1 << (index % BYTE_SIZE));
    }
};

}  // namespace lab_13

#endif  // MY_ARRAY_H_
