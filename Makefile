CXX = g++
CXXFLAGS = -O3 -Wall -std=c++23
LIBGIT = git2
DXG = doxygen
hdr: main.o arg_class.o hash_list.o hamming.o utils.o hdstats.o HDGen.o
	$(CXX) $(CXXFLAGS) main.o arg_class.o hash_list.o hamming.o utils.o hdstats.o HDGen.o -l$(LIBGIT) -o hdr
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
arg_class.o: arg_class.cpp arg_class.h
	$(CXX) -l$(LIBGIT) $(CXXFLAGS) -c arg_class.cpp
hash_list.o: hash_list.cpp hash_list.h
	$(CXX) -l$(LIBGIT) $(CXXFLAGS) -c hash_list.cpp
hamming.o: hamming.cpp hamming.h
	$(CXX) -l$(LIBGIT) $(CXXFLAGS) -c hamming.cpp
utils.o: utils.cpp utils.h
	$(CXX) -l$(LIBGIT) $(CXXFLAGS) -c utils.cpp
hdstats.o: hdstats.cpp hdstats.h
	$(CXX) -l$(LIBGIT) $(CXXFLAGS) -c hdstats.cpp
HDGen.o: HDGen.cpp HDGen.h
	$(CXX) -l$(LIBGIT) $(CXXFLAGS) -c HDGen.cpp
docs: main.cpp arg_class.cpp hash_list.cpp hamming.cpp utils.cpp hdstats.cpp HDGen.cpp
	$(DXG) Doxyfile
clean:
	rm hdr *.o
