
%startsymbol S EOF

%grammar

S => E ;

E => E plus F
  | F
  ;  

F => F times G 
  | G 
  ;

G => lpar E rpar 
  | number
  | id 
  ;


