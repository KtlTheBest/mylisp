

#ifndef TOKENIZING_INCLUDED
#define TOKENIZING_INCLUDED    1

#include "../filereader.h"
#include "symbol.h"

namespace tokenizing 
{

   std::pair< symboltype, size_t > try_whitespace( filereader& read );
   std::pair< symboltype, size_t > try_comment( filereader& read ); 
   std::pair< symboltype, size_t > try_double( filereader& read );
   std::pair< symboltype, size_t > try_special( filereader& read );
   std::pair< symboltype, size_t > try_identifier( filereader& read );
      // We cannot reuse from Maphoon because the enumerations are different.

   symbol readsymbol( filereader& read );
      // Gets a token from somewhere and appends it to lookahead.

} 

#endif

