CPPC		= g++
CPPFLAGS	=-c -O2 -g -B~/source/HCC86/kernel86
MASTER		=-O2 -g -B~/source/HCC86/kernel86 

all:	obj/Main.o obj/ErrorMessage.o obj/Files.o obj/Keywords.o obj/Stack.o obj/StringsHolder.o obj/Vertex.o obj/CompilationStructs.o obj/Generate86.o obj/VarTable.o obj/Lexer.o obj/AstDump.o obj/Parse.o obj/WriteAsm86.o obj/Translate86.o

	$(CPPC) $(MASTER) -O2 obj/Main.o obj/ErrorMessage.o obj/Files.o obj/Keywords.o \
	    obj/Stack.o obj/StringsHolder.o obj/Vertex.o obj/CompilationStructs.o \
		obj/Generate86.o obj/VarTable.o obj/Lexer.o obj/AstDump.o obj/Parse.o obj/WriteAsm86.o obj/Translate86.o -o hcc

asan:	obj/Main.o obj/ErrorMessage.o obj/Files.o obj/Keywords.o obj/Stack.o obj/StringsHolder.o obj/Vertex.o obj/CompilationStructs.o obj/Generate86.o obj/VarTable.o obj/Lexer.o obj/AstDump.o obj/Parse.o obj/WriteAsm86.o obj/Translate86.o

	$(CPPC) $(MASTER) -O2 obj/Main.o obj/ErrorMessage.o obj/Files.o obj/Keywords.o \
	    obj/Stack.o obj/StringsHolder.o obj/Vertex.o obj/CompilationStructs.o \
		obj/Generate86.o obj/VarTable.o obj/Lexer.o obj/AstDump.o obj/Parse.o obj/WriteAsm86.o obj/Translate86.o -o hcc -fsanitize=address

msan:	obj/Main.o obj/ErrorMessage.o obj/Files.o obj/Keywords.o obj/Stack.o obj/StringsHolder.o obj/Vertex.o obj/CompilationStructs.o obj/Generate86.o obj/VarTable.o obj/Lexer.o obj/AstDump.o obj/Parse.o obj/WriteAsm86.o obj/Translate86.o

	$(CPPC) $(MASTER) -O2 obj/Main.o obj/ErrorMessage.o obj/Files.o obj/Keywords.o \
	    obj/Stack.o obj/StringsHolder.o obj/Vertex.o obj/CompilationStructs.o \
		obj/Generate86.o obj/VarTable.o obj/Lexer.o obj/AstDump.o obj/Parse.o obj/WriteAsm86.o obj/Translate86.o -o hcc -fsanitize=memory

recompile: all clean
	echo Recompiled

clean:
	rm obj/Main.o
	rm obj/ErrorMessage.o
	rm obj/Files.o
	rm obj/Keywords.o
	rm obj/Stack.o
	rm obj/StringsHolder.o
	rm obj/Vertex.o
	rm obj/CompilationStructs.o
	rm obj/Generate86.o
	rm obj/VarTable.o
	rm obj/Lexer.o
	rm obj/AstDump.o
	rm obj/Parse.o
	rm obj/WriteAsm86.o
	rm obj/Translate86.o


#------------------------------------------------------

obj/Main.o: Main.cpp
	$(CPPC) $(CPPFLAGS) Main.cpp
	mv Main.o obj

#------------------------------------------------------

obj/ErrorMessage.o: common/ErrorMessage.cpp
	$(CPPC) $(CPPFLAGS) common/ErrorMessage.cpp
	mv ErrorMessage.o obj

obj/Files.o: common/Files.cpp
	$(CPPC) $(CPPFLAGS) common/Files.cpp
	mv Files.o obj

obj/Keywords.o: common/Keywords.cpp
	$(CPPC) $(CPPFLAGS) common/Keywords.cpp
	mv Keywords.o obj

obj/Stack.o: common/Stack.cpp
	$(CPPC) $(CPPFLAGS) common/Stack.cpp
	mv Stack.o obj

obj/StringsHolder.o: common/StringsHolder.cpp
	$(CPPC) $(CPPFLAGS) common/StringsHolder.cpp
	mv StringsHolder.o obj

obj/Vertex.o: common/Vertex.cpp
	$(CPPC) $(CPPFLAGS) common/Vertex.cpp
	mv Vertex.o obj

#------------------------------------------------------

obj/CompilationStructs.o: gen/CompilationStructs.cpp
	$(CPPC) $(CPPFLAGS) gen/CompilationStructs.cpp
	mv CompilationStructs.o obj

obj/Generate86.o: gen/Generate86.cpp
	$(CPPC) $(CPPFLAGS) gen/Generate86.cpp
	mv Generate86.o obj

obj/VarTable.o: gen/VarTable.cpp
	$(CPPC) $(CPPFLAGS) gen/VarTable.cpp
	mv VarTable.o obj

#------------------------------------------------------

obj/Lexer.o: lex/Lexer.cpp
	$(CPPC) $(CPPFLAGS) lex/Lexer.cpp
	mv Lexer.o obj

#------------------------------------------------------

obj/AstDump.o: parser/AstDump.cpp
	$(CPPC) $(CPPFLAGS) parser/AstDump.cpp
	mv AstDump.o obj

obj/Parse.o: parser/Parse.cpp
	$(CPPC) $(CPPFLAGS) parser/Parse.cpp
	mv Parse.o obj

#------------------------------------------------------

obj/WriteAsm86.o: trans/WriteAsm86.cpp
	$(CPPC) $(CPPFLAGS) trans/WriteAsm86.cpp
	mv WriteAsm86.o obj

obj/Translate86.o: trans/Translate86.cpp
	$(CPPC) $(CPPFLAGS) trans/Translate86.cpp
	mv Translate86.o obj

#------------------------------------------------------