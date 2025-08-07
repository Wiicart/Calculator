# C Calculator
A basic C calculator that reads from left to right.\
Supports `_, -, *, /, ^` operators.

Logic based on [this](https://blog.darrien.dev/posts/writing-calc-parser/)

## Usage & Installation

Clone this repo locally.
Install a C compiler for your platform, such as `gcc`.

To build, in the directory of your local repo,
run `gcc -o calculator src/main.c src/parser/parser.c src/token/token.c -lm
`

To run the program run `./calculator` where the program is installed.

Once the program is running, simply enter a calculation like `5 + 65`.

For help, type `help`

To quit, type `quit`
