
%startsymbol E EOF 

%rules

% E : identifier 
%   | integer 
%   | identifier lpar A rpar
%   ;


% A : 
%   | A1 
%   ;

% A1 : E 
%    | E comma A1
%    ;






