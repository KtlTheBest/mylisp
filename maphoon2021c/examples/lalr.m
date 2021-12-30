
// Language with tricky lookaheads:

%startsymbol S EOF

%rules

S =>  c b c a | A a A b ;
A =>  B ;
B =>  c ; 


