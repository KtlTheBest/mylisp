
// Code written by Hans de Nivelle, February 2021.
// See the licence that is included with the code. 

#include <algorithm>
#include <sstream>

#include "parsercodebuilder.h" 
#include "errors.h"
#include "tablecodebuilder.h"


void parsercodebuilder::reduction::print( std::ostream& out ) const 
{
   out << "reduction";
   for( auto p = parameters. begin( ); p != parameters. end( ); ++ p ) 
   {
      if( p != parameters. begin( )) 
         out << ", ";
      else
         out << "( ";
      out << ( p -> first ) << " : " << ( p -> second );
   }
   
   if( parameters. size( ))
      out << " )"; 
   out << "\n";
   if( !cond. empty( )) 
      out << "? " << cond << "\n";
   if( !body. empty( )) 
      out << body << "\n";
}


namespace
{
   // A simplified version of filereader.

   void readchar( std::istream& idee, long unsigned int line, std::string& s ) 
   {
      s. push_back( idee. get( )); 
      if( !idee.good( ))  
         throw ideeproblem( "could not read", line );
   }

   void setideeline( std::ostream& out, long unsigned int line )
   {
      out << "#line " << (line+1) << " \"idee.x\"\n";
   }

}


void 
parsercodebuilder::printcode( const symbolcodebuilder& bld_sym,
                              const parsetable& pt, 
                              std::vector< conflict > & conflicts, 
                              std::istream& idee,
                              std::ostream& cpp, std::ostream& hh ) const
{
   std::ostream* dest = nullptr;
   long unsigned int line = 0;      // Line in idee

   while( true )
   {
      std::string inp; 
      readchar( idee, line, inp );  // Read and append one character. 

      if( inp. back( ) == '$' ) 
      {
         readchar( idee, line, inp );  
         if( inp. back( ) == '$' ) 
         {
            readchar( idee, line, inp );
            while( isdigit( inp. back( )) || isalpha( inp. back( )) || 
                   inp. back( ) == '_' )
            {
               readchar( idee, line, inp );
            }

            if( inp. size( ) < 4 || inp. back( ) != '$' ) 
               throw ideeproblem( "ill-formed $-insertion", line );

            readchar( idee, line, inp );
            if( inp. back( ) != '$' )
               throw ideeproblem( "second $ expected", line );
         
            // When inp has been recognized and processed, it 
            // should be cleared.
     
            if( inp == "$$h$$" )
            {
               dest = &hh;
               inp. clear( ); 
            } 

            if( inp == "$$cpp$$" )
            {
               dest = &cpp;
               inp. clear( );
            }
 
            if( inp == "$$nowhere$$" )
            {
               dest = nullptr;
               inp. clear( );
            }
    
            if( inp == "$$includeguard$$" )
            {
               if( dest )
                  *dest << space. includeguard( "parser" ); 
               inp. clear( ); 
            } 
         
            if( inp == "$$parsercode_h$$" )
            {
               if( dest )
               {
                  code_h. printascode( *dest ); 
                  setideeline( *dest, line );
               }
               inp. clear( );  
            }

            if( inp == "$$parsercode_cpp$$" )
            {
               if( dest )
               {
                  code_cpp. printascode( *dest );
                  setideeline( *dest, line ); 
               }
               inp. clear( ); 
            }

            if( inp == "$$parameterfields$$" )
            {
               if( dest )
                  printparameterfields( *dest ); 
               inp. clear( ); 
            }

            if( inp == "$$constructor$$" )
            {
               if( dest )
                  printconstructor( *dest );
               inp. clear( );
            }

            if( inp == "$$parserspace$$" ) 
            {
               if( dest )
                  space. printasprefix( *dest ); 
               inp. clear( );  
            }

            if( inp == "$$symbolspace$$" )
            {
               if( dest )
                  bld_sym. space. printasprefix( *dest );
               inp. clear( );
            }

            if( inp == "$$source$$" )
            {
               if( dest )
                  source. printascode( *dest );
               inp. clear( );
            }

            if( inp == "$$actiondeclarations$$" )
            {
               if( dest )
                  printactiondeclarations( bld_sym, *dest );
               inp. clear( ); 
            }

            if( inp == "$$actiondefinitions$$" )
            {
               if( dest )
                  printactiondefinitions( bld_sym, *dest );
               inp. clear( );
            }

            if( inp == "$$symbolhasinfo$$" )
            {
               // print true if symbol has an infotype:

               if( dest )
               {
                  if( bld_sym. infotype. isvoid( ))
                     *dest << "false";
                  else
                     *dest << "true";
               }
               inp. clear( );
            }

            if( inp == "$$usererror$$" )
            {
               // print true if user defines error:

               if( dest )
               {
                  if( usererror )
                     *dest << "true";
                  else
                     *dest << "false";
               } 
               inp. clear( );
            }

            if( inp == "$$maintables$$" )
            {
               if( dest )
                  printmaintables( pt, bld_sym. space, conflicts, *dest );
               inp. clear( );
            }

            if( inp == "$$reductioncases$$" )
            {
               if( dest )
                  printreductioncases( bld_sym, *dest );
               inp. clear( );
            }
 
            if( inp == "$$end$$" )
               return;

            if( !inp. empty( ))
            { 
               throw ideeproblem(  
                         std::string( "unknown insertion: " ) + inp, line ); 
            }

            
         }
      }

      for( auto c : inp )
      {
         if( c == '\n' )
            ++ line; 

         if( dest )
            dest -> put(c);
      } 
   }

}


