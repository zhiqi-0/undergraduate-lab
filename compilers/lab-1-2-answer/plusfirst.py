'''PlusFirstession recognizer.
Handles PlusFirstession described in PlusFirst.g4.
Grammar file should be compiled by antlr4 with option '-Dlanguage=Python3' before executing this.
Module 'antlr4' is required.
'''
import antlr4
import PlusFirstLexer
import PlusFirstParser
import PlusFirstListener
from typing import Mapping


class Listener(PlusFirstListener.PlusFirstListener):
    '''Listener doing calculation based on recognized input.
    '''

    def __init__(self, var_value_source: Mapping[str, int]):
        self.var_value_source = var_value_source

    def exitMult(self, ctx: PlusFirstParser.PlusFirstParser.EContext):
        ctx.value = ctx.getChild(0).value * ctx.getChild(2).value

    def exitNum(self, ctx: PlusFirstParser.PlusFirstParser.EContext):
        ctx.value = int(str(ctx.getChild(0)))

    def exitPlus(self, ctx: PlusFirstParser.PlusFirstParser.EContext):
        ctx.value = ctx.getChild(0).value + ctx.getChild(2).value


class LazyInputDict(dict):
    '''A lazy dictionary asking for input when a new item is queried.'''

    def __getitem__(self, key):
        try:
            return dict.__getitem__(self, key)
        except KeyError:
            self[key] = int(
                input('Please enter value for variable \'{}\': '.format(key)))
        return dict.__getitem__(self, key)


if __name__ == '__main__':
    PARSER = PlusFirstParser.PlusFirstParser(antlr4.CommonTokenStream(PlusFirstLexer.PlusFirstLexer(
        antlr4.InputStream(input('Please enter a expression: ')))))
    PARSER.addParseListener(Listener(LazyInputDict()))
    print(PARSER.e().value)
