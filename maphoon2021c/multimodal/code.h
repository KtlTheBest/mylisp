
// automatically generated code:
// generator written by Hans de Nivelle and Dina Muktubayeva

template< typename S >
std::pair< symboltype, size_t > readandclassify( lexing::trivial triv, S& inp )
{
   auto latest = std::make_pair< symboltype, size_t > ( sym_ERROR, 0 );
   if( !inp. has(1))
      return latest;
   char c = inp. peek(0);
   size_t i = 0;

Q00:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q0, next char is " << c << "\n";
   switch( c )
   {
   case 32:
      ++ i; goto Q01;
   case 36:
      ++ i; goto Q02;
   case 38:
      ++ i; goto Q03;
   case 40:
      ++ i; goto Q04;
   case 41:
      ++ i; goto Q05;
   case 45:
      ++ i; goto Q06;
   case 47:
      ++ i; goto Q07;
   case 48:
      ++ i; goto Q08;
   case 59:
      ++ i; goto Q10;
   case 60:
      ++ i; goto Q11;
   case 61:
      ++ i; goto Q12;
   case 62:
      ++ i; goto Q13;
   case 83:
      ++ i; goto Q14;
   case 70:
      ++ i; goto Q15;
   case 78:
      ++ i; goto Q16;
   case 82:
      ++ i; goto Q17;
   case 84:
      ++ i; goto Q18;
   case 91:
      ++ i; goto Q19;
   case 93:
      ++ i; goto Q20;
   case 102:
      ++ i; goto Q21;
   case 116:
      ++ i; goto Q22;
   case 124:
      ++ i; goto Q23;
   case 126:
      ++ i; goto Q24;
   case 37:
   case 39:
   case 46:
   case 58:
   case 92:
   case 123:
   case 125:
      return latest;
   }
   if( c >= 63 )
   {
      if( c >= 94 )
      {
         if( c >= 127 ) return latest;
         if( c >= 97 ) { ++ i; goto Q14; }
         if constexpr( true ) return latest;
      }
      else
      {
         if( c >= 65 ) { ++ i; goto Q14; }
         if constexpr( true ) return latest;
      }
   }
   else
   {
      if( c >= 49 ) { ++ i; goto Q09; }
      if( c >= 11 ) return latest;
      if( c >= 9 ) { ++ i; goto Q01; }
      if constexpr( true ) return latest;
   }
Q01:
   latest. first = sym_WHITESPACE; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q1, next char is " << c << "\n";
   if( c == 32 ) { ++ i; goto Q01; }
   if( c >= 11 ) return latest;
   if( c >= 9 ) { ++ i; goto Q01; }
   if constexpr( true ) return latest;
Q02:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q2, next char is " << c << "\n";
   if( c >= 91 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q25; }
      if constexpr( true ) return latest;
   }
   else
   {
      if( c >= 65 ) { ++ i; goto Q25; }
      if constexpr( true ) return latest;
   }
Q03:
   latest. first = sym_AND; latest. second = i;
   return latest;
Q04:
   latest. first = sym_LEFTPAR; latest. second = i;
   return latest;
Q05:
   latest. first = sym_RIGHTPAR; latest. second = i;
   return latest;
Q06:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q6, next char is " << c << "\n";
   if( c == 62 ) { ++ i; goto Q26; }
   if constexpr( true ) return latest;
Q07:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q7, next char is " << c << "\n";
   if( c == 42 ) { ++ i; goto Q27; }
   if( c == 47 ) { ++ i; goto Q28; }
   if constexpr( true ) return latest;
Q08:
   latest. first = sym_NUMBER; latest. second = i;
   return latest;
Q09:
   latest. first = sym_NUMBER; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q9, next char is " << c << "\n";
   if( c >= 58 ) return latest;
   if( c >= 48 ) { ++ i; goto Q09; }
   if constexpr( true ) return latest;
Q10:
   latest. first = sym_SEMICOLON; latest. second = i;
   return latest;
Q11:
   latest. first = sym_DIASTART; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q11, next char is " << c << "\n";
   if( c == 45 ) { ++ i; goto Q29; }
   if( c == 62 ) { ++ i; goto Q30; }
   if constexpr( true ) return latest;
