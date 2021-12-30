#pragma once

#include <map>

#include "list/list.h"

namespace neweval {

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

list::list eval( list::list &cur_list ) {

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
    std::vector< list::list > vec;
    while( cur. try_cast< list::nil >() != nullptr ){
      auto cur_cast = cur_list. try_cast< list::cons >();
      auto res = eval( cur_cast -> first );
      vec. push_back( res );
      cur = cur_cast -> rest;
    }

    auto res = list::list( new list::nil() );
    size_t pos = vec. size();
    while( pos > 0 ){
      pos --;
      res = list::list( new list::cons( vec[ pos ], res ) );
    }

    return res;
  }
  if( auto cast = command. try_cast< list::atom >(); cast != nullptr ){
    auto target_list = cons. rest;
    auto command_name = cast -> getstring();
    if( command_name == "FIRST" || command_name == "CAR" ){
      auto to_get_first_from = target_list. try_cast< list::cons >() -> first;
      to_get_first_from = eval( to_get_first_from );
      auto try_cast = to_get_first_from. try_cast< list::cons >();
      if( try_cast != nullptr ){
        return try_cast -> first;
      } else {
        return list::list( new list::nil() );
      }
    }
    if( command_name == "REST" || command_name == "CDR" ){
      auto to_get_rest_from = target_list. try_cast< list::cons >() -> first;
      to_get_rest_from = eval( to_get_rest_from );
      auto try_cast = to_get_rest_from. try_cast< list::cons >();
      if( try_cast != nullptr ){
        return try_cast -> rest;
      } else {
        return list::list( new list::nil() );
      }
    }
    if( command_name == "PRINT" ){
      while( target_list. try_cast< list::nil >() == nullptr ){
        auto cons_cast = target_list. try_cast< list::cons >();
        auto elem = cons_cast -> first;
        target_list = cons_cast -> rest;
        auto temp_res = eval( elem );

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
        auto temp_res = eval( elem );
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
  }

  return list::list( new list::nil() );
}

} // namespace
