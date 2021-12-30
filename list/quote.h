
#ifndef LIST_QUOTE_
#define LIST_QUOTE_

#include "list.h"

namespace list {

struct quote : listbase {

   list lst;
   quote() noexcept {}

   quote( list _lst ) : lst{ _lst } {}

   bool equal_to( const list& lst ) const override
   {
      return lst. try_cast< quote > ( );
   }

   void print( std::ostream& out ) const {
      out << "'" << lst;
   }

   void prettyprint( std::ostream& out, indentation ind ) const
   {
      out << ind << "'\n";
   }

};

} 

#endif

