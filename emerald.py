from gen.Rubito.rubitoLexer import *
from gen.Rubito.rubitoListener import *
from gen.Rubito.rubitoParser import *
from gen.Rubito.rubitoVisitor import *


def main():
    lexer = rubitoLexer(input)
    stream = CommonTokenStream(lexer)
    parser = rubitoParser(stream)
    tree = parser.prog()
    printer = rubitoListener()
    walker = ParseTreeWalker()
    walker.walk(printer, tree)

    class HelloPrintListener(rubitoListener):
        def enterFunction_definition(self, ctx):
            print("found a function declaration: %s" % ctx.ID())


if __name__ == '__main__':
    main()
