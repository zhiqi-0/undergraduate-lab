lexer grammar C1Lexer;

tokens {
    Comma,
    SemiColon,
    Assign,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
    LeftParen,
    RightParen,
    If,
    Else,
    While,
    Const,
    Equal,
    NonEqual,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulo,

    Int,
    Void,

    Identifier,
    Number
}
Comma: ',' ;
SemiColon: ';' ;
Assign: '=' ;
LeftBracket: '[' ;
RightBracket: ']' ;
LeftBrace: '{' ;
RightBrace: '}';
LeftParen: '(' ;
RightParen: ')' ;
If: 'if' ;
Else: 'else' ;
While: 'while' ;
Const: 'const' ;
Equal: '==' ;
NonEqual: '!=' ;
Less: '<' ;
Greater: '>' ;
LessEqual: '<=' ;
GreaterEqual: '>=' ;
Plus: '+' ;
Minus: '-' ;
Multiply: '*' ;
Divide: '/' ;
Modulo: '%' ;
Int: 'int' ;
Void: 'void' ;
Identifier: ('_' | [a-zA-Z])+ ('_' | [a-zA-Z] | [0-9])* ;
Number: [0-9]+ | '0x' [0-9a-fA-F]+ ;
WhiteSpace: [ \t\r\n]+ -> skip;
LineComment: ('//''\r'?'\n'|'//'(.)*? ~'\\''\r'?'\n') -> skip;
BlockComment: '/*' (.)*? '*/' -> skip; 

