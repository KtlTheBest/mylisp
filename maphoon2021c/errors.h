
// this file defines syntaxerror and readerror. A readerror 
// means that reading of input was attempted and failed, for some
// reason different than encountering end of file.
//
// A syntaxerror means that it was attempted to read a term, 
// that enough characters were successfully read, but that they could not
// be parsed according to the input grammar.
//
// Code written by Hans de Nivelle, April 2006.
// See the licence that was included with the code.

#ifndef MAPH_ERRORS
#define MAPH_ERRORS 1 

#include <string>
#include <iostream>

#include "itemsets.h"

struct syntaxerror
{
   std::string problem;
      
   std::string filename;
   long unsigned int line;
   long unsigned int column;

   syntaxerror( const std::string& problem,
		const std::string& filename,
		long unsigned int line,
                long unsigned int column ) 
      : problem( problem ),
        filename( filename ),
	line( line ),
        column( column ) 
   { }

};

std::ostream& operator << ( std::ostream&, const syntaxerror& ); 


struct generalerror
{

   std::string problem;

   std::string filename;
   long unsigned int line;
   long unsigned int column; 

   // The description of the problem should be such that in can
   // be followed by 'in line ... of file ...'.

   generalerror( const std::string& problem,
                 const std::string& filename,
                 long unsigned int line,
                 long unsigned int column ) 
      : problem( problem ),
        filename( filename ),
	line( line ),
        column( column ) 
   { }
};

std::ostream& operator << ( std::ostream&, const generalerror& );


struct conflict 
{
   size_t statenr;
   symbolset lookaheads;

   conflict( size_t statenr, const symbolset& lookaheads )
      : statenr( statenr ),
        lookaheads( lookaheads ) 
   { } 
};

std::ostream& operator << ( std::ostream&, const conflict& );


struct ideeproblem 
{
   std::string problem; 
   long unsigned int line;
  
   ideeproblem( const std::string& problem, long unsigned int line )
      : problem( problem ), line( line )
   { }
};

std::ostream& operator << ( std::ostream&, const ideeproblem& ); 

#endif