std::unordered_map< std::string, std::string >
parsercodebuilder::createreplacement( size_t nr, 
                         const symbolcodebuilder& bld_sym ) const
{
   std::unordered_map< std::string, std::string > res;
   for( const auto& par : reductions[nr]. parameters )
   {
      std::ostringstream expr; 
         // Expression by which par. left will be replaced.

      
      expr << "(topsymbol(";
      expr << grrr. rules[ nr ]. rhs. size( ) - par. second; 
      expr << ").get<";
      symbol s = grrr. rules[nr]. rhs[ par. second ];
      bld_sym. attributes. at(s). printascode( expr, cpp::type::value ); 
      expr << ">())"; 

      res. insert( std::pair( par. first, expr. str( )) );
   }

   return res; 
}


void parsercodebuilder::printparameterfields( std::ostream& out ) const
{
   for( const auto& par : parameters )
   {
      out << "   ";  
      par. second. printascode( out, cpp::type::ref );
      out << " ";
      par. first. print( out );
      out << ";\n";
   }
}

void parsercodebuilder::printconstructor( std::ostream& out ) const
{
   out << "   parser("; 
   bool first = true; 
   for( const auto& par : parameters ) 
   {
      if( first ) 
         out << " "; 
      else
         out << ",\n           ";

      par. second. printascode( out, cpp::type::ref );
      out << " ";
      par. first. print( out );
      first = false; 
   }
   out << " )";

   first = true;
   for( const auto& par : parameters )
   {
      if( first )
         out << "\n      : ";
      else
         out << ",\n        ";
      par. first. print( out ); 
      out << "( "; 
      par. first. print( out );
      out << " )";
      first = false; 
   }
  
   out << "\n   { }\n";
}


void parsercodebuilder::printactiondeclarations( 
         const symbolcodebuilder& bld_sym, std::ostream& out ) const
{
   if( grrr. nrrules( ) != reductions. size( ))
      throw std::logic_error( "sizes must be equal" );

   // We look for the first rule that has a condition or reduction code.

   size_t start = 0;
   while( start != grrr. nrrules( ) && reductions[ start ]. empty( ) )
      ++ start;

   if( start == grrr. nrrules( ))
      return; 

   out << "   // Declarations of reduction functions and their conditions:\n";
   out << "   // They have no arguments because they use the stack.\n\n";

   for( size_t i = start; i != grrr. nrrules( ); ++ i )
   {
      if( !reductions[i]. cond. empty( ))
      {
         out << "   short cond" << i << "( ) const;\n";
      }

      if( !reductions[i]. body. empty( ))
      {
         cpp::type tp = bld_sym. attributes. at( grrr. rules[i]. lhs ); 
         out << "   ";
         tp. printascode( out, cpp::type::value );
         out << " body" << i << "( );\n";
      }
   }
}

