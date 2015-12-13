//
//  IOManager.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "IOManager.hpp"

string* IOManager::extractGenomeFromFile(string genomeFile) {
    
    string* wholeGenome = new string();
    FILE *inGenome = fopen(genomeFile.c_str(), "r");
    if (inGenome == NULL) {
        print("Reference file does not exist: " + genomeFile);
        exit(-1);
    }
    char buff[256];
    
    while (fgets(buff, 255, inGenome)) {
        // ignore lines that start with genome desc, they start with '>'
        if (buff[0] != '>') {
            string tmp = buff;
            tmp.resize(tmp.size() - 1);  // remove endl
            *wholeGenome += tmp;
        }
    }
    return wholeGenome;
}

void IOManager::writeIndexToFile(GenomeIndex* index) {
    string indexId = Config::instance()->indexId;
    
    string sizesArrayName = GenomeIndex::sizesArrayName;
    string sizesLocation = Config::instance()->outRootDir + "/" + sizesArrayName + indexId;
    writeLongArray(index->sizes, keyspace(), sizesLocation, sizesArrayName);
    
    string sitesArrayName = GenomeIndex::sitesArrayName;
    string sitesLocation = Config::instance()->outRootDir + "/" + sitesArrayName + indexId;
    writeLongArray(index->sizes, index->sitesLength, sitesLocation, sitesArrayName);
}


void IOManager::writeLongArray(long *array, long length, string location, string name) {
    
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    long startday = t1.tv_sec;
    long startday2 = t1.tv_usec;
    
    FILE* pFile;
    pFile = fopen(location.c_str(), "wb");
    fwrite(array, sizeof(long), length, pFile);
    fclose(pFile);
    
    gettimeofday(&t2, NULL);
    long endday = t2.tv_sec;
    long endday2 = t2.tv_usec;
    double timefinal = ((endday - startday) * 1000000.0 + (endday2 - startday2))/ 1000000;
    print("Wrote " + name + ": " + to_string(timefinal));
}

GenomeIndex* IOManager::readIndexFromFile() {
    
    string sizesLocation = Config::instance()->inRootDir + "/" + GenomeIndex::sizesArrayName + Config::instance()->indexId;
    long sizesLength;
    long *sizes = readArray(sizesLocation, GenomeIndex::sizesArrayName, &sizesLength);
    
    string sitesLocation = Config::instance()->inRootDir + "/" + GenomeIndex::sitesArrayName + Config::instance()->indexId;
    long sitesLength;
    long *sites = readArray(sitesLocation, GenomeIndex::sitesArrayName, &sitesLength);
    
    GenomeIndex* index = new GenomeIndex(sizes, sitesLength, sites);
    return index;
}

long* IOManager::readArray(string filename, string name, long* arrayLength) {
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    long startday = t1.tv_sec;
    long startday2 = t1.tv_usec;
    
    FILE* pFile;
    long lSize;
    long* buffer;
    
    pFile = fopen ( filename.c_str() , "rb" );
    
    if(!pFile) {
        print("File" + filename + " does not exist. Please create index.");
        exit(-1);
    }
    
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    
    *arrayLength = lSize/sizeof(long);
    
    rewind (pFile);
    
    // allocate memory to contain the whole file:
    buffer = (long*) malloc (sizeof(char)*lSize);
    
    // copy the file into the buffer:
    fread (buffer,1,lSize,pFile);
    /* the whole file is now loaded in the memory buffer. */
    
    // terminate
    fclose (pFile);
    
    gettimeofday(&t2, NULL);
    long endday = t2.tv_sec;
    long endday2 = t2.tv_usec;
    double timefinal = ((endday - startday) * 1000000.0 + (endday2 - startday2))/ 1000000;
    print(name + " loaded: " + to_string(timefinal) + " seconds");
    
    return buffer;
}

