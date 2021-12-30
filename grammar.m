%startsymbol S_EXPR EOF

%infotype{ location }

%symbol{} EOF ERROR WHITESPACE COMMENT EMPTY
%symbol{} LPAR RPAR QUOT
%symbol{ std::string } ID STR
%symbol{ bigint }      INT
%symbol{ double }      FLOAT

%symbol{ list::list } ATOM LIST
%symbol{ list::list } S_EXPR
%symbol{ list::list } LIST_REST LIST_INNER

%symbolcode_h { #include "list/list.h" }
%symbolcode_h { #include "util/filereader.h" }
%symbolcode_h { #include "util/shared_ptr.h" }
%symbolcode_h { #include <vector> }
%symbolcode_h { #include <memory> }

%parameter { filereader } r
%parameter { tokenizer } tok

%symbolcode_h {
struct location{
  long unsigned int line;
  long unsigned int column;

  location() {}
  location( long unsigned int line,
            long unsigned int column )
            : line( line ),
              column( column )
  { }
};
}

%symbolcode_cpp{

namespace {

  std::ostream& operator<< ( std::ostream& out, const location& loc ){
    out << "at position " << loc. line << "/" << loc. column;
    return out;
  }

  std::ostream& operator<< ( std::ostream& out, const std::vector< list::list > vec ){
    out << "[";
    for( auto x : vec ){ x -> print( out ); }
    out << "]";
    return out;
  }
}

}

%parsercode_h { #include "tokenizer.h" }
%parsercode_h { #include "list/list.h" }
%parsercode_h { #include <algorithm> }

%source { tok.read_symbol(); }

%rules
ATOM => ID:id   { return list::list( new list::atom( id ) ); }
      | STR:s   { return list::list( new list::string( s ) ); }
      | FLOAT:f { return list::list( new list::number( f ) ); }
      | INT:i   { return list::list( new list::integer( i ) ); }
      ;


S_EXPR => ATOM:atom { return atom; }
        | LIST:lst  { return lst; }
        | QUOT S_EXPR:s { 
          return list::list( new list::quote( s ) ); }
        ;

LIST_REST => { return list::list( new list::nil() ); }
           | S_EXPR : s_expr LIST_REST:lst 
           {
             return list::list( new list::cons( s_expr, lst ) ) ;
           }
           ;

LIST => LPAR LIST_INNER: inner RPAR
      {
        return inner;
      }
      ;

LIST_INNER => { return list::list( new list::nil() ); }
            | S_EXPR:s_expr LIST_REST: lst
            {
                return list::list( new list::cons( s_expr, lst ) );
            }
            ;
