
%startsymbol E EOF 

%rules

E => E plus F
  | E minus F
  | F
  ;  

F => F times G 
  | F div G 
  | G 
  ;

G => minus G 
  | lpar E rpar 
  | identifier
  | number
  | identifier lpar A rpar
  ;

A => E 
  | A comma E  
  ; 






