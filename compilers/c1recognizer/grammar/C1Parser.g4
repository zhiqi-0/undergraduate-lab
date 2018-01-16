parser grammar C1Parser;
options { tokenVocab = C1Lexer; }

compilationUnit: (decl | funcdef)+ EOF
               ;
decl: constdecl 
    | vardecl
    ;
constdecl: Const (Int)? constdef (Comma constdef)* SemiColon;
constdef: Identifier Assign exp 
        | Identifier LeftBracket (exp)? RightBracket Assign LeftBrace exp (Comma exp)* RightBrace
        ;
vardecl: Int vardef (Comma vardef)* SemiColon;
vardef: Identifier 
   | Identifier LeftBracket exp RightBracket 
   | Identifier Assign exp 
   | Identifier LeftBracket (exp)? RightBracket Assign LeftBrace exp (Comma exp)* RightBrace
   ;
funcdef: Void Identifier LeftParen RightParen block;
block: LeftBrace (decl | stmt)* RightBrace;
stmt: lval Assign exp SemiColon 
    | Identifier LeftParen RightParen SemiColon 
    | block 
    | If LeftParen cond RightParen stmt (Else stmt)? 
    | While LeftParen cond RightParen stmt
    | SemiColon
    ;
lval: Identifier 
    | Identifier LeftBracket exp RightBracket
    ;
cond: exp Equal exp
    | exp NonEqual exp
    | exp Less exp
    | exp Greater exp
    | exp LessEqual exp
    | exp GreaterEqual exp
    ;
exp: Minus exp
   | Plus exp
   | exp Divide exp
   | exp Multiply exp
   | exp Modulo exp 
   | exp Minus exp 
   | exp Plus exp
   | LeftParen exp RightParen 
   | lval 
   | Number
   ;
