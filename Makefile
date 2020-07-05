APP := 				pangolin0.3.0.17
CXX := 				g++-10
BUILDDIR +=			build/
CXXFLAGS += 		$(CXXSTDFLAGS) $(CXXOPTFLAGS) $(CXXLIBFLAGS) $(CXXMACROFLAGS) $(CXXDEBUGFLAGS) $(LINKDIR)
CXXSTDFLAGS +=		-std=c++17
CXXOPTFLAGS +=		-O3 -ffast-math -funroll-loops -flto -finline-functions -fdata-sections -ffunction-sections
CXXLIBFLAGS +=		-ltbb -pthread -lstdc++ -fopenmp -lpthread
CXXMACROFLAGS +=	-D_GLIBCXX_PARALLEL
CXXDEBUGFLAGS +=	-Wall -Wpedantic -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wuseless-cast -Wconversion # -Wsign-conversion
SRCDIR += 			src/
INCLUDEDIR += 		include/
LINKDIR += 			-L/usr/include/ -Iinclude/
ALLFILES +=			$(SRCDIR)main.cpp $(INCLUDEDIR)CheckFile.hpp 	$(INCLUDEDIR)Types.hpp 	$(INCLUDEDIR)CSV.hpp 	$(INCLUDEDIR)NodelistGen.hpp
ALLFILESO +=		$(BUILDDIR)main.o $(BUILDDIR)CheckFile.o 		$(BUILDDIR)Types.o 		$(BUILDDIR)CSV.o 		$(BUILDDIR)NodelistGen.o
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
$(BUILDDIR)NodelistGen.o: $(INCLUDEDIR)NodelistGen.hpp $(INCLUDEDIR)Types.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDEDIR)NodelistGen.hpp -o $(BUILDDIR)NodelistGen.o