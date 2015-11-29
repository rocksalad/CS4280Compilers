Parser:

invoke by making with makefile (make) and then typing ./testScanner <someinputfileendinginlanextension>

./testScanner somefile for example would invoke the scanner/parser using somefile.lan to read in.

parser will call scanner and generate parse tree, then upon a successful parse it will print the parse tree with a pre-order traversal.