Q12:
   latest. first = sym_BECOMES; latest. second = i;
   return latest;
Q13:
   latest. first = sym_DIAEND; latest. second = i;
   return latest;
Q14:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q14, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q15:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q15, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 65 ) { ++ i; goto Q31; }
   if( c == 96 ) return latest;
   if( c >= 66 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q16:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q16, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 78 ) { ++ i; goto Q32; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q17:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q17, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 69 ) { ++ i; goto Q33; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q18:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q18, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 82 ) { ++ i; goto Q34; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q19:
   latest. first = sym_BOXSTART; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q19, next char is " << c << "\n";
   if( c == 93 ) { ++ i; goto Q35; }
   if constexpr( true ) return latest;
Q20:
   latest. first = sym_BOXEND; latest. second = i;
   return latest;
Q21:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q21, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 97 ) { ++ i; goto Q36; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 98 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q22:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q22, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 114 ) { ++ i; goto Q37; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q23:
   latest. first = sym_OR; latest. second = i;
   return latest;
Q24:
   latest. first = sym_NOT; latest. second = i;
   return latest;
Q25:
   latest. first = sym_METAVAR; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q25, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q25; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q25; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q25; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q25; }
      if constexpr( true ) return latest;
   }
Q26:
   latest. first = sym_IMP; latest. second = i;
   return latest;
Q27:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q27, next char is " << c << "\n";
   if( c == 42 ) { ++ i; goto Q38; }
   if constexpr( true ) { ++ i; goto Q27; }
Q28:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q28, next char is " << c << "\n";
   if( c == 10 ) { ++ i; goto Q39; }
   if constexpr( true ) { ++ i; goto Q28; }
Q29:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q29, next char is " << c << "\n";
   if( c == 62 ) { ++ i; goto Q40; }
   if constexpr( true ) return latest;
Q30:
   latest. first = sym_DIA; latest. second = i;
   return latest;
Q31:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q31, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 76 ) { ++ i; goto Q41; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q32:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q32, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 70 ) { ++ i; goto Q42; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q33:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q33, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 84 ) { ++ i; goto Q43; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q34:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q34, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 85 ) { ++ i; goto Q44; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q35:
   latest. first = sym_BOX; latest. second = i;
   return latest;
Q36:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q36, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 108 ) { ++ i; goto Q45; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q37:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q37, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 117 ) { ++ i; goto Q46; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q38:
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q38, next char is " << c << "\n";
   if( c == 42 ) { ++ i; goto Q38; }
   if( c == 47 ) { ++ i; goto Q39; }
   if constexpr( true ) { ++ i; goto Q27; }
Q39:
   latest. first = sym_COMMENT; latest. second = i;
   return latest;
Q40:
   latest. first = sym_EQUIV; latest. second = i;
   return latest;
Q41:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q41, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 83 ) { ++ i; goto Q44; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q42:
   latest. first = sym_NNF; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q42, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q43:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q43, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 85 ) { ++ i; goto Q47; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q44:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q44, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 69 ) { ++ i; goto Q48; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q45:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q45, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 115 ) { ++ i; goto Q46; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q46:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q46, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 101 ) { ++ i; goto Q48; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q47:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q47, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 82 ) { ++ i; goto Q49; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q48:
   latest. first = sym_CONST; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q48, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q49:
   latest. first = sym_ID; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q49, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 78 ) { ++ i; goto Q50; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
Q50:
   latest. first = sym_RETURN; latest. second = i;
   if( !inp. has(i+1))
      return latest;
   c = inp. peek(i);
   std::cout << "state Q50, next char is " << c << "\n";
   if( c == 95 ) { ++ i; goto Q14; }
   if( c == 96 ) return latest;
   if( c >= 65 )
   {
      if( c >= 123 ) return latest;
      if( c >= 97 ) { ++ i; goto Q14; }
      if( c >= 91 ) return latest;
      if constexpr( true ) { ++ i; goto Q14; }
   }
   else
   {
      if( c >= 58 ) return latest;
      if( c >= 48 ) { ++ i; goto Q14; }
      if constexpr( true ) return latest;
   }
}