void parsercodebuilder::printactiondefinitions(
         const symbolcodebuilder& bld_sym, std::ostream& out ) const
{
   if( grrr. nrrules( ) != reductions. size( ))
      throw std::logic_error( "sizes must be equal" );

   // We look for the first rule that has a condition or reduction code.

   size_t start = 0;
   while( start != grrr. nrrules( ) && reductions[ start ]. empty( ) )
      ++ start;

   if( start == grrr. nrrules( ))
      return;

   out << "\n";
   out << "// Definitions of the reduction functions:\n";
   out << "\n"; 

   for( size_t i = start; i != grrr. nrrules( ); ++ i )
   {
      if( !reductions[i]. empty( ))
      {
         auto repl = createreplacement( i, bld_sym ); 
         if( !reductions[i]. cond. empty( ))
         {
            out << "short ";
            space. printasprefix( out ); 
            out << "parser::cond" << i << "( ) const\n";
            out << "{\n";
            reductions[i]. cond. printascode( out, repl ); 
            out << "}\n\n";
         }

         if( !reductions[i]. body. empty( ))
         {
            cpp::type tp = bld_sym. attributes. at( grrr. rules[i]. lhs );
            tp. printascode( out, cpp::type::value );
            out << ' ';
            space. printasprefix( out );
            out << "parser::body" << i << "( )\n";
            out << "{\n";
            reductions[i]. body. printascode( out, repl ); 
            out << "}\n\n";
         }
      }
   }
}



size_t 
parsercodebuilder::findinredsequences( const reductionsequence& seq ) const
{
   for( size_t nr = 0; nr != redsequences. size( ); ++ nr ) 
   {
      for( const rule* r : seq )
      {
         if( redsequences[nr]. count( r -> lhs ) == 0 )
            goto failed;
      }
      return nr;
   failed:
      ;
   }
   return redsequences. size( ); 
}

bool parsercodebuilder::containsrepeatedlhs( const reductionsequence& seq )
{
   if( seq. size( ) < 2 ) return false;

   for( size_t i = 0; i + 1 != seq. size( ); ++ i )
   {
      if( seq[i] -> lhs == seq[i+1] -> lhs ) 
         return true;
   }
   return false;
}

std::vector< size_t > 
parsercodebuilder::getthenumbers( const reductionsequence& seq ) 
{
   std::vector< size_t > res;
   for( auto r : seq )
      res. push_back( r -> nr ); 
   return res; 
}



void 
parsercodebuilder::printmaintables( const parsetable& pt, 
                                    const cpp::nspace& symbolspace, 
                                    std::vector< conflict > & conflicts, 
                                    std::ostream& out ) const
{
   tablecodebuilder bld_code; 
   for( const auto& start : grrr. startsymbols )
   {
      symbol sym = start. first; 
      size_t state = pt. initialstates. at( sym ); 

      bld_code. startsymbols. insert( { sym, { state, start. second }} );
   }

   for( size_t ss = 0; ss != pt. nrstates( ); ++ ss )
   {
      std::cout << "state " << ss << "\n"; 
      const parsetable::state& st = pt. states[ss];

      symbolset errors; 
         // symbols for which we could not resolve a conflict.
         // They will be put in error message. 
 
      symbolset shiftred; 
         // Symbols for which there are both a shift and a reduction:

      for( const auto& p : st. reductions )
      {
         if( st. shifts. count( p. first ))
            shiftred. insert( p. first );
      }

      if( st. reductions. size( ))
      {
         if( usedefaults && shiftred. size( ) == 0 && 
             st. itemset. nrreductions( ) == 1 )
         {
            const auto& s = st. reductions. begin( ) -> second; 
            size_t nr = (*s.begin( )) -> nr; 

            std::cout << "default rule = " << nr << "\n";
            if( st. shifts. size( ) == 0 )
            {
               // The state consists of a single reduction without shifts: 

               bld_code. reductioninfo. push_back( { 'T', nr } );  
            }
            else
               bld_code. reductioninfo. push_back( { 'D', nr } ); 
         }
         else
         {
            bld_code. reductioninfo. push_back( { 'H', 0 } );
               // It is a hard state.

            for( const auto& red : st. reductions )
            {
               std::cout << "lookahead " << red. first << "\n";

               reductionsequence candidates; 
               for( const auto& p : red. second )
                  candidates. push_back(p);

               bool doinggreat = true;
               if( candidates. size( ) > 1 )
               {
                  size_t seqnr = findinredsequences( candidates ); 
                  std::cout << "seqnr = " << seqnr << "\n";
                  if( seqnr < redsequences. size( ))
                  {
                     std::sort( candidates. begin( ), candidates. end( ),
                          [&]( const rule* r1, const rule* r2 )
                          { return 
                               redsequences[seqnr]. at( r1 -> lhs ) <
                               redsequences[seqnr]. at( r2 -> lhs ); } ); 

                     if( containsrepeatedlhs( candidates ))
                        doinggreat = false;
                  }
                  else
                     doinggreat = false;  
               }

               std::cout << "reduction candidates ";
               for( auto c : candidates )
                  std::cout << ( c -> lhs ) << " ";
               std::cout << "\n";
               
               for( size_t i = 0; i + 1 < candidates. size( ); ++ i )
               {
                  if( reductions[ candidates[i] -> nr ]. cond. empty( ))
                  {
                     std::cout << "Reduction candidate ";
                     std::cout << candidates[i] -> nr;
                     std::cout << " has no condition\n";
                     doinggreat = false;
                  }
               }

               if( reductions[ candidates. back( ) -> nr ]. cond. empty( ))
               {
                  std::cout << "last reduction candidate ";
                  std::cout << candidates. back( ) -> nr;
                  std::cout << " has no condition, but there is a shift\n";
                  doinggreat = false;
               }

               if( !doinggreat )
               {
                  std::cout << "   storing a conflict\n";
                  errors. insert( red. first );
               }

               bld_code. reductions. insert( { { ss, red. first }, 
                                               getthenumbers( candidates ) } );
            }   
         }
      }
      else
      {
         bld_code. reductioninfo. push_back( { 'N', 0 } );  
            // State has no reductions.
      }

      // We almost forgot about the shifts. Here they are.

      for( const auto& shift : st. shifts )
         bld_code. shifts. insert( {{ ss, shift. first }, shift. second } ); 
   
      if( errors. size( ))
         conflicts. emplace_back( ss, errors ); 
   }

   bld_code. printascode( out, space, symbolspace );    
}

