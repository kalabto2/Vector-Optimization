#define BOOST_TEST_MODULE practical1_test

#include <boost/test/included/unit_test.hpp>

#include "vector.h"

#include "X.h"

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      auto temp = v.data();

      epc::vector<X> v_copy(v);

      BOOST_TEST( v_copy.data() != v.data() );

      BOOST_TEST( v.data() == temp );
      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );

      BOOST_TEST( v_copy.size() == 3 );
      BOOST_TEST( v_copy[0] == 1 );
      BOOST_TEST( v_copy[1] == 2 );
      BOOST_TEST( v_copy[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_constructor_excpetion_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.push_back(1);

      X::set_copy_constructor_throw_n(1);
      X::set_copy_assignment_throw_n(1);

      bool propagated = false;

      try
      {
         epc::vector<X> v_copy(v);
      }
      catch (...)
      {
         propagated = true;
      }

      BOOST_TEST( propagated == true );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_assignment_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      auto temp = v.data();

      epc::vector<X> v_copy;
      v_copy.push_back(4);
      v_copy.push_back(5);

      v_copy = v;

      BOOST_TEST( v_copy.data() != v.data() );

      BOOST_TEST( v.data() == temp );
      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );

      BOOST_TEST( v_copy.size() == 3 );
      BOOST_TEST( v_copy[0] == 1 );
      BOOST_TEST( v_copy[1] == 2 );
      BOOST_TEST( v_copy[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(self_copy_assignment_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      v = v;

      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(copy_assignment_exception_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.push_back(1);

      X::set_copy_constructor_throw_n(1);
      X::set_copy_assignment_throw_n(1);

      bool propagated = false;

      try
      {
         epc::vector<X> v_copy;
         v_copy = v;
      }
      catch (...)
      {
         propagated = true;
      }

      BOOST_TEST( propagated == true );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(swap_content_test)
{
   X::reset();

   {
      epc::vector<X> va;
      va.push_back(1);
      va.push_back(2);

      epc::vector<X> vb;
      vb.push_back(3);
      vb.push_back(4);
      vb.push_back(5);

      va.swap(vb);

      BOOST_TEST( va.size() == 3 );
      BOOST_TEST( va[0] == 3 );
      BOOST_TEST( va[1] == 4 );
      BOOST_TEST( va[2] == 5 );
         
      BOOST_TEST( vb.size() == 2 );
      BOOST_TEST( vb[0] == 1 );
      BOOST_TEST( vb[1] == 2 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(swap_noexcept_test)
{
   X::reset();

   {
      epc::vector<X> va;
      va.push_back(1);
      va.push_back(2);

      epc::vector<X> vb;
      vb.push_back(3);
      vb.push_back(4);
      vb.push_back(5);

      auto constructed = X::constructed();

      X::set_default_constructor_throw_n(1);
      X::set_int_constructor_throw_n(1);
      X::set_copy_constructor_throw_n(1);
      X::set_copy_assignment_throw_n(1);

      bool problem = false;

      try
      {
         va.swap(vb);
      }
      catch (...)
      {
         problem = true;
      }

      BOOST_TEST( problem == false );

      BOOST_TEST( X::constructed() == constructed );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();
}

BOOST_AUTO_TEST_CASE(reserve_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(1);

      BOOST_TEST( v.capacity() == 1 );
      BOOST_TEST( v.size() == 0 );

      v.push_back(1);

      BOOST_TEST( v.capacity() == 1 );
      BOOST_TEST( v.size() == 1 );
      BOOST_TEST( v[0] == 1 );

      v.reserve(3);

      BOOST_TEST( v.capacity() == 3 );
      BOOST_TEST( v.size() == 1 );
      BOOST_TEST( v[0] == 1 );

      v.push_back(2);
      v.push_back(3);
      
      BOOST_TEST( v.capacity() == 3 );
      BOOST_TEST( v.size() == 3 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( v[2] == 3 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}

BOOST_AUTO_TEST_CASE(reserve_exception_test)
{
   X::reset();

   {
      epc::vector<X> v;

      X::set_default_constructor_throw_n(1);

      try
      {
         v.reserve(1);
      }
      catch(...)
      { }
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();

   X::reset();

   {
      epc::vector<X> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      X::set_copy_constructor_throw_n(2);
      X::set_copy_assignment_throw_n(2);

      bool propagated = false;

      auto capacity = v.capacity();

      try
      {
         v.reserve(7);
      }
      catch(...)
      {
         propagated = true;
      }

      BOOST_TEST( propagated == true );
      BOOST_TEST( v.capacity() == capacity );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();
}

BOOST_AUTO_TEST_CASE(push_back_exception_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.reserve(1);

      X::set_copy_constructor_throw_n(1);
      X::set_copy_assignment_throw_n(1);

      bool propagated = false;

      try
      {
         v.push_back(1);
      }
      catch (...)
      {
         propagated = true;
      }

      BOOST_TEST( propagated == true );
      BOOST_TEST( v.capacity() == 1 );
      BOOST_TEST( v.size() == 0 );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();

   X::reset();

   {
      epc::vector<X> v;
      v.reserve(3);
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      X::set_copy_constructor_throw_n(2);
      X::set_copy_assignment_throw_n(2);

      bool propagated = false;

      auto capacity = v.capacity();

      try
      {
         v.push_back(4);
      }
      catch(...)
      {
         propagated = true;
      }

      BOOST_TEST( propagated == true );
      BOOST_TEST( v.capacity() == capacity );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );

   X::reset_exceptions();
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
   X::reset();

   {
      epc::vector<X> v;
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);

      auto capacity = v.capacity();
      auto destructed = X::destructed();
      
      v.pop_back();

      BOOST_TEST( v.capacity() == capacity );
      BOOST_TEST( v.size() == 2 );
      BOOST_TEST( v[0] == 1 );
      BOOST_TEST( v[1] == 2 );
      BOOST_TEST( X::destructed() == destructed );
   }

   BOOST_TEST( X::constructed() == X::destructed() );
   BOOST_TEST( X::alive() == 0 );
}
