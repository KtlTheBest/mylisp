
#ifndef LIST_INTEGER_
#define LIST_INTEGER_

#include "list.h"

#include "../util/bigint.h" 

namespace list {

struct integer : listbase {
   bigint val;


   // Too many of those:

   integer( ) = default;

   integer( bigint x ) 
      : val(x) 
   { }

   integer( int x ) 
      : val(x) 
   { }

   integer( long int x ) 
      : val(x)
   { }

   integer( const char* c ) 
      : val(c)
   { }

   integer( std::string_view s ) 
      : val( std::string( s ) )
   { }

   integer( const std::string& s )
      : val(s)
   { }

   bool equal_to( const list& lst ) const override
   {
      auto p = lst. try_cast< integer > ( );
      return p && val == p -> val;
   }

   void print( std::ostream& out ) const override
      { out << val; } 

   void prettyprint( std::ostream& out, indentation ind ) const override 
      { out << ind << val << '\n'; } 

   };

}

#endif


