

%startsymbol E EOF

%grammar

E => F plus E | F ; 
F => id ; 