vector<Read>* IOManager::readReadsFromBBFormat(string filename) {
    ifstream ifs(filename.c_str());
    vector<Read>* reads = new vector<Read>();
    if(!ifs) {
        print("File" + filename + " does not exist");
        exit(-1);
    }
    string line;
    int br = 0;
    while(getline(ifs, line)) {
        vector<string> lines = split(line, '\t');
        string readId = to_string(br);
        string name = lines[0];
        long start = atol(lines[1].c_str());
        long stop = atol(lines[2].c_str());
        string cigarString = lines[3];
        vector<long> gapArray = gapArrayFromString(lines[4]);
        string readContent = lines[5];
        CorrectAlignment* correctAlignment = new CorrectAlignment(start, stop, cigarString, gapArray);
        Read read = Read(br, readContent, name, correctAlignment);
        reads->push_back(read);
        br++;
    }
    return reads;
}

vector<long> gapArrayFromString(string str) {
    vector<long> gapArray;
    char delimiterMain = ' ';
    char delimiterSecondary = '-';
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiterMain)) {
        if(item[item.size()-1] == ',') {
            item.erase(item.size()-1);
        }
        stringstream ss2(item);
        string firstElement;
        string secondElement;
        getline(ss2, firstElement, delimiterSecondary);
        getline(ss2, secondElement, delimiterSecondary);
        gapArray.push_back(atoi(firstElement.c_str()));
        gapArray.push_back(atoi(secondElement.c_str()));
    }
    return gapArray;
}

vector<Read>* readReadsFromFastaFormat(string filename) {
    vector<Read>* reads = new vector<Read>();
    ifstream ifs(filename.c_str());
    if(!ifs) {
        print("File" + filename + " does not exist");
        exit(-1);
    }
    string nameLine;
    string contentLine;
    int br = 0;
    while(getline(ifs, nameLine)) {
        getline(ifs, contentLine);
        Read read = Read(br, contentLine, nameLine, NULL);
        reads->push_back(read);
        br++;
    }
    return reads;
}

void writeAlignmentsInBBOFormat(vector<Alignment> alignments, string outfile) {
    ofstream out(outfile.c_str());
    for(unsigned int i = 0; i < alignments.size(); i++) {
        Alignment alignment = alignments[i];
        Read* read = alignment.read;
        CorrectAlignment* correctAlignment = read->correctAlignment;
        
        out << read->id << endl;
        
        if (correctAlignment != NULL) {
            out << correctAlignment->start << "-";
            out << correctAlignment->stop << "-";
            out << (correctAlignment->stop - correctAlignment->start) << endl;
        } else {
            cout << endl;
        }
        
        out << alignment.start << "-";
        out << alignment.stop << "-";
        out << (alignment.stop - alignment.start) << endl;
        if (correctAlignment != NULL) {
            for (unsigned long j = 0; j < correctAlignment->gapArray.size(); j+=2) {
                out << correctAlignment->gapArray[j] << "-" << correctAlignment->gapArray[j+1] << ", ";
            }
        } else {
            out << endl;
        }
        
        for (unsigned long j = 0; j < alignment.gapArray.size(); j+=2) {
            out << alignment.gapArray[j] << "-" << alignment.gapArray[j+1] << ", ";
        }
    }
    out.close();
}

void writeResultsInSamFormat(vector<Alignment> alignments, string outfile) {
    ofstream out(outfile.c_str());
    for(unsigned int i = 0; i < alignments.size(); i++) {
        Alignment alignment = alignments[i];
        Read* read = alignment.read;
        
        out << read->name << "\t";
        
        for(unsigned long j = 0; j < alignment.gapArray.size(); j+=2) {
            out << alignment.gapArray[j] << "-" << alignment.gapArray[j+1];
            if(j+2 != alignment.gapArray.size()) out << ",";
        }
        out << "\t";
        out << "0\t";
        out << "\t";
        out << alignment.start << "\t";
        out << "*\t";
        out << matchStringToCigarString(alignment.matchString) << "\t";
        out << "*\t";
        out << "0\t";
        out << "0\t";
        out << read->content << "\n";
        out << "*\t";
        out << "*\t";
        out << "\n";
    }
}



