
#ifndef TOKENIZER_INCLUDED
#define TOKENIZER_INCLUDED    1

#include "../filereader.h"

#include "../lexing/classifier.h"

#include "symbol.h"

struct tokenizer
{
   filereader read;

   tokenizer( ) 
      : read( filereader( ))
   { }

   tokenizer( filereader&& read )
      : read( std::move( read ))
   { }

   symbol get( );

   void print( std::ostream& out ) const; 

   lexing::classifier<char,symboltype> getclassifier( );
      // Constructs the classifier that we are using.

   void test( );
      // Keep on reading and printing symbols until we reach EOF
      // or SEMICOLON.
}; 

inline std::ostream& operator << ( std::ostream& out, const tokenizer& tok )
{
   tok. print( out );
   return out;
}

#endif

