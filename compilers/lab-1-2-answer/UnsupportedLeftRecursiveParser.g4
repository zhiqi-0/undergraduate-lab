parser grammar UnsupportedLeftRecursiveParser;
options { tokenVocab = UnsupportedLeftRecursiveLexer; }

s: a | Int;
a: b | Int;
b: s | Int;