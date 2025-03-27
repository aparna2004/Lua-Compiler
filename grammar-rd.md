program     → statement program
            | statement

statement   → if_statement
            | while_statement
            | for_statement
            | print_statement
            | assignment

if_statement    → "if" expression "then" 
                  statement_list
                  elseif_list
                  else_part
                  "end"

elseif_list     → "elseif" expression "then" statement_list elseif_list
                | ε

else_part       → "else" statement_list
                | ε

while_statement → "while" expression "do" statement_list "end"

for_statement   → "for" IDENTIFIER "=" expression "," expression step? "do" 
                  statement_list 
                  "end"

step            → "," expression

print_statement → "print" expression

assignment      → IDENTIFIER "=" expression
                | expression

expression → logical_or

logical_or → logical_and ("or" logical_and)*

logical_and → equality ("and" equality)*

equality → comparison (("==" | "~=") comparison)*

comparison → concat (("<" | ">" | "<=" | ">=") concat)*

concat → term (".." term)*

term → factor ("+" | "-" factor)*

factor → unary ("*" | "/" unary)*


unary → "-" unary
      | "not" unary
      | primary

primary → NUMBER
        | STRING
        | "true"
        | "false"
        | IDENTIFIER
        | "(" expression ")"

