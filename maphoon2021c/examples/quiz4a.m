
%startsymbol S EOF 

%rules

S => a S a | a A ;
A => a a b S | b S b ;


