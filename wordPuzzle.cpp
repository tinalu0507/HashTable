//Yuyang Lu
//yl5pw
//3.17.2016
//wordPuzzle.cpp
//Big Theta (n) linear time

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "hashTable.h"
#include "timer.h"

using namespace std;

// We create a 2-D array of some big size, and assume that the table
// read in will be less than this size (a valid assumption for lab 6)
#define MAXROWS 500
#define MAXCOLS 500
char table[MAXROWS][MAXCOLS];

// Forward declarations
bool readInTable (string filename, int &rows, int &cols);
char* getWordInTable (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols);
int getNextPrime(unsigned int n);

int main(int argc, char* argv[]) {
	string dictionary = argv[1];
	string grid = argv[2];
    string word;
    int MAXLENGTH = 0;
    int numLines = 0;
    string line;
    ifstream aFile(dictionary.c_str());
    while (getline(aFile, line))
        ++numLines;
    int size = getNextPrime(numLines*10);
    hashTable h(size);
	ifstream fin(dictionary.c_str());
	//if (!fin)
		//return false;
	while (fin >> word) {
        if (word.length() > MAXLENGTH)
            MAXLENGTH = word.length();
		h.insert(word);
        if (word.length() >= 3) {
            for (int i = 3; i <= word.length(); i++) {
                h.insert(word.substr(0,i)+".");
            }
        }
        numLines++;
	}
    // to hold the number of rows and cols in the input file
    int rows, cols;
    // attempt to read in the file
    bool result = readInTable (grid, rows, cols);

    // if there is an error, report it
    if ( !result ) {
        cout << "Error reading in file!" << endl;
        exit(1); // requires the <stdlib.h> #include header!
    }
    // Get a word (of length 10), starting at position (2,2) in the
    // array, in each of the 8 directions
    //cout << endl;
    int num_wordsFound = 0;
    timer t;
    t.start();
    vector<string> wordsFound;
    for (int row = 0; row < rows; row++) {
    	for (int col = 0; col < cols; col++) {
    		for (int dir = 0; dir < 8; dir++) {
                for (int length = 3; length <= MAXLENGTH; length++) {
                	string word = getWordInTable(row,col,dir,length,rows,cols);
                    if (word.length() < length) {
                        break;
                    }
                    if (!h.find(word+"."))
                        break;
                	if (h.find(word)) {
                        string dirPrint;
                		if (dir == 0) {
                			dirPrint = "N ";
                		}
                        if (dir == 1) {
                            dirPrint = "NE";
                        }
                        if (dir == 2) {
                            dirPrint = "E ";
                        }
                        if (dir == 3) {
                            dirPrint = "SE";
                        }
                        if (dir == 4) {
                            dirPrint = "S ";
                        }
                        if (dir == 5) {
                            dirPrint = "SW";
                        }
                        if (dir == 6) {
                            dirPrint = "W ";
                        }
                        if (dir == 7) {
                            dirPrint = "NW";
                        }
                        num_wordsFound++;
                        //cout << "(" << row << ", " << col << ")" << ":    " << word << endl;
                        ostringstream convert1;
                        convert1 << row;
                        string rowPrint = convert1.str();
                        ostringstream convert2;
                        convert2 << col;
                        string colPrint = convert2.str();
                        string output = dirPrint+"("+rowPrint+","+colPrint+"):   "+word;
                        wordsFound.push_back(output);
                    }
        		}
            }
    	}
    }
    t.stop();
    for (int i = 0; i < wordsFound.size(); i++) {
        cout << wordsFound[i] << endl;
    }
    cout << num_wordsFound << " words found" << endl;
    cout << "Found all words in " << t.getTime() << " seconds" << endl;
    cout << (int)(t.getTime()*1000) << endl;
    // All done!
    //delete h;
    return 0;
}

bool readInTable (string filename, int &rows, int &cols) {
    // a C++ string to hold the line of data that is read in
    string line;
    // set up the file stream to read in the file (takes in a C-style
    // char* string, not a C++ string object)
    ifstream file(filename.c_str());
    // upon an error, return false
    if ( !file.is_open() )
        return false;
    // the first line is the number of rows: read it in
    file >> rows;
    //cout << "There are " << rows << " rows." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the second line is the number of cols: read it in and parse it
    file >> cols;
    //cout << "There are " << cols << " cols." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the third and last line is the data: read it in
    getline (file,line);
    // close the file
    file.close();
    // convert the string read in to the 2-D grid format into the
    // table[][] array.  In the process, we'll print the table to the
    // screen as well.
    int pos = 0; // the current position in the input data
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            table[r][c] = line[pos++];
            //cout << table[r][c];
        }
        //cout << endl;
    }
    // return success!
    return true;
}


char* getWordInTable (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocataion.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static char output[256];
    // make sure the length is not greater than the array size.
    if ( len >= 255 )
        len = 255;
    // the position in the output array, the current row, and the
    // current column
    int pos = 0, r = startRow, c = startCol;
    // iterate once for each character in the output
    for ( int i = 0; i < len; i++ ) {
        // if the current row or column is out of bounds, then break
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        // set the next character in the output array to the next letter
        // in the table
        output[pos++] = table[r][c];
        // move in the direction specified by the parameter
        switch (dir) { // assumes table[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    // set the next character to zero (end-of-string)
    output[pos] = 0;
    // return the string (a C-style char* string, not a C++ string
    // object)
    return output;
}

bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}
