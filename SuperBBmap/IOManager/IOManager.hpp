//
//  IOManager.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef IOManager_hpp
#define IOManager_hpp

#include "Utils.hpp"
#include "GenomeIndex.hpp"
#include "Read.hpp"
#include "Alignment.hpp"

using namespace std;

// class that handles I/O operations of genome, reads, results and statistics
class IOManager {
public:
    // GENOME INDEX METHODS
    // reads genome string from file
    static string* extractGenomeFromFile(string genomeFile);
    // writes created genome index to file
    static void writeIndexToFile(GenomeIndex* index);
    // reads created genome index from file
    static GenomeIndex* readIndexFromFile();
    
    // READS METHODS
    // reads reads from file in BB format
    static vector<Read*>* readReadsFromBBFormat(string filename);
    // reads reads from file in Fasta formatx
    static vector<Read*>* readReadsFromFastaFormat(string filename);
    static void writeAlignmentsInBBFormat(vector<Alignment> alignments, string outfile);
    static void writeResultsInSamFormat(vector<Alignment> alignments, string outfile);
private:
    // GENOME INDEX METHODS
    static void writeLongArray(long* array, long length, string location, string name);
    static long* readLongArray(string filename, string name, long* arrayLength);
    
    // READS METHODS
    // parses gap array
    static vector<long> gapArrayFromString(string str);
};

#endif /* IOManager_hpp */
