
%startsymbol S EOF 

%rules

S => if E then S 
  |  if E then S else S 
  |  ident becomes E 
  ;

E => number 
  | ident
  ;


