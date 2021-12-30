
%startsymbol E EOF

%rules

E => F plus E 
  | F
  ;  

F => id 
  ;


