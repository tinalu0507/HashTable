#Yuyang Lu
#yl5pw
CXX=clang++ -Wall -O2
OFILES = hashTable.o timer.o wordPuzzle.o
.SUFFIXES: .o .cpp
wordPuzzle: $(OFILES)
	$(CXX) $(OFILES)
	@echo "Succesful!"
	
clean:
	-rm -f *.o *~  wordPuzzle

hashTable.o: hashTable.cpp hashTable.h
timer.o: timer.cpp timer.h
wordPuzzle.o: wordPuzzle.cpp hashTable.h timer.h