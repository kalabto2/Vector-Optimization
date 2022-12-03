#ifndef EPC_VECTOR
#define EPC_VECTOR

#include <cstdlib>

namespace epc
{
   template <typename T, size_t N>
   class vector
   {
      private:
           size_t t_capacity; // allocated space
           size_t t_size; // number of elements in allocated space
           T *t_data; // array
           alignas(T) std::byte t_buffer[sizeof(T) * N]; // static buffer

      public:
       vector() noexcept {
           t_capacity = N;
            t_data = reinterpret_cast<T*>(t_buffer);
           t_size = 0;
       }

       vector(const vector &v) {
           T *tmp;
           if (v.t_capacity <= N)
               tmp = reinterpret_cast<T*>(t_buffer);
           tmp = static_cast<T *>(::operator new(sizeof(T) * v.t_capacity));

           int i = 0;
           try {
               for ( ; i < v.t_size; i++ )
                   new(tmp + i) T(v[i]);
           } catch (...) {
               for ( int j = 0; j < i; j++ )
                   tmp[j].T::~T();
               if (v.t_capacity > N)
                    operator delete[](tmp);
               throw;
           }

           t_data = tmp;
           t_capacity = v.t_capacity;
           t_size = v.t_size;
       }

       vector &operator=(const vector &v) {
           vector tmp(v);
           swap(tmp);
           return *this;
       }

       vector(vector&& v) {
           t_size = std::move(v.t_size);
           t_capacity = std::move(v.t_capacity);
           t_data = std::move(v.t_data);

           if (this->t_capacity <= N) {
               for (int i = 0; i < N; i ++) {
                   t_buffer[i] = std::move(v.t_buffer[i]);
               }
           }

           v.t_size = 0;
           v.t_capacity = N;
           v.t_data = nullptr;
       } // todo move source vector to target vector

       vector& operator=(vector&& v) {
           for ( int i = 0; i < t_size; i++ )
               t_data[i].T::~T();

           if (t_size > N)
               operator delete[](t_data);

           t_size = std::move(v.t_size);
           t_capacity = std::move(v.t_capacity);
           t_data = std::move(v.t_data);

           if (this->t_capacity <= N) {
               for (int i = 0; i < N; i ++) {
                   t_buffer[i] = std::move(v.t_buffer[i]);
               }
           }


           v.t_size = 0;
           v.t_capacity = N;
           v.t_data = nullptr;
       } // todo move source vector to target vector

       ~vector() {
           for ( int i = 0; i < t_size; i++ )
               t_data[i].T::~T();

           if (t_size > N)
                operator delete[](t_data);
       }

       T *data() {
           return t_data;
       }

       const T *data() const {
           return t_data;
       }

       T &operator[](size_t i) {
           return t_data[i];
       }

       const T &operator[](size_t i) const {
           return t_data[i];
       }

       size_t capacity() const {
           return t_capacity;
       }

       size_t size() const {
           return t_size;
       }

       void reserve(size_t s) { // todo move
           if (s > t_size) {
               T *tmp = static_cast<T *>(::operator new(sizeof(T) * s));
               size_t i = 0;

               try {
                   for ( ; i < t_size; i++ )
//                        new(tmp + i) T(std::forward<T>(t_data[i]));
//                       tmp[i] = std::move(t_data[i]);
//                       new(tmp + i) T(t_data[i]);
                       new(tmp + i) T(std::move(t_data[i])); // todo what to do here?
//                        new(tmp + i) T(static_cast<T&&>(t_data[i]));
               } catch (...) {
                   for ( int j = 0; j < i; j++ )
                       tmp[j].T::~T();

                   operator delete[](tmp);
                   throw;
               }

               for ( int j = 0; j < t_size; j++ )
                   t_data[j].T::~T();

//               operator delete[](t_data);
                // free memory only from dynamic allocation
               if (t_size > N)
                    operator delete[](t_data);

               t_data = tmp;
               t_capacity = s;
           }
       }

       void push_back(const T &t) { // todo really done? I didn't do anything
           if (t_size == t_capacity) { // reallocate array
               reserve((t_capacity == 0 ? 1 : t_capacity * 2));
//               T *tmp = static_cast<T *>(::operator new(sizeof(T) * (t_capacity == 0 ? 1 : t_capacity * 2)));
//               size_t i = 0;
//
//               try {
//                   // copy new elements
//                   for ( ; i < t_size; i++ )
//                       new(tmp + i)T(t_data[i]);
//               } catch (...) {
//                   for ( size_t j = 0; j < i; j++ )
//                       tmp[i].T::~T();
//
//                   operator delete[](tmp);
//                   throw;
//               }
//
//               // destroy all elements (buffer + dynamic allocation)
//               for ( int j = 0; j < t_size; j++ )
//                   t_data[j].T::~T();
//
//               // free memory only from dynamic allocation
//               if (t_size > N)
//                    operator delete[](t_data);
//
//               t_data = tmp;
//               t_capacity = t_capacity == 0 ? 1 : t_capacity * 2;
           }

           new(t_data + t_size) T(t);
           t_size++;
       }

