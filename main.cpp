#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "util/filereader.h"
#include "parser.h"
#include "neweval.h"
#include "symbol.h"

#include "list/list.h"

void print_help(){
  std::cout << "Usage:"
               "    $ lisp_parser filename.lsp\n";
}

int main(int argc, char* argv[]){
  if( argc == 2 && std::string( argv[1] ) == "help" ){
    print_help();
    return 1;
  }
  if( argc == 1 ){
    neweval::context ctx;
    while( true ){

      std::cout << ">>> ";
      std::string input;
      std::getline( std::cin, input );
          
      std::string filename{ "stdin" };
      std::stringstream ss{ input };
      filereader fr( &ss, filename );

      tokenizer tok( fr, filename );
      parser pr( fr, tok );
      auto res = pr. parse( sym_S_EXPR );

      auto ptr = res.get< list::list >();

      if( auto try_cast = ptr. try_cast< list::atom >(); try_cast != nullptr ){
        if( try_cast -> getstring( ) == "QUIT" ){
          return 0;
        }
      }

      auto evalres = neweval::eval( ptr, ctx );

      std::cout << evalres << '\n';
    }
  } else {
    std::string filename{ argv[1] };
    std::ifstream inputfile( filename );
    filereader fr( &inputfile, filename );
      
    tokenizer tok( fr, filename );
    parser pr( fr, tok );
    neweval::context ctx;
    while( fr. eof() == false ){
      auto res = pr. parse( sym_S_EXPR );
      auto ptr = res.get< list::list >();

      neweval::eval( ptr, ctx );
    }
  }
  return 0;
}
