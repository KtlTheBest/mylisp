#include <cctype>

#include "tokenizer.h"
#include "symbol.h"
#include "lexing/algorithms.h"
#include "lexing/minimization.h"

lexing::classifier< char, symboltype > tokenizer::buildclassifier(){
  using namespace lexing;

  classifier< char, symboltype > tcls( sym_ERROR );

  auto comment = just( ';' ) * ( every<char>(). without( '\n' ) ).star();

  auto alphabetic =   just( '+' )
                    | just( '-' ) 
                    | just( '*' )
                    | just( '/' )
                    | just( '@' )
                    | just( '$' )
                    | just( '%' )
                    | just( '^' )
                    | just( '&' )
                    | just( '_' )
                    | just( '=' )
                    | just( '<' ) 
                    | just( '>' )
                    | just( '~' )
                    | just( '.' );

  auto letter = range( 'a', 'z' ) | range( 'A', 'Z' );
  auto digit  = range( '0', '9' );
  auto id     = letter * ( letter | digit | just( '.' ) ). star();

  auto whitespace = just(' ') | just('\n') | just('\t') | just('\r');

  auto integer = just('0') | just('-'). optional() * range( '1', '9' ) * digit. star();
  auto floating_part = just('.') * digit.plus();
  auto floating_number = integer * floating_part;
  auto special_sym = just('.') | just(',') | just('\'') | just('`');

  auto strconst = just('"') * every<char>(). without('"'). star() * just('"');

  auto symbolpat = ( range( 'a', 'z' ) | range( 'A', 'Z' ) | alphabetic ). plus();

  tcls. insert( just('('), sym_LPAR );
  tcls. insert( just(')'), sym_RPAR );

  tcls. insert( comment, sym_COMMENT );
  tcls. insert( whitespace, sym_WHITESPACE );
  tcls. insert( floating_number, sym_FLOAT );
  tcls. insert( integer, sym_INT );
  tcls. insert( strconst, sym_STR );
  tcls. insert( symbolpat, sym_ID );
  tcls. insert( just( '\'' ), sym_QUOT );

  return tcls;
}

std::pair< symboltype, unsigned long > tokenizer::skip_whitespace(){
  if( fr. eof() ){
    return std::pair< symboltype, unsigned long >{ sym_EOF, 0 };
  }
  auto res = readandclassify( cls, fr );
  while( res. first == sym_COMMENT || res. first == sym_WHITESPACE ){
    fr. commit( res. second );
    if( fr. eof() ){
      return std::pair< symboltype, unsigned long >{ sym_EOF, 0 };
    }
    res = readandclassify( cls, fr );
  }
  return res;
}

symbol tokenizer::get_new_symbol(){
  location loc{ fr. line, fr. column };
  auto res = skip_whitespace();

  if( res. first == sym_INT ){
    std::string str;
    auto len = res. second;
    for( size_t i = 0; i < len; ++ i ){ str += fr. peek( i ); }

    bigint b( str );
    fr. commit( res. second );
    return symbol( res.first, loc, b );
  }

  if( res. first == sym_FLOAT ){
    std::string str;
    auto len = res. second;
    for( size_t i = 0; i < len; ++ i ){ str += fr. peek( i ); }

    double f = std::stod( str );
    fr. commit( res. second );
    return symbol( res. first, loc, f );
  }

  if( res. first == sym_STR ){
    std::string str;
    auto len = res. second - 1;
    for( size_t i = 1; i < len; ++ i ){ str += fr. peek( i ); }

    fr. commit( res. second );
    return symbol( res. first, loc, str );
  }

  if( res. first == sym_ID ){
    std::string str;
    auto len = res. second;
    for( size_t i = 0; i < len; ++ i ){ str += toupper( fr. peek( i ) ); }

    fr. commit( res. second );
    return symbol( res. first, loc, str );
  }

  fr. commit( res. second );
  return symbol( res. first, loc );
}

symbol tokenizer::read_symbol(){
  if( cur_symbol. type != sym_EOF ){
    cur_symbol = get_new_symbol();
  }
  return cur_symbol;
}

void tokenizer::commit_symbol(){
  if( cur_symbol. type != sym_EOF ) 
    cur_symbol = symbol( sym_EMPTY, {} );
}
