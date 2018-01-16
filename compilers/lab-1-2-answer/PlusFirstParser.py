# Generated from PlusFirst.g4 by ANTLR 4.7
# encoding: utf-8
from antlr4 import *
from io import StringIO
from typing.io import TextIO
import sys

def serializedATN():
    with StringIO() as buf:
        buf.write("\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\6")
        buf.write("\30\4\2\t\2\4\3\t\3\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3")
        buf.write("\3\3\3\3\3\3\3\7\3\23\n\3\f\3\16\3\26\13\3\3\3\2\3\4\4")
        buf.write("\2\4\2\2\2\27\2\6\3\2\2\2\4\t\3\2\2\2\6\7\5\4\3\2\7\b")
        buf.write("\7\2\2\3\b\3\3\2\2\2\t\n\b\3\1\2\n\13\7\3\2\2\13\24\3")
        buf.write("\2\2\2\f\r\f\5\2\2\r\16\7\4\2\2\16\23\5\4\3\6\17\20\f")
        buf.write("\4\2\2\20\21\7\5\2\2\21\23\5\4\3\5\22\f\3\2\2\2\22\17")
        buf.write("\3\2\2\2\23\26\3\2\2\2\24\22\3\2\2\2\24\25\3\2\2\2\25")
        buf.write("\5\3\2\2\2\26\24\3\2\2\2\4\22\24")
        return buf.getvalue()


class PlusFirstParser ( Parser ):

    grammarFileName = "PlusFirst.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "<INVALID>", "'+'", "'*'" ]

    symbolicNames = [ "<INVALID>", "Number", "Plus", "Multiply", "WhiteSpace" ]

    RULE_s = 0
    RULE_e = 1

    ruleNames =  [ "s", "e" ]

    EOF = Token.EOF
    Number=1
    Plus=2
    Multiply=3
    WhiteSpace=4

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.7")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None



    class SContext(ParserRuleContext):

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def e(self):
            return self.getTypedRuleContext(PlusFirstParser.EContext,0)


        def EOF(self):
            return self.getToken(PlusFirstParser.EOF, 0)

        def getRuleIndex(self):
            return PlusFirstParser.RULE_s

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterS" ):
                listener.enterS(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitS" ):
                listener.exitS(self)




    def s(self):

        localctx = PlusFirstParser.SContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_s)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 4
            self.e(0)
            self.state = 5
            self.match(PlusFirstParser.EOF)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx

    class EContext(ParserRuleContext):

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser


        def getRuleIndex(self):
            return PlusFirstParser.RULE_e

     
        def copyFrom(self, ctx:ParserRuleContext):
            super().copyFrom(ctx)


    class MultContext(EContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a PlusFirstParser.EContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def e(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(PlusFirstParser.EContext)
            else:
                return self.getTypedRuleContext(PlusFirstParser.EContext,i)

        def Multiply(self):
            return self.getToken(PlusFirstParser.Multiply, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterMult" ):
                listener.enterMult(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitMult" ):
                listener.exitMult(self)


    class NumContext(EContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a PlusFirstParser.EContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def Number(self):
            return self.getToken(PlusFirstParser.Number, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterNum" ):
                listener.enterNum(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitNum" ):
                listener.exitNum(self)


    class PlusContext(EContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a PlusFirstParser.EContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def e(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(PlusFirstParser.EContext)
            else:
                return self.getTypedRuleContext(PlusFirstParser.EContext,i)

        def Plus(self):
            return self.getToken(PlusFirstParser.Plus, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterPlus" ):
                listener.enterPlus(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitPlus" ):
                listener.exitPlus(self)



    def e(self, _p:int=0):
        _parentctx = self._ctx
        _parentState = self.state
        localctx = PlusFirstParser.EContext(self, self._ctx, _parentState)
        _prevctx = localctx
        _startState = 2
        self.enterRecursionRule(localctx, 2, self.RULE_e, _p)
        try:
            self.enterOuterAlt(localctx, 1)
            localctx = PlusFirstParser.NumContext(self, localctx)
            self._ctx = localctx
            _prevctx = localctx

            self.state = 8
            self.match(PlusFirstParser.Number)
            self._ctx.stop = self._input.LT(-1)
            self.state = 18
            self._errHandler.sync(self)
            _alt = self._interp.adaptivePredict(self._input,1,self._ctx)
            while _alt!=2 and _alt!=ATN.INVALID_ALT_NUMBER:
                if _alt==1:
                    if self._parseListeners is not None:
                        self.triggerExitRuleEvent()
                    _prevctx = localctx
                    self.state = 16
                    self._errHandler.sync(self)
                    la_ = self._interp.adaptivePredict(self._input,0,self._ctx)
                    if la_ == 1:
                        localctx = PlusFirstParser.PlusContext(self, PlusFirstParser.EContext(self, _parentctx, _parentState))
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_e)
                        self.state = 10
                        if not self.precpred(self._ctx, 3):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 3)")
                        self.state = 11
                        self.match(PlusFirstParser.Plus)
                        self.state = 12
                        self.e(4)
                        pass

                    elif la_ == 2:
                        localctx = PlusFirstParser.MultContext(self, PlusFirstParser.EContext(self, _parentctx, _parentState))
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_e)
                        self.state = 13
                        if not self.precpred(self._ctx, 2):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 2)")
                        self.state = 14
                        self.match(PlusFirstParser.Multiply)
                        self.state = 15
                        self.e(3)
                        pass

             
                self.state = 20
                self._errHandler.sync(self)
                _alt = self._interp.adaptivePredict(self._input,1,self._ctx)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.unrollRecursionContexts(_parentctx)
        return localctx



    def sempred(self, localctx:RuleContext, ruleIndex:int, predIndex:int):
        if self._predicates == None:
            self._predicates = dict()
        self._predicates[1] = self.e_sempred
        pred = self._predicates.get(ruleIndex, None)
        if pred is None:
            raise Exception("No predicate with index:" + str(ruleIndex))
        else:
            return pred(localctx, predIndex)

    def e_sempred(self, localctx:EContext, predIndex:int):
            if predIndex == 0:
                return self.precpred(self._ctx, 3)
         

            if predIndex == 1:
                return self.precpred(self._ctx, 2)
         




