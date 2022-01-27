
#ifndef LIST_NUMBER_
#define LIST_NUMBER_

#include "list.h"

namespace list 
{

   struct number : listbase 
   {
      double val;

      number( ) : val( 0.0 ) { }
      number( double x ) : val(x) {}

      bool equal_to( const list& lst ) const override 
      {
         auto p = lst. try_cast< number > ( );
         return p && val == p -> val;
      }

      list copy( ){ return list( new number( val ) ); }
 
      void print( std::ostream& out ) const override 
         { out << val; }
      void prettyprint( std::ostream& out, indentation ind ) const override
         { out << ind << val << '\n'; } 
   };

} 

#endif

