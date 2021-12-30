
%startsymbol S EOF 

%rules

S => a S a | A ;
A => b a b S | b S b ;



