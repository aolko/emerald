from gen.Rubito.rubitoLexer import *
from gen.Rubito.rubitoListener import *
from gen.Rubito.rubitoParser import *


def main():
    lexer = rubitoLexer(StdinStream())
    stream = CommonTokenStream(lexer)
    parser = rubitoParser(stream)
    tree = parser.prog()
    printer = rubitoListener()
    walker = ParseTreeWalker()
    walker.walk(printer, tree)


if __name__ == '__main__':
    main()
