CXX = g++
CC = gcc

CXXFLAGS =
CFLAGS =
XLIBS = -lX11
LIBS = -lm

TYPE1 = AllFriends
TYPE2 = NotFriends_NoTemplates
TYPE3 = NotFriends_NotMembers
TYPE4 = NotFriends_MostlyMembers

all: $(TYPE1) $(TYPE2) $(TYPE3) $(TYPE4) Other

AllFriends:
	[ -d $(TYPE1) ] || mkdir -p $(TYPE1)
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/testc -I ../$(TYPE1) testc.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/testq -I ../$(TYPE1) testq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/testeq -I ../$(TYPE1) testeq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/testmf -I ../$(TYPE1) testmf.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/testall -I ../$(TYPE1) testall.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/testall2 -I ../$(TYPE1) testall2.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/vgraphl -I ../$(TYPE1) vgraphl.cpp $(XLIBS)
	$(CXX) $(CXXFLAGS) -o $(TYPE1)/qgraphl -I ../$(TYPE1) qgraphl.cpp $(XLIBS)

NotFriends_NoTemplates:
	[ -d $(TYPE2) ] || mkdir -p $(TYPE2)
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/testc -I ../$(TYPE2) testc.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/testq -I ../$(TYPE2) testq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/testeq -I ../$(TYPE2) testeq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/testmf -I ../$(TYPE2) testmf.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/testall -I ../$(TYPE2) testall.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/testall2 -I ../$(TYPE2) testall2.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/vgraphl -I ../$(TYPE2) vgraphl.cpp $(XLIBS)
	$(CXX) $(CXXFLAGS) -o $(TYPE2)/qgraphl -I ../$(TYPE2) qgraphl.cpp $(XLIBS)

NotFriends_NotMembers:
	[ -d $(TYPE3) ] || mkdir -p $(TYPE3)
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/testc -I ../$(TYPE3) testc.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/testq -I ../$(TYPE3) testq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/testeq -I ../$(TYPE3) testeq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/testmf -I ../$(TYPE3) testmf.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/testall -I ../$(TYPE3) testall.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/testall2 -I ../$(TYPE3) testall2.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/vgraphl -I ../$(TYPE3) vgraphl.cpp $(XLIBS)
	$(CXX) $(CXXFLAGS) -o $(TYPE3)/qgraphl -I ../$(TYPE3) qgraphl.cpp $(XLIBS)

NotFriends_MostlyMembers:
	[ -d $(TYPE4) ] || mkdir -p $(TYPE4)
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/testc -I ../$(TYPE4) testc.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/testq -I ../$(TYPE4) testq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/testeq -I ../$(TYPE4) testeq.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/testmf -I ../$(TYPE4) testmf.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/testall -I ../$(TYPE4) testall.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/testall2 -I ../$(TYPE4) testall2.cpp
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/vgraphl -I ../$(TYPE4) vgraphl.cpp $(XLIBS)
	$(CXX) $(CXXFLAGS) -o $(TYPE4)/qgraphl -I ../$(TYPE4) qgraphl.cpp $(XLIBS)

Other:
	$(CXX) $(CXXFLAGS) -o testccc testccc.cpp
	$(CC) $(CFLAGS) -o testcc testcc.c $(LIBS)

clean:
	rm -rI AllFriends NotFriends_NoTemplates NotFriends_NotMembers NotFriends_MostlyMembers testccc testcc
