grammar PlusFirst;

Number: [1-9] [0-9]*;
Plus: '+';
Multiply: '*';
WhiteSpace: [ \t\n\r]+ -> skip;

s : e EOF;
e : e Plus e # Plus
  | e Multiply e # Mult
  | Number # Num
  ;