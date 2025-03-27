program     -> statement program'

program'    -> statement program'
             | ε

statement   -> ifStmt
             | whileStmt 
             | forStmt 
             | printStmt 
             | assignment

ifStmt      -> "if" expression "then" statements elseifList elsePart "end"

elseifList  -> "elseif" expression "then" statements elseifList
             | ε

elsePart    -> "else" statements
             | ε

statements  -> statement statements
             | ε

whileStmt   -> "while" expression "do" statements "end"

forStmt     -> "for" IDENTIFIER "=" expression "," expression step "do" statements "end"

step        -> "," expression
             | ε

printStmt   -> "print" expression

assignment  -> IDENTIFIER "=" expression

expression  -> logicalAnd orTail

orTail      -> "or" logicalAnd orTail
             | ε

logicalAnd  -> equality andTail

andTail     -> "and" equality andTail
             | ε

equality    -> comparison equalityTail

equalityTail-> "==" comparison equalityTail
             | "~=" comparison equalityTail
             | ε

comparison  -> concat comparisonTail

comparisonTail -> "<" concat comparisonTail
                | ">" concat comparisonTail
                | "<=" concat comparisonTail
                | ">=" concat comparisonTail
                | ε

concat      -> term concatTail

concatTail  -> ".." term concatTail
             | ε

term        -> factor termTail

termTail    -> "+" factor termTail
             | "-" factor termTail
             | ε

factor      -> unary factorTail

factorTail  -> "*" unary factorTail
             | "/" unary factorTail
             | ε

unary       -> "-" unary
             | "not" unary
             | primary

primary     -> NUMBER
             | STRING
             | "true"
             | "false"
             | IDENTIFIER
             | "(" expression ")"