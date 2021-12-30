
// Written by Hans de Nivelle, February 2021.
// See the licence that was included with this code. 

#ifndef MAPH_PARSERCODEBUILDER 
#define MAPH_PARSERCODEBUILDER   1 

#include "symbolcodebuilder.h"
#include "parsetable.h"

// This struct has an open design because it is gradually filled
// in with user input.

struct parsercodebuilder 
{

   cpp::nspace space;   // Full name of the parser is always 'parser'.

   cpp::codefragment source;
      // This must be C++ expression that can be used as source.
      // It must return a symbol. 

   std::vector< std::pair< cpp::identifier, cpp::type >> parameters;
      // Order matters, so we cannot use a map here. 

   cpp::codefragment code_h;
   cpp::codefragment code_cpp;
      // This is code that goes to the beginning of parser.h 
      // (intended for includes), and code that goes to the
      // beginning of parser.cpp (intended for helper functions in
      // anonymous namespace).

   std::vector< symbol::map< size_t >> redsequences;
      // If symbols occur in the same set, the one which is mapped to the
      // lower number is preferred.
  
   bool usedefaults = true; 
      // If true, we use default reductions. This simplifies
      // the parser, and is useful for interactive applications.

   bool usererror = false;
      // If true, the user defines his own error function.
      // If fase, we create a default one.
  
   // Code that is associated to a reduction:

   struct reduction
   {
      std::unordered_map< std::string, size_t > parameters;
         // These are the parameters that the user defined in the 
         // reduction code. For example E => E:e plus F:f will result in
         // parameters[ "e" ] = 0, and parameters[ "f" ] = 2.
         // The types can be read off from the rules, so we don't store them.

      cpp::codefragment cond;
      cpp::codefragment body;

      reduction( std::unordered_map< std::string, size_t > && parameters, 
                 cpp::codefragment&& cond,
                 cpp::codefragment&& body )
         : parameters( std::move( parameters )),
           cond( std::move( cond )),
           body( std::move( body ))
      { }

      bool empty( ) const { return cond. empty( ) && body. empty( ); }

      void print( std::ostream& out ) const; 
   };

   grammar grrr;
   std::vector< reduction > reductions; 


   parsercodebuilder( const cpp::nspace& space )
      : space( space )
   { }

   using reductionsequence = std::vector< const rule* > ; 
      // A sequence of possible reductions that should be tried in the
      // given order. 

   size_t findinredsequences( const reductionsequence& ) const;
      // returns redsequences. size( ) if we don't find it.

   static bool containsrepeatedlhs( const reductionsequence& );
      // Returns true if two rules in the sequence have the same lhs. 
      // We assume that the sequences is sorted by lhs, because then 
      // the check is very cheap. 
  
   static std::vector< size_t > getthenumbers( const reductionsequence& );
      // Get the rule numbers. They go into the reduction table. 
 
   void 
   printcode( const symbolcodebuilder& bld_sym, const parsetable& pt,
              std::vector< conflict > & conflicts,
              std::istream& idee, std::ostream& cpp, std::ostream& hh ) const;
      // Uses idee.x as template.
      // We need the symbolcode builder for the namespace of symbol,
      // for the types of the symbols and for the attribute type. 

   std::unordered_map< std::string, std::string >
   createreplacement( size_t nr, const symbolcodebuilder& bld_sym ) const;
      // Create the replacment that maps the parameters 
      // for the i-th rule into their expressions.

   void printparameterfields( std::ostream& ) const;
   void printconstructor( std::ostream& ) const; 
   void printactiondeclarations( 
           const symbolcodebuilder& bld_sym, std::ostream& ) const;
   void printactiondefinitions(
           const symbolcodebuilder& bld_sym, std::ostream& ) const;

   void printmaintables( const parsetable& pt, 
                         const cpp::nspace& symbolspace,
                         std::vector< conflict > & conflicts, 
                         std::ostream& out ) const;

   void printreductioncases( const symbolcodebuilder& bld_sym, 
                             std::ostream& out ) const; 
};


std::ostream& operator << ( std::ostream& out, const parsercodebuilder& bld );

#endif


