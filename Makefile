APP := 				pangolin0.3.2.17
CXX := 				g++-10
# CXX := 			clang++-10
BUILDDIR +=			build/
CXXFLAGS += 		$(CXXSTDFLAGS) $(CXXOPTFLAGS) $(CXXLIBFLAGS) $(CXXMACROFLAGS) $(CXXDEBUGFLAGS) $(LINKDIR)
CXXSTDFLAGS +=		-std=c++17
CXXOPTFLAGS +=		-Ofast -march=native # -fprofile-use #3 -fpermissive
CXXLIBFLAGS +=		-lstdc++ -ltbb -pthread -lpthread -fopenmp
CXXMACROFLAGS +=	-D_GLIBCXX_PARALLEL
CXXDEBUGFLAGS +=	-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wuseless-cast -Wconversion -Wpessimizing-move -Wredundant-move -Wunused -Wsign-conversion # -Wpedantic 
SRCDIR += 			src/
INCLUDEDIR += 		include/
LINKDIR += 			-L/usr/include/ -Iinclude/ -L/usr/include/c++/10/
ALLFILES +=			$(SRCDIR)main.cpp $(INCLUDEDIR)Types.hpp 	$(INCLUDEDIR)CheckFile.hpp	$(INCLUDEDIR)CSV.hpp 	$(INCLUDEDIR)GenNodelist.hpp	$(INCLUDEDIR)GenAlters.hpp	$(INCLUDEDIR)Degree.hpp	$(INCLUDEDIR)TriadGen.hpp	$(INCLUDEDIR)GenCliques.hpp $(INCLUDEDIR)PrestigeSimple.hpp
ALLFILESO +=		$(BUILDDIR)main.o $(BUILDDIR)Types.o 		$(BUILDDIR)CheckFile.o 		$(BUILDDIR)CSV.o 		$(BUILDDIR)GenNodelist.o		$(BUILDDIR)GenAlters.o		$(BUILDDIR)Degree.o		$(BUILDDIR)TriadGen.o		$(BUILDDIR)GenCliques.o		$(BUILDDIR)PrestigeSimple.o

$(APP): $(ALLFILESO)
	$(CXX) $(CXXFLAGS) $(BUILDDIR)main.o -o $(APP)

$(BUILDDIR)main.o: $(ALLFILES)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)main.cpp -o $(BUILDDIR)main.o 

$(BUILDDIR)Types.o: $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)Types.hpp -o $(BUILDDIR)Types.o

$(BUILDDIR)CheckFile.o: $(INCLUDEDIR)CheckFile.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)CheckFile.hpp -o $(BUILDDIR)CheckFile.o

$(BUILDDIR)CSV.o: $(INCLUDEDIR)CSV.hpp $(INCLUDEDIR)CheckFile.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)CSV.hpp -o $(BUILDDIR)CSV.o

$(BUILDDIR)GenNodelist.o: $(INCLUDEDIR)GenNodelist.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)GenNodelist.hpp -o $(BUILDDIR)GenNodelist.o

$(BUILDDIR)Degree.o: $(INCLUDEDIR)Degree.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)Degree.hpp -o $(BUILDDIR)Degree.o

$(BUILDDIR)GenAlters.o: $(INCLUDEDIR)GenAlters.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)GenAlters.hpp -o $(BUILDDIR)GenAlters.o

$(BUILDDIR)GenCliques.o: $(INCLUDEDIR)GenCliques.hpp $(INCLUDEDIR)Types.hpp $(INCLUDEDIR)GenAlters.hpp 
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)GenCliques.hpp -o $(BUILDDIR)GenCliques.o

$(BUILDDIR)TriadGen.o: $(INCLUDEDIR)TriadGen.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)TriadGen.hpp -o $(BUILDDIR)TriadGen.o

$(BUILDDIR)PrestigeSimple.o: $(INCLUDEDIR)PrestigeSimple.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)PrestigeSimple.hpp -o $(BUILDDIR)PrestigeSimple.o