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
