grammar MultFirst;

Number: [1-9] [0-9]*;
Plus: '+';
Multiply: '*';
WhiteSpace: [ \t\n\r]+ -> skip;

s: e EOF;
e: e Multiply e # Mult
    | e Plus e # Plus
    | Number # Num
    ;
