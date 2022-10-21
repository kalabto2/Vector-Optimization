#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <cstdlib>

namespace epc
{
   template <typename T>
   class vector
   {
   private:
       size_t t_capacity; // allocated space
       size_t t_size; // number of elements in allocated space
       T* t_data; // array
   public:
         vector() noexcept {
             t_capacity = 0;
             t_data = nullptr;
             t_size = 0;
         }

         vector(const vector& v) {
             T *tmp;
             tmp = static_cast<T*>(::operator new(sizeof(T) * v.t_capacity));

             int i = 0;
             try {
                 for (; i < v.t_size; i ++)
                     new (tmp + i) T(v[i]);
             } catch (...){
                 for (int j = 0; j < i; j ++)
                     tmp[j].T::~T();
                operator delete[] (tmp);
                throw;
             }

             t_data = tmp;
             t_capacity = v.t_capacity;
             t_size = v.t_size;
         }

         vector& operator=(const vector& v) {
             vector tmp(v);
             swap(tmp);
             return *this;
         }

         ~vector() {
             for (int i = 0; i < t_size; i ++)
                 t_data[i].T::~T();

             operator delete [] (t_data);
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
           if (t_size == t_capacity) { // reallocate array
                T * tmp = static_cast<T*>(::operator new(sizeof(T) * (t_capacity == 0 ? 1 : t_capacity * 2)));
                size_t i = 0;

               try {
                   for (; i < t_size; i ++)
                       new(tmp + i)T(t_data[i]);
               } catch (...) {
                   for (size_t j = 0; j < i; j ++)
                       tmp[i].T::~T();

                   operator delete [] (tmp);
                   throw;
               }

               for (int j = 0; j < t_size; j++)
                    t_data[j].T::~T();
               operator delete [] (t_data);

               t_data = tmp;
               t_capacity = t_capacity == 0 ? 1 : t_capacity * 2;
           }

           new (t_data + t_size) T(t);
           t_size ++;
       }

       void swap(vector& other) noexcept {
           std::swap(t_data, other.t_data);
           std::swap(t_size, other.t_size);
           std::swap(t_capacity, other.t_capacity);
       }

       size_t capacity() const {
           return t_capacity;
       }

       size_t size() const {
           return t_size;
       }

       void reserve(size_t s) {
           if (s > t_size) {
                T* tmp = static_cast<T*>(::operator new(sizeof(T) * s));
               size_t i = 0;

               try {
                   for (; i < t_size; i ++)
                       new (tmp + i) T(t_data[i]);
               } catch (...) {
                   for (int j = 0; j < i; j ++)
                       tmp[j].T::~T();

                   operator delete [] (tmp);
                   throw;
               }

               for (int j = 0; j < t_size; j ++)
                   t_data[j].T::~T();

               operator delete [] (t_data);

               t_data = tmp;
               t_capacity = s;
           }
       }

       void pop_back() {
             t_data[t_size - 1].T::~T();
             t_size --;
       }

       void clear() {
             for (int i = 0; i < t_size; i ++)
                 t_data[i].T::~T();
             t_size = 0;
       }
   };
}

#endif
