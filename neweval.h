#ifndef NEW_EVAL_H
#define NEW_EVAL_H

#include <map>

#include "list/list.h"

namespace neweval {

using storage = std::map< std::string, list::list >;

struct context {

  storage funcs;
  storage global_vars;
  storage local_vars;

  bool quit = false;

  context(){}

  context( storage a, storage b, storage c ): funcs{ a }, global_vars{ b }, local_vars{ c } {} 
  context( storage a, storage b ): funcs{ a }, global_vars{ b } {} 
};

list::list eval_primitives( list::list &prim ){
  if( auto cast = prim. try_cast< list::number >(); cast != nullptr ){
    return prim;
  }
  if( auto cast = prim. try_cast< list::integer >(); cast != nullptr ){
    return prim;
  }
  if( auto cast = prim. try_cast< list::string >(); cast != nullptr ){
    return prim;
  }

  return list::list( new list::nil() );
}

list::list get_atom_val( std::string atomname ){
  static std::map< std::string, list::list > values_map;

  if( values_map. find( atomname ) != values_map. end() ){
    return values_map[ atomname ];
  } else {
    return list::list( new list::nil() );
  }
}

bigint numeric_action( bigint &a, bigint &b, std::string op ){
  if( op == "+" ){
    return a + b;
  }
  if( op == "-" ){
    return a - b;
  }
  if( op == "*" ){
    return a * b;
  }
  if( op == "/" ){
    return a / b;
  }

  return bigint( 0 );
}

double numeric_action( double a, double b, std::string op ){
  if( op == "+" ){
    return a + b;
  }
  if( op == "-" ){
    return a - b;
  }
  if( op == "*" ){
    return a * b;
  }
  if( op == "/" ){
    return a / b;
  }

  return 0;
}

list::list eval( list::list &cur_list, context &ctx ) {

  if( auto cast = cur_list. try_cast< list::nil >(); cast != nullptr ){
    return cur_list;
  }
  if( auto cast = cur_list. try_cast< list::quote >(); cast != nullptr ){
    return cast -> lst;
  }
  auto prim_or_nil = eval_primitives( cur_list );
  if( auto cast = prim_or_nil. try_cast< list::nil >(); cast == nullptr ){
    return cur_list;
  }
  if( auto cast = cur_list. try_cast< list::atom >(); cast != nullptr ){
    return get_atom_val( cast -> getstring() );
  }

  list::cons cons = *( cur_list. try_cast< list::cons >() );

  auto command = cons. first;
  if( auto cast = command. try_cast< list::cons >(); cast != nullptr ){
    auto cur = cur_list;
    list::list res;
    std::vector< list::list > vec;
    while( cur. try_cast< list::nil >() == nullptr ){
      auto cur_cast = cur. try_cast< list::cons >();
      res = eval( cur_cast -> first, ctx );
      vec. push_back( res );
      cur = cur_cast -> rest;
    }

    return res;
  }
  if( auto cast = command. try_cast< list::atom >(); cast != nullptr ){
    auto target_list = cons. rest;
    auto command_name = cast -> getstring();
    if( command_name == "PROGN" ){
      list::list res;
      while( target_list. try_cast< list::nil >() == nullptr ){
        auto list_cast = target_list. try_cast< list::cons >();
        auto new_command = list_cast -> first;
        target_list = list_cast -> rest;
        res = eval( new_command, ctx );
      }
      return res;
    }
    if( command_name == "FIRST" || command_name == "CAR" ){
      auto to_get_first_from = target_list. try_cast< list::cons >() -> first;
      to_get_first_from = eval( to_get_first_from, ctx );
      auto try_cast = to_get_first_from. try_cast< list::cons >();
      if( try_cast != nullptr ){
        return try_cast -> first;
      } else {
        return list::list( new list::nil() );
      }
    }
    if( command_name == "REST" || command_name == "CDR" ){
      auto to_get_rest_from = target_list. try_cast< list::cons >() -> first;
      to_get_rest_from = eval( to_get_rest_from, ctx );
      auto try_cast = to_get_rest_from. try_cast< list::cons >();
      if( try_cast != nullptr ){
        return try_cast -> rest;
      } else {
        return list::list( new list::nil() );
      }
    }
    if( command_name == "LENGTH" ){
      size_t len = 0;
      auto list_cast = target_list. try_cast< list::cons >();
      target_list = eval( list_cast -> first, ctx );
      while( target_list. try_cast< list::nil >() == nullptr ){
        target_list = target_list. try_cast< list::cons >() -> rest;
        len ++;
      }
      return list::list( new list::integer( (int) len ) );
    }
    if( command_name == "DEFUN" ){
      auto list_cast = target_list. try_cast< list::cons >();
      auto funcname  = list_cast -> first; list_cast = list_cast -> rest. try_cast< list::cons >();
      auto arguments = list_cast -> first; list_cast = list_cast -> rest. try_cast< list::cons >();
      auto body      = list_cast -> first;
      auto funcname_str = funcname. try_cast< list::atom >() -> getstring();
      
      ctx. funcs[ funcname_str ] = list::list( new list::cons( arguments, body ) );
      std::cout << "DEBUG: " << body << '\n';
      std::cout << "DEBUG: " << ctx. funcs. size() << '\n';
      return funcname;
    }
    if( command_name == "IF" ){
      list::cons* temp;
      temp = target_list. try_cast< list::cons >();  auto cond         = eval( temp -> first, ctx );
      temp = temp -> rest. try_cast< list::cons >(); auto true_branch  = temp -> first;
      temp = temp -> rest. try_cast< list::cons >(); auto false_branch = temp -> first;
      if( cond. try_cast< list::nil >() == nullptr ){
        return eval( true_branch, ctx );
      } else {
        return eval( false_branch, ctx );
      }
    }
    if( command_name == "PRINT" ){
      while( target_list. try_cast< list::nil >() == nullptr ){
        auto cons_cast = target_list. try_cast< list::cons >();
        auto elem = cons_cast -> first;
        target_list = cons_cast -> rest;
        auto temp_res = eval( elem, ctx );

        if( auto if_cast = temp_res. try_cast< list::string >(); if_cast != nullptr ){
          std::cout << if_cast -> s;
        } else
        if( auto if_cast = temp_res. try_cast< list::integer >(); if_cast != nullptr ){
          std::cout << if_cast -> val;
        } else
        if( auto if_cast = temp_res. try_cast< list::number >(); if_cast != nullptr ){
          std::cout << if_cast -> val;
        } else
        if( auto if_cast = temp_res. try_cast< list::atom >(); if_cast != nullptr ){
          auto val = get_atom_val( if_cast -> getstring() );
          std::cout << val;
        } else {
          std::cout << temp_res;
        }
        std::cout << "\n";
      }

      return list::list( new list::nil() );
    }
    if( command_name == "LAMBDA" ){
      //
    }
    if( command_name == "+" ||
        command_name == "-" ||
        command_name == "*" ||
        command_name == "/" ){
      auto res = list::list( new list::integer( 0 ) );
      bool isfloat = false;
      bool isfirst = true;

      auto first_val = list::list( new list::nil() );
      while( target_list. try_cast< list::nil >() == nullptr ){
        auto cons_cast = target_list. try_cast< list::cons >();
        auto elem = cons_cast -> first;
        target_list = cons_cast -> rest;
        auto temp_res = eval( elem, ctx );
        if( isfirst ){
          isfirst = false;
          first_val = temp_res;
        }

        if( auto if_cast = temp_res. try_cast< list::integer >(); if_cast != nullptr ){

          if( isfloat ){
            auto res_cast = res.try_cast< list::number >();
            res_cast -> val = numeric_action( res_cast -> val, if_cast -> val.  approximation(), command_name );
          } else {
            auto res_cast = res.try_cast< list::integer >();
            res_cast -> val = numeric_action( res_cast -> val, if_cast -> val, command_name );
          }

        } else
        if( auto if_cast = temp_res. try_cast< list::number >(); if_cast != nullptr ){

          if( isfloat == false ){
            isfloat = true;
            auto res_cast = res.try_cast< list::integer >();
            auto temp_res = new list::number( res_cast -> val. approximation() );
            res = temp_res;
          }
          auto res_cast = res.try_cast< list::number >();
          res_cast -> val = numeric_action( res_cast -> val, if_cast -> val, command_name );

        } else
        if( auto if_cast = temp_res. try_cast< list::atom >(); if_cast != nullptr ){

          auto val = get_atom_val( if_cast -> getstring() );
          if( auto atom_num_cast = val. try_cast< list::number >(); atom_num_cast != nullptr ){
            auto res_cast = res.try_cast< list::number >();
            res_cast -> val = numeric_action( res_cast -> val, atom_num_cast -> val, command_name );
          } else
          if( auto atom_num_cast = val. try_cast< list::integer >(); atom_num_cast != nullptr ){
            auto res_cast = res.try_cast< list::integer >();
            res_cast -> val = numeric_action( res_cast -> val, atom_num_cast -> val, command_name );
          }
        }
      }

      if( command_name == "-" ){
        if( isfloat ){
          auto res_cast = res. try_cast< list::number >();
          if( auto try_cast = first_val. try_cast< list::integer >(); try_cast != nullptr ){
            res_cast -> val += try_cast -> val. approximation();
            res_cast -> val += try_cast -> val. approximation();
          } else 
          if( auto try_cast = first_val. try_cast< list::number >(); try_cast != nullptr ){
            res_cast -> val += try_cast -> val;
            res_cast -> val += try_cast -> val;
          }
        } else {
          auto res_cast = res. try_cast< list::integer >();
          if( auto try_cast = first_val. try_cast< list::integer >(); try_cast != nullptr ){
            res_cast -> val += try_cast -> val;
            res_cast -> val += try_cast -> val;
          }
        }
      }
      return res;
    }
    if( command_name == "=" ){
      list::list a, b;
      bool res = true;
      auto list_cast = target_list. try_cast< list::cons >();
      a = eval( list_cast -> first, ctx );
      target_list = list_cast -> rest;
      while( target_list. try_cast< list::nil >() == nullptr ){
        list_cast = target_list. try_cast< list::cons >();
        b = eval( list_cast -> first, ctx );
        if( !( a -> equal_to(b) ) ){ res = false; break; }
        a = b;
        target_list = list_cast -> rest;
      }
      if( res == true ){
        return list::list( new list::atom( "T" ) );
      } else {
        return list::list( new list::nil() );
      }
    }
    if( command_name == "/=" ){
      list::list a, b;
      bool res = true;
      auto list_cast = target_list. try_cast< list::cons >();
      std::vector< list::list > pool;
      a = eval( list_cast -> first, ctx );
      target_list = list_cast -> rest;
      pool. push_back( a );
      while( target_list. try_cast< list::nil >() == nullptr ){
        list_cast = target_list. try_cast< list::cons >();
        b = eval( list_cast -> first, ctx );
        for( auto t : pool ){ if( t -> equal_to( b ) ){ res = false; break; } }
        if( res == false ) break;
        pool. push_back( b );
        a = b;
        target_list = list_cast -> rest;
      }
      if( res == true ){
        return list::list( new list::atom( "T" ) );
      } else {
        return list::list( new list::nil() );
      }
    }
    if( ctx. funcs. find( command_name ) != ctx. funcs. end() ){
      auto funcdef = ctx. funcs[ command_name ];
      auto list_cast = funcdef. try_cast< list::cons >();
      auto args = list_cast -> first;
      auto body = list_cast -> rest;
      context new_ctx{ ctx. funcs, ctx. global_vars };
      auto l = args;
      auto r = target_list;
      storage new_local_vars;
      while( l. try_cast< list::nil >() == nullptr && r. try_cast< list::nil >() == nullptr ){
        auto l_list_cast = l. try_cast< list::cons >();
        auto sym = l_list_cast -> first. try_cast< list::atom >() -> getstring();
        auto r_list_cast = r. try_cast< list::cons >();
        auto val = eval( r_list_cast -> first, ctx );
        new_local_vars[ sym ] = val;
      }
      new_ctx. local_vars = new_local_vars;
      return eval( body, new_ctx );
    }
    if( ctx. local_vars. find( command_name ) != ctx. local_vars. end() ){
      return ctx. local_vars[ command_name ];
    }
    if( ctx. global_vars. find( command_name ) != ctx. global_vars. end() ){
      return ctx. global_vars[ command_name ];
    }
  }

  return list::list( new list::nil() );
}

} // namespace

#endif
