//
//  GenomeIndexer.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef GenomeIndexer_hpp
#define GenomeIndexer_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "Utils.hpp"
#include "Config.hpp"
#include "GenomeIndex.hpp"

using namespace std;

class GenomeIndexer {
public:
    static GenomeIndex* createIndex(string *wholeGenome);
private:
    static int keyFromKmer(string *wholeGenome, long start, long stop);
    static void* countKeys(void *threadid);
    static long* createSizes(string *wholeGenome);
    static long transformAndSumSizes(long* sizes);
    static long* createSites(string* wholeGenome, long* sizes, long sum);
    static void* fillSites(void *threadid);
};



#endif /* GenomeIndexer_hpp */
