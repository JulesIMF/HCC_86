CPPC		= g++
CPPFLAGS	=-c -O2 -g -B~/source/HCC86/core86/backend
MASTER		=-O2 -g -B~/source/HCC86/core86/backend

all: obj/Main.o obj/CompilationStructs.o obj/Generate86.o obj/VarTable.o obj/AstDump.o obj/WriteAsm86.o obj/Translate86.o obj/Tree.o obj/AstDump.o
	g++ obj/Main.o ../obj/ErrorMessage.o ../obj/Files.o ../obj/Keywords.o ../obj/Stack.o ../obj/StringsHolder.o ../obj/Vertex.o obj/CompilationStructs.o obj/Generate86.o obj/VarTable.o obj/AstDump.o obj/WriteAsm86.o obj/Translate86.o obj/Tree.o -O2 -o hccback86 -g
	mv hccback86 ../bin

#------------------------------------------------------

obj/Main.o: Main.cpp
	$(CPPC) $(CPPFLAGS) Main.cpp
	mv Main.o obj

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

obj/AstDump.o: convert/AstDump.cpp
	$(CPPC) $(CPPFLAGS) convert/AstDump.cpp
	mv AstDump.o obj

obj/Tree.o: convert/Tree.cpp
	$(CPPC) $(CPPFLAGS) convert/Tree.cpp
	mv Tree.o obj

#------------------------------------------------------

obj/WriteAsm86.o: trans/WriteAsm86.cpp
	$(CPPC) $(CPPFLAGS) trans/WriteAsm86.cpp
	mv WriteAsm86.o obj

obj/Translate86.o: trans/Translate86.cpp
	$(CPPC) $(CPPFLAGS) trans/Translate86.cpp
	mv Translate86.o obj

#------------------------------------------------------