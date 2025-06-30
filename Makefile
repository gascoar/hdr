CXX = g++
CXXFLAGS = -O3 -Wall -std=c++23
LIBGIT = git2
DXG = doxygen
hdr: main.cpp arg_class.h hash_list.h hamming.h utils.h hdstats.h
	clear
	$(CXX) main.cpp -o hdr -l$(LIBGIT) $(CXXFLAGS)
docs: main.cpp arg_class.h hash_list.h hamming.h utils.h hdstats.h
	$(DXG) Doxyfile
clean:
	rm hdr
