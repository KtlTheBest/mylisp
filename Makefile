
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wpedantic -pedantic-errors -std=c++17 -I util
CPP = g++

listfiles=$(ls list/*.{cpp,h})

main : Makefile   filereader.o parser.o symbol.o tokenizer.o bigint.o main.o string.o list.o cons.o
	$(CPP) $(Flags) -o main   main.o filereader.o parser.o symbol.o tokenizer.o bigint.o string.o list.o cons.o

main.o : Makefile   main.cpp eval.h parser.h parser.cpp symbol.h symbol.cpp neweval.h
	$(CPP) -c $(Flags) main.cpp -o  main.o

filereader.o : Makefile   util/filereader.cpp  util/filereader.h 
	$(CPP) -c $(Flags) util/filereader.cpp -o  filereader.o

parser.o : Makefile   parser.cpp   parser.h symbol.h util/bigint.h tokenizer.h util/filereader.h 
	$(CPP) -c $(Flags) -I util parser.cpp -o  parser.o

symbol.o : Makefile   symbol.cpp symbol.h $(listfiles) util/bigint.h 
	$(CPP) -c $(Flags) symbol.cpp -o  symbol.o

parser.cpp : grammar.m  symbol.cpp symbol.h Makefile
	maphoon2021c/maphoon grammar.m . maphoon2021c

parser.h : grammar.m  symbol.cpp symbol.h Makefile
	maphoon2021c/maphoon grammar.m . maphoon2021c

symbol.cpp : grammar.m Makefile
	maphoon2021c/maphoon grammar.m .

symbol.h : grammar.m Makefile
	maphoon2021c/maphoon grammar.m .

tokenizer.o : Makefile   tokenizer.cpp   lexing/classifier.h lexing/acceptor.h lexing/flatmap.h lexing/state.h lexing/minmax.h lexing/deterministic.h lexing/generators.h util/indentation.h lexing/trivial.h lexing/minimization.h lexing/partition.h lexing/stateset.h lexing/reachableclasses.h lexing/algorithms.h tokenizer.h symbol.h util/bigint.h util/filereader.h 
	$(CPP) -c $(Flags) tokenizer.cpp -o  tokenizer.o

cons.o: list/cons.cpp list/cons.h
	$(CPP) -c $(Flags) list/cons.cpp -o cons.o

list.o: list/list.cpp list/list.h
	$(CPP) -c $(Flags) list/list.cpp -o list.o

string.o: list/string.cpp list/string.h
	$(CPP) -c $(Flags) list/string.cpp -o string.o

bigint.o : Makefile   util/bigint.cpp   util/bigint.h 
	$(CPP) -c $(Flags) util/bigint.cpp -o  bigint.o

