
#ifndef LIST_LIST_
#define LIST_LIST_

#include "../util/shared_ptr.h"
#include "../util/indentation.h"

namespace list 
{

   struct listbase;

   using list = util::shared_ptr< listbase >;

   struct listbase 
   {
      listbase() noexcept = default;
      virtual ~listbase( ) = default;

      virtual bool equal_to( const list& ) const = 0;
      virtual void print( std::ostream& out ) const {
         out << "list::list";
      }
      virtual void prettyprint( std::ostream& out, indentation ) const = 0;

      virtual bool isnil( ) const { return false; }
      virtual bool iscons( ) const { return false; }
      virtual list copy( ) = 0;
   };

   inline std::ostream& operator << ( std::ostream& out, const listbase& x )
   {
      x. print( out );
      return out;
   }

   list build( std::initializer_list< list > args );
} 

#include "string.h"
#include "integer.h"
#include "number.h" 
#include "atom.h"
#include "quote.h" 
#include "nil.h"
#include "cons.h"

#endif


