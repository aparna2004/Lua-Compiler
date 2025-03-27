# Lua - compiler

## Features
- Supports
    - arithmetic expressions
    - boolean expressions
    - logical expressions
    - print statement
    - if, if-else, if-elseif-else statements
    - for, while loops
    - string and string concatenation

## Usage
### Test
For the compiler using lex and yacc, 
```sh
./test auto
```
For the compiler using manual lexer and parser, 
```sh
./test
```
### Run
For the compiler using lex and yacc, 
```sh
# assuming input.lua is the input file
cd cpp/lex\ and\ yacc/
make clean && make
./main < input.lua 
```
For the compiler using manual lexer and parser, 
```sh
# assuming input.lua is the input file
cd cpp/manual/
make clean && make
./minilua input.lua
```

### Debug and visualisation
```sh
# assuming input.lua is the input file
./minilua input.lua [--tokens| --parsetree |--trace | --tac]

```

where

- `--tokens` shows token recognition table
- `--trace` shows node calls
- `--parsetree` shows the parse tree
- `--tac` genreates three address code