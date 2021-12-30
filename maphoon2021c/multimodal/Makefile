
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++17
CPP = g++


multimodal : Makefile   multimodal.o tokenizer.o ../filereader.o symbol.o ../lexing/stateset.o ../lexing/partition.o form.o agent.o parser.o 
	$(CPP) $(Flags) -o multimodal   multimodal.o tokenizer.o ../filereader.o symbol.o ../lexing/stateset.o ../lexing/partition.o form.o agent.o parser.o 

multimodal.o : Makefile   multimodal.cpp   ../lexing/algorithms.h ../lexing/acceptor.h ../lexing/flatmap.h ../lexing/state.h ../lexing/minmax.h ../lexing/classifier.h ../lexing/stateset.h ../calculator/varstore.h form.h agent.h ../indentation.h ../../easycomp2021b/util/shared_ptr.h parser.h symbol.h tokenizer.h ../filereader.h 
	$(CPP) -c $(Flags) multimodal.cpp -o  multimodal.o


tokenizer.o : Makefile   tokenizer.cpp   code.h ../lexing/generators.h ../indentation.h ../lexing/deterministic.h ../lexing/minimization.h ../lexing/partition.h ../lexing/stateset.h ../lexing/state.h ../lexing/reachableclasses.h ../lexing/algorithms.h ../lexing/acceptor.h ../lexing/flatmap.h ../lexing/minmax.h ../lexing/classifier.h tokenizer.h ../filereader.h symbol.h form.h agent.h ../../easycomp2021b/util/shared_ptr.h 
	$(CPP) -c $(Flags) tokenizer.cpp -o  tokenizer.o


../filereader.o : Makefile   ../filereader.cpp   ../filereader.h 
	$(CPP) -c $(Flags) ../filereader.cpp -o  ../filereader.o


symbol.o : Makefile   symbol.cpp   symbol.h form.h agent.h ../indentation.h ../../easycomp2021b/util/shared_ptr.h 
	$(CPP) -c $(Flags) symbol.cpp -o  symbol.o


../lexing/stateset.o : Makefile   ../lexing/stateset.cpp   ../lexing/stateset.h ../lexing/state.h 
	$(CPP) -c $(Flags) ../lexing/stateset.cpp -o  ../lexing/stateset.o


../lexing/partition.o : Makefile   ../lexing/partition.cpp   ../lexing/partition.h ../lexing/stateset.h ../lexing/state.h 
	$(CPP) -c $(Flags) ../lexing/partition.cpp -o  ../lexing/partition.o


form.o : Makefile   form.cpp   form.h agent.h ../indentation.h ../../easycomp2021b/util/shared_ptr.h 
	$(CPP) -c $(Flags) form.cpp -o  form.o


agent.o : Makefile   agent.cpp   agent.h 
	$(CPP) -c $(Flags) agent.cpp -o  agent.o


parser.o : Makefile   parser.cpp   parser.h symbol.h form.h agent.h ../indentation.h ../../easycomp2021b/util/shared_ptr.h tokenizer.h ../filereader.h ../lexing/classifier.h ../lexing/acceptor.h ../lexing/flatmap.h ../lexing/state.h ../lexing/minmax.h ../calculator/varstore.h 
	$(CPP) -c $(Flags) parser.cpp -o  parser.o


