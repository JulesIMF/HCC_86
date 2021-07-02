CPPC		= g++
CPPFLAGS	=-c -O2 -g -B~/source/HCC86/core86/backend
MASTER		=-O2 -g -B~/source/HCC86/core86/backend

all: obj/Main.o obj/Lexer.o obj/Parse.o obj/Tree.o obj/AstDump.o
	g++ obj/Main.o ../obj/ErrorMessage.o ../obj/Files.o ../obj/Keywords.o ../obj/Stack.o ../obj/StringsHolder.o ../obj/Vertex.o obj/Lexer.o obj/Parse.o  obj/AstDump.o obj/Tree.o -O2 -o hccfronthcc -g
	mv hccfronthcc ../bin
	
#------------------------------------------------------

obj/Main.o: Main.cpp
	$(CPPC) $(CPPFLAGS) Main.cpp
	mv Main.o obj

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

obj/Tree.o: convert/Tree.cpp
	$(CPPC) $(CPPFLAGS) convert/Tree.cpp
	mv Tree.o obj

#------------------------------------------------------
