
#ifndef LIST_NIL_
#define LIST_NIL_

#include "list.h"

namespace list {

struct nil : listbase {

  nil() noexcept {}

   bool equal_to( const list& lst ) const override
   {
      return lst. try_cast< nil > ( );
   }

   void print( std::ostream& out ) const {
      out << "nil";
   }

   void prettyprint( std::ostream& out, indentation ind ) const
   {
      out << ind << "nil\n";
   }

   bool isnil( ) const override { return true; }

   list copy( ){ return list( new nil() ); }
};

} 

#endif

