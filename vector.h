#ifndef EPC_VECTOR_H
#define EPC_VECTOR_H

#include <cstdlib>

namespace epc
{
    template <typename T>
    class vector
    {
    private:
        size_t t_capacity;
        size_t t_size;
        T* t_data;
    public:
        vector() noexcept {
            t_capacity = 0;
            t_data = nullptr;
            t_size = 0;
        }

        vector(const vector& v) {
            t_capacity = v.t_capacity;
            t_data = new T[t_capacity];
            t_size = v.t_size;
            for (int i = 0; i < v.t_size; i ++) {
                t_data[i] = v[i];
            }
        }
        vector& operator=(const vector& v) {
            delete [] t_data;

            t_capacity = v.t_capacity;
            t_data = new T[t_capacity];
            t_size = v.t_size;
            for (int i = 0; i < v.t_size; i ++) {
                t_data[i] = v[i];
            }

            return *this;
        }

        ~vector() {
            delete [] t_data;
        }

        T* data() {
            return t_data;
        }
        const T* data() const {
            return t_data;
        }

        T& operator[](size_t i) {
            return t_data[i];
        }
        const T& operator[](size_t i) const {
            return t_data[i];
        }

        void push_back(const T& t) {
            if (t_size == t_capacity) {
                t_capacity = t_capacity == 0 ? 1 : t_capacity * 2;
                T* tmp = new T[t_capacity];
                for (size_t i = 0; i < t_size; i ++)
                    tmp[i] = t_data[i];
                delete [] t_data;
                t_data = tmp;
            }
            t_data[t_size ++] = t;
        }

        size_t capacity() const {
            return t_capacity;
        }
        size_t size() const {
            return t_size;
        }
    };
}

#endif
