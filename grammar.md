program     -> program statement
             | statement


statement   -> ifStmt
             | whileStmt 
             | forStmt 
             | printStmt 
             | assignment


ifStmt      -> "if" expression "then" statements elseifList elsePart "end"


elseifList  -> elseifList "elseif" expression "then" statements
             | ε


elsePart    -> "else" statements
             | ε


statements  -> statements statement
             | ε


whileStmt   -> "while" expression "do" statements "end"



forStmt     -> "for" IDENTIFIER "=" expression "," expression step "do" statements "end"


step        -> "," expression
             | ε


printStmt   -> "print" expression


assignment  -> IDENTIFIER "=" expression


expression  -> logicalOr


logicalOr   -> logicalOr "or" logicalAnd
             | logicalAnd


logicalAnd  -> logicalAnd "and" equality
             | equality


equality    -> equality "==" comparison
             | equality "~=" comparison
             | comparison


comparison  -> comparison "<" concat
             | comparison ">" concat
             | comparison "<=" concat
             | comparison ">=" concat
             | concat


concat      -> concat ".." term
             | term


term        -> term "+" factor
             | term "-" factor
             | factor


factor      -> factor "*" unary
             | factor "/" unary
             | unary


unary       -> "-" unary
             | "not" unary
             | primary


primary     -> NUMBER
             | STRING
             | "true"
             | "false"
             | IDENTIFIER
             | "(" expression ")"