void parsercodebuilder::printreductioncases( 
         const symbolcodebuilder& bld_sym, 
         std::ostream& out ) const
{
   if( grrr. nrrules( ) != reductions. size( ))
      throw std::logic_error( "sizes must be equal" );

   for( size_t nr = 0; nr != reductions. size( ); ++ nr )
   {
      indentation ind(6);
      out << ind << "case " << nr << ":\n";
      ind += 3;
      if( !reductions[nr]. cond. empty( ))
      {
         out << ind << "if( short s = cond" << nr << "(); s > 0 )\n"; 
         out << ind << "{\n";
         ind += 3;
      }

      if( !bld_sym. attributes. at( grrr. rules[nr]. lhs ). isvoid( ))
      {
         // This should have been checked before, so if it happens
         // here, it is a logic error.

         if( reductions[nr]. body. empty( ))
         {
            std::cout << "rule is " << nr << "\n";
            throw std::logic_error( "no attribute function defined" ); 
         }
 
         out << ind << "reduce( sym_" << grrr.rules[nr]. lhs << ", ";
         out << "body" << nr << "( ), "; 
         out << grrr.rules[nr]. rhs.size( ) << " );\n";
      }
      else
      {
         if( !reductions[nr]. body. empty( ))
         {
            out << ind << "body" << nr << "( );\n";
         }
         out << ind << "reduce( sym_" << grrr.rules[nr].lhs << ", "; 
         out << "std::monostate( ), ";
         out << grrr.rules[nr]. rhs. size( ) << " );\n";
      }
      out << ind << "goto mainloop;\n";

      if( !reductions[nr]. cond. empty( ))
      {
         ind -= 3;
         out << ind << "}\n";
         out << ind << "else\n";
         out << (ind+3) << "if( s < 0 ) shift = reductioninfo. size( );\n"; 
      }
      out << ind << "break;\n";
   }


}

#if 0

