
#include "../filereader.h"
#include "symbol.h" 
#include "tokenizing.h"
#include "parser.h"

void testtokenizer( filereader& read )
{

   symbol sym = tokenizing::readsymbol( read );
   while( sym. type != sym_EOF )
   {
      std::cout << sym << "\n";
      sym = tokenizing::readsymbol( read );
   }
   std::cout << "that's end of file\n";

}


int main( int argc, char* argv [] )
{

   varstore<double> vs;
   vs. assign( "e", 2.71828182845904523536 );
   vs. assign( "pi", 3.14159265358979323846264338327950288 ); 

   std::cout << vs << "\n";

   filereader read( &std::cin, "stdin" );
   // testtokenizer( read );

   std::vector< std::string > errorlog;

   parser prs( vs, errorlog, read );
 
   prs. debug = 0;  
   prs. parse( sym_Session );

#if 0
   parser( tt, vs, tkn_Session, 10 );

   if( tt. lookahead. front( ). type != tkn_Session )
      std::cout << "ended with an error\n";
#endif
}


