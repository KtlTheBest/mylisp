
%startsymbol S EOF 

%rules

S => a S A | A | c ;

A => a b | S b ;


