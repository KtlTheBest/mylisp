

// Code written by Hans de Nivelle, April 2006.
// See the licence that was included with the code.


#include "errors.h"


std::ostream& operator << ( std::ostream& out, const syntaxerror& err )
{
   out << "Syntax error: " << err. problem;
   out << " at position " << (err.line+1) << "/" << (err.column+1); 
   out << " of inputstream " << err. filename;  

   return out;
}
            

std::ostream& operator << ( std::ostream& out, const generalerror& err )
{
   out << "Error: " << err. problem;
   out << " at position " << (err.line+1) << "/" << (err.column+1); 
   out << " of inputstream " << err. filename;

   return out;
}

std::ostream& operator << ( std::ostream& out, const conflict& confl )
{
   out << "unresolved conflict in state " << confl. statenr;
   out << " for lookahead " << confl. lookaheads;
   return out;
}

std::ostream& operator << ( std::ostream& out, const ideeproblem& prob )
{
   out << "problem with idee.x in line " << (prob. line+1) << ": ";
   out << prob. problem << "\n";
   return out;
}