void buildparsercode::builddefinition( 
          const std::list< std::string > & parsernamespace,
          const std::list< std::string > & tokennamespace, 
	  const std::list< std::string > & tokenizernamespace, 
	  const grammar& gram,
	  const parsetable& pt,
          const globalvariables& glob, 
	  std::ostream& outputstream ) 
{

   std::ifstream inputstream( "idee.x" );
   if( ! inputstream )
   {
      std::cout << "ERROR: could not open idee.x\n\n";
      exit(0);
   }

   // Some headers:

   outputstream << "\n\n"; 
   outputstream << "#include \"token.h\"\n";
   outputstream << "#include \"tokenizer.h\"\n";
   outputstream << "#include \"parser.h\"\n";
   outputstream << "\n";
   outputstream << "#include <cstdlib>\n";
   outputstream << "\n\n";

   while( true )
   {

      std::string line;

      char nextchar = inputstream. get( );
      if( nextchar == EOF )
         return;

      while( nextchar != '\n' && nextchar != EOF )
      {
         line. push_back( nextchar );
	 nextchar = inputstream. get( );

         if( ! inputstream )
         {
            std::cout << "ERROR: problems with idee.x\n\n";
	    exit(0);
         }
      }

      if( nextchar == EOF )
      {
         std::cout << "ERROR: EOF unexpectedly came in idee.x\n\n";
	 exit(0);
      }

      // We copy the line. If we encounter $X$, we insert something
      // special which depends on the character X. 

      unsigned int pp = 0;
      while( pp < line. size( ))
      {

         if( pp + 3 <= line. size( ) &&
             line [ pp + 0 ] == '$' && 
	     line [ pp + 2 ] == '$' )
         {
            switch( line [ pp + 1 ] ) 
            {
	    case 'P':
               outputstream << cpp::makename( parsernamespace, "parser" ); 
	       break;

            case 'T':
	       outputstream << cpp::makename( tokennamespace, "token" ); 
	       break;

            case 'E':
               outputstream << cpp::makename( tokennamespace, "tkn_" );
               break;

            case 'R':
	       outputstream << cpp::makename( tokenizernamespace, 
                                                       "tokenizer" );
	       break;

            case 'A':
	       for( unsigned int nr = 0; nr < gram. rules. size( ); ++ nr )
               {
		  gram. reductions [nr]. printdefinition( 
                                           outputstream, glob, 
                                           parsernamespace, tokennamespace, 
                                           gram. rules [nr] );
		  outputstream << "\n";  
               }
	       break;

            case 'C':
               for( unsigned int nr = 0; nr < gram. rules. size( ); ++ nr )
               {
                  outputstream << "case " << nr << ":\n";

                  outputstream << "   "; 
                  gram. reductions [nr]. printcall( outputstream,
                                                 glob, gram. rules [nr] );
                  outputstream << "   break;\n";
               }
               break;

            case 'G':
               for( std::list< globalvariables::globalvar > :: const_iterator
                       p = glob. list. begin( );
                       p != glob. list. end( );
                       ++ p )
               {
                  outputstream << ",\n";
                  outputstream << "      ";
                  outputstream << p -> type << " & " << p -> name;
               }
               break;
 
            default:
               std::cout << "ERROR: unknown special insert: ";
	       std::cout << line [ pp + 1 ];
	       std::cout << "\n"; 
	       exit(0);
            }

	    pp += 3; 
         }
	 else
         {
            outputstream << line [ pp ];
	    ++ pp; 
         }
      }
      outputstream << "\n";
   }

}

#endif

std::ostream& 
operator << ( std::ostream& out, const parsercodebuilder& bld )
{
   out << "parsercodebuilder:\n\n";

   out << "namespace =      ";
   bld. space. print( out );
   out << "\n";

   out << "source =          ";
   bld. source. print( out ); 

   out << "parameters:\n";
   for( const auto& g : bld. parameters )
   {
      out << "   " << g. first << " :       " << g. second << "\n";
   } 
   out << "\n"; 

   if( !bld. code_h. empty( ))
      out << "code for .h:\n" << bld. code_h << "\n";

   if( !bld. code_cpp. empty( ))
      out << "code for .cpp:\n" << bld. code_cpp << "\n";
 
   out << bld. grrr << "\n";

   if( bld. redsequences. size( ))
   {
      out << "Reduction Sequences:\n";
      for( const auto& seq: bld. redsequences )
      {
         out << "   ";
         for( auto p = seq. begin( ); p != seq. end( ); ++ p ) 
         {
            if( p != seq. begin( ))
               out << ", ";
            out << ( p -> first ) << "/" << ( p -> second );
         }
         out << "\n";
      } 
      out << "\n";
   }

   for( size_t i = 0; i != bld. reductions. size( ); ++ i )
   {
      if( !bld. reductions[i]. empty( ))
      {
         out << "#" << i << ": ";
         bld. reductions[i]. print( out );
      }
   }

   return out;
}

