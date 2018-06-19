from emerald import *
from textx.metamodel import metamodel_from_file

emrld_mm = metamodel_from_file('emerald/grammar.tx')

# Load the program:
program = emrld_mm.model_from_file('emerald/example.rbt')

for statement in program.statements:
    print(statement)