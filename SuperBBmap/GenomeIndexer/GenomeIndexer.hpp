//
//  GenomeIndexer.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef GenomeIndexer_hpp
#define GenomeIndexer_hpp

#include "Utils.hpp"
#include "Config.hpp"
#include "GenomeIndex.hpp"

using namespace std;

class GenomeIndexer {
public:
    static GenomeIndex* createIndex(string *wholeGenome);
private:
    static long* createSizes(string *wholeGenome);
    static long transformAndSumSizes(long* sizes);
    static long* createSites(string* wholeGenome, long* sizes, long sum);
    static void* countKeys(void *threadid);
    static void* fillSites(void *threadid);
    static int keyFromKmer(string *wholeGenome, long start, long stop);
};

#endif /* GenomeIndexer_hpp */