       void push_back(T&& t) {
           if (t_size == t_capacity) { // reallocate array
               reserve((t_capacity == 0 ? 1 : t_capacity * 2));
//               T *tmp = static_cast<T *>(::operator new(sizeof(T) * (t_capacity == 0 ? 1 : t_capacity * 2)));
//               size_t i = 0;
//
//               try {
//                   for ( ; i < t_size; i++ )
//                       new(tmp + i)T(t_data[i]);
//               } catch (...) {
//                   for ( size_t j = 0; j < i; j++ )
//                       tmp[i].T::~T();
//
//                   operator delete[](tmp);
//                   throw;
//               }
//
//               for ( int j = 0; j < t_size; j++ )
//                   t_data[j].T::~T();
//               if (t_size > N)
//                   operator delete[](t_data);
//
//               t_data = tmp;
//               t_capacity = t_capacity == 0 ? 1 : t_capacity * 2;
           }

           new(t_data + t_size) T(std::move(t));
           t_size++;
       } // todo really done??

       template <typename... Ts>
         void emplace_back(Ts&&... ts) {
           if (t_size == t_capacity) { // reallocate array
               reserve((t_capacity == 0 ? 1 : t_capacity * 2));
//               T *tmp = static_cast<T *>(::operator new(sizeof(T) * (t_capacity == 0 ? 1 : t_capacity * 2)));
//               size_t i = 0;
//
//               try {
//                   for ( ; i < t_size; i++ )
//                       new(tmp + i)T(t_data[i]);
//               } catch (...) {
//                   for ( size_t j = 0; j < i; j++ )
//                       tmp[i].T::~T();
//
//                   operator delete[](tmp);
//                   throw;
//               }
//
//               for ( int j = 0; j < t_size; j++ )
//                   t_data[j].T::~T();
//               if (t_size > N)
//                   operator delete[](t_data);
//
//               t_data = tmp;
//               t_capacity = t_capacity == 0 ? 1 : t_capacity * 2;
           }

           // perfect forwarding used for initialization
           new (t_data + t_size) T(std::forward<Ts>(ts)...);
           t_size ++;
       } // todo

       void pop_back() {
           t_data[t_size - 1].T::~T();
           t_size--;
       }

       void clear() {
           for ( int i = 0; i < t_size; i++ )
               t_data[i].T::~T();
           t_size = 0;
       }

       void swap(vector &other) {
           if (other.t_capacity > N && t_capacity > N)
               std::swap(t_data, other.t_data);
           else if (other.t_capacity <= N && t_capacity <= N) {
               for (int i = 0; i < std::min(other.t_size, t_size); i++){
                   std::swap(reinterpret_cast<T*>(t_buffer)[i], reinterpret_cast<T*>(other.t_buffer)[i]);
               }
               for (int i = std::min(other.t_size, t_size); i < other.t_size; i++) {
                   new(reinterpret_cast<T*>(t_buffer) + i)T(reinterpret_cast<T*>(other.t_buffer)[i]);
                   reinterpret_cast<T*>(other.t_buffer)[i].T::~T();
               }
               for (int i = std::min(other.t_size, t_size); i < t_size; i++) {
                   new(reinterpret_cast<T*>(other.t_buffer) + i)T(reinterpret_cast<T*>(t_buffer)[i]);
                   reinterpret_cast<T*>(t_buffer)[i].T::~T();
               }
           } else if (other.t_capacity > N && t_capacity <= N) {
               // copy this buffer to other buffer
               for ( int j = 0; j < t_size; j++ )
                   new (reinterpret_cast<T*>(other.t_buffer) + j) T(t_data[j]);

               // destroy this buffer
               for ( int j = 0; j < t_size; j++ )
                   t_data[j].T::~T();

               // link other data to this data
               t_data = other.t_data;

               //link other data to its buffer
               other.t_data = reinterpret_cast<T*>(other.t_buffer);
           } else {
                // copy other buffer to this buffer
               for ( int j = 0; j < other.t_size; j++ )
                   new (reinterpret_cast<T*>(t_buffer) + j) T(other.t_data[j]);

               // destroy other buffer
               for ( int j = 0; j < other.t_size; j++ )
                   other.t_data[j].T::~T();

               // link this data to other data(array)
               other.t_data = t_data;

               //link this data to its buffer
               t_data = reinterpret_cast<T*>(t_buffer);
           }

           std::swap(t_size, other.t_size);
           std::swap(t_capacity, other.t_capacity);
       }
   };
}

#endif
