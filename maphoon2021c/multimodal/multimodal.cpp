#include <iostream>
#include <fstream>
#include "../filereader.h"
#include "tokenizer.h"
#include "parser.h"

#include "form.h"
#include "../calculator/varstore.h"

#include "../lexing/algorithms.h"

#include <functional>


int main( int argc, char* argv[] )
{
   varstore< form > vs;

   tokenizer tok( filereader( &std::cin, "stdin") );
   std::cout << tok << "\n";

   parser prs( tok, vs );

   prs. debug = 2;
   auto res = prs. parse( sym_Session );

   std::cout << "parser returned " << res << "\n";
}


