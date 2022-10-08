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
//             t_capacity = 0;
//             t_data = nullptr;
//             t_size = 0;
             T *tmp;
             tmp = new T[v.t_capacity];
             try {
                 for (int i = 0; i < v.t_size; i ++) {
                     tmp[i] = v[i];
                 }
             } catch (...){
                 delete [] tmp;
                 throw;
             }
//             std::cout << "HERE" << std::endl;
//             if (t_capacity == 0) {
//                 delete t_data;
//             }
//             else {
//                 delete [] t_data;
//             }
//            delete [] t_data;
             t_data = tmp;
             t_capacity = v.t_capacity;
             t_size = v.t_size;
         }

         vector& operator=(const vector& v) {
             if (&v == this)
                 return *this;

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
//             std::cout << t_size << " " << t_capacity << std::endl;
//             std::cout << "[]=" << t_data[i] << std::endl;
             return t_data[i];
         }
         const T& operator[](size_t i) const {
//             std::cout << t_size << " " << t_capacity << std::endl;
//             std::cout << "[]=" << t_data[i] << std::endl;
             return t_data[i];
         }

         void push_back(const T& t) {
//             std::cout << "PUSHing to array: [";
//             for (int i = 0; i < t_size; i ++)
//                 std::cout << t_data[i] << ", ";
//             std::cout << "]" << std::endl;

             if (t_size == t_capacity) { // reallocate array
                 T* tmp = new T[t_capacity == 0 ? 1 : t_capacity * 2];
                 try {
                     for (size_t i = 0; i < t_size; i ++)
                         tmp[i] = t_data[i];
                 } catch (...) {
                     delete [] tmp;
                     throw;
                 }
                 delete [] t_data;
                 t_data = tmp;
                 t_capacity = t_capacity == 0 ? 1 : t_capacity * 2;
             }
             t_data[t_size] = t;
             t_size ++;

//             std::cout << "PUSHED to array: [";
//             for (int i = 0; i < t_size; i ++)
//                 std::cout << t_data[i] << ", ";
//             std::cout << "]" << std::endl;
         }

         void swap(vector& other) noexcept {
             T* s_data = t_data;
             size_t s_size = t_size;
             size_t s_capacity = t_capacity;

             t_data = other.t_data;
             t_size = other.t_size;
             t_capacity = other.t_capacity;

             other.t_data = s_data;
             other.t_size = s_size;
             other.t_capacity = s_capacity;
         }

         size_t capacity() const {
             return t_capacity;
         }
         size_t size() const {
             return t_size;
         }

         void reserve(size_t s) {
             if (s > t_size) {
                 T * tmp = new T[s];

                 try {
                     for (size_t i = 0; i < t_size; i ++)
                         tmp[i] = t_data[i];
                 } catch (...) {
                     delete [] tmp;
                     throw;
                 }
                 delete [] t_data;
                 t_data = tmp;
                 t_capacity = s;
             }
         }

         void pop_back() {
            if (t_size > 0)
                t_size --;
         }
   };
}

#endif
