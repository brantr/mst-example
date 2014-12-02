EXEC   = test_mst

OPTIMIZE =  -O2 -Wno-write-strings


OBJS   = main.o kdtree2.o spanning_tree.o write_spanning_tree.o rng.o timer.o

##CXX    = mpicxx
##CC     = mpicxx
#CXX    = mpiicpc
#CC     = mpiicpc
CXX    = mpicxx
CC     = mpicxx

INCL   = kdtree2.hpp spanning_tree.hpp spanning_tree_data_types.hpp write_spanning_tree.hpp rng.h timer.h

#LIBS   = -lm -lgsl -lgslcblas -lmpich
LIBS   = -lm -lgsl -lgslcblas -lmpi
#LIBS   = -lm -lgsl -lgslcblas -lmpi++

CFLAGS = $(OPTIMIZE)
CXXFLAGS = $(OPTIMIZE)

$(EXEC): $(OBJS) 
	 $(CXX) $(OBJS) $(LIBS) -o $(EXEC)   
         

$(OBJS): $(INCL) 

.PHONY : clean

clean:
	 rm -f $(OBJS) $(EXEC)

