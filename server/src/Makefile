CXXFLAGS= -std=c++11 -Wall -g -march=native -O3
TARGETOS= $(shell uname -s)

ifeq ($(TARGETOS), Darwin)
    LIBS=-losmpbf -lprotobuf -lz -pthread  -lboost_thread-mt -lboost_system -lboost_filesystem -lssl -lcrypto 
	MACLIB=-L /usr/local/opt/openssl/lib
	MACINC=-I /usr/local/opt/openssl/include
else 
    LIBS=-losmpbf -lprotobuf -lz -lpthread -pthread -lboost_thread -lboost_system -lboost_filesystem -lssl -lcrypto
endif

LIB=-L ./../libs/osmpbf/build/osmpbf/ 
INC=-I ./include/ -I ../libs/osmpbf/osmpbf/include -I ../libs/osmpbf -I ./ -I ../libs/Simple-Web-Server/ 
#INC_DEBUG=-I ./include/ -I ../libs/osmpbf/osmpbf/include -I ../libs/osmpbf -I ./
#LIBS_DEBUG=-losmpbf -lprotobuf -lz 


default:
	rm -f main.out
	g++ $(CXXFLAGS) $(INC) $(MACINC) $(LIB) $(MACLIB) main.cpp graphreader.cpp edge.cpp node.cpp webserver.cpp search.cpp $(LIBS) -o main.out