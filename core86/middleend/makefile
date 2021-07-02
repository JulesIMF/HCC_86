CPPC		= g++
CPPFLAGS	=-c -O2 -g -B~/source/HCC86/core86/backend
MASTER		=-O2 -g -B~/source/HCC86/core86/backend

all: Main.o Convolute.o Tree.o
	$(CPPC) $(MASTER) Main.o Convolute.o Tree.o ../obj/Vertex.o ../obj/ErrorMessage.o ../obj/StringsHolder.o -o hccmiddle
	mv hccmiddle ../bin