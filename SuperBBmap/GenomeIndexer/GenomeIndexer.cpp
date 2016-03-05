//
//  GenomeIndexer.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "GenomeIndexer.hpp"

struct SizesCreationThreadData {
    int threadId;
    long* sizes;
    string* wholeGenome;
    SizesCreationThreadData() {
    }
    SizesCreationThreadData(int _threadId, long* _sizes, string* _wholeGenome) {
        threadId = _threadId;
        sizes = _sizes;
        wholeGenome = _wholeGenome;
    }
};

struct SitesCreationThreadData {
    int threadId;
    long* sizes;
    long* sites;
    string* wholeGenome;
    SitesCreationThreadData() {
    }
    SitesCreationThreadData(int _threadId, long *_sizes, long *_sites, string* _wholeGenome) {
        threadId = _threadId;
        sizes = _sizes;
        sites = _sites;
        wholeGenome = _wholeGenome;
    }
};

GenomeIndex* GenomeIndexer::createIndex(string *wholeGenome) {
    long* sizes = createSizes(wholeGenome);
    long sum = transformAndSumSizes(sizes);
    
    long* sites = createSites(wholeGenome, sizes, sum);
    
    for(int i = keyspace()-1; i > 0; i--) {
        sizes[i] = sizes[i-1];
    }
    sizes[0] = 0;
    
    GenomeIndex* index = new GenomeIndex(sizes, sum, sites);
    return index;
}

long* GenomeIndexer::createSizes(string *wholeGenome) {
    int numberOfThreads = 4;
    
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    long startday = t1.tv_sec;
    long startday2 = t1.tv_usec;
    
    pthread_t threads[numberOfThreads];
    long *sizes = new long[keyspace()] {0};
    
    int rc;
    pthread_attr_t attr;
    void *status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    SizesCreationThreadData threadDatas[4];
    
    for(int i = 0; i < numberOfThreads; i++) {
        threadDatas[i] = SizesCreationThreadData(i, sizes, wholeGenome);
    }
    
    for(int i = 0; i < numberOfThreads; i++) {
        rc = pthread_create(&threads[i], NULL, countKeys, (void *)&threadDatas[i]);
    }
    pthread_attr_destroy(&attr);
    
    for(int i=0; i < numberOfThreads; i++){
        rc = pthread_join(threads[i], &status);
        if (rc){
            print("Error:unable to join," + to_string(rc));
            exit(-1);
        }
        print("Main: completed thread id :" + to_string(i));
    }
    
    gettimeofday(&t2, NULL);
    long endday = t2.tv_sec;
    long endday2 = t2.tv_usec;
    
    double timefinal = ((endday - startday) * 1000000.0 + (endday2 - startday2))/ 1000000;
    print("Created sizes: " + to_string(timefinal));
    return sizes;
}

long GenomeIndexer::transformAndSumSizes(long* sizes) {
    long sum=0;
    for(int i = 0; i < keyspace(); i++) {
        long tmp = sizes[i];
        sizes[i] = sum;
        sum += tmp;
    }
    return sum;
}

long* GenomeIndexer::createSites(string* wholeGenome, long* sizes, long sum) {
    int numberOfThreads = 4;
    
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    long startday = t1.tv_sec;
    long startday2 = t1.tv_usec;
    
    pthread_t threads[numberOfThreads];
    long *sites = new long[sum];
    
    int rc;
    pthread_attr_t attr;
    void *status;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    SitesCreationThreadData threadDatas[4];
    
    for(int i = 0; i < numberOfThreads; i++) {
        threadDatas[i] = SitesCreationThreadData(i, sizes, sites, wholeGenome);
    }
    
    for(int i = 0; i < numberOfThreads; i++) {
        rc = pthread_create(&threads[i], NULL, fillSites, (void *)&threadDatas[i]);
    }
    pthread_attr_destroy(&attr);
    
    for(int i=0; i < numberOfThreads; i++ ){
        rc = pthread_join(threads[i], &status);
        if (rc){
            print("Error:unable to join," + to_string(rc));
            exit(-1);
        }
        print("Main: completed thread id :" + to_string(i));
    }
    
    gettimeofday(&t2, NULL);
    long endday = t2.tv_sec;
    long endday2 = t2.tv_usec;
    double timefinal = ((endday - startday) * 1000000.0 + (endday2 - startday2))/ 1000000;
    print("Created sites: " + to_string(timefinal));
    return sites;
}

void* GenomeIndexer::countKeys(void *threadid) {
    SizesCreationThreadData *td = (SizesCreationThreadData *) threadid;
    string* wholeGenome = td->wholeGenome;
    int threadId = td->threadId;
    long* sizes = td->sizes;
    Config* config = Config::instance();
    
    unsigned long start = 0;
    while (baseToCode((*wholeGenome)[start]) < 0) {
        start++;
    }
    
    for(unsigned long i = start; i < ((*wholeGenome).size() - (config->keylen-1)); i++) {
        if(baseToCode((*wholeGenome)[i]) == threadId) {
            int code = baseToCode((*wholeGenome)[i]);
            if(code >= 0) {
                int key = keyFromKmer(wholeGenome, i, i+config->keylen);
                if(key >= 0) {
                    sizes[key]++;
                }
            }
        }
    }
    pthread_exit(NULL);
}


void* GenomeIndexer::fillSites(void *threadid) {
    SitesCreationThreadData *td = (SitesCreationThreadData *) threadid;
    unsigned long start = 0;
    string* wholeGenome = td->wholeGenome;
    int threadId = td->threadId;
    long* sizes = td->sizes;
    long* sites = td->sites;
    Config* config = Config::instance();
    
    while(baseToCode((*wholeGenome)[start]) < 0) {
        start++;
    }
    
    for(unsigned long i = start; i < (*wholeGenome).size()-(config->keylen-1); i++) {
        int code = baseToCode((*wholeGenome)[i]);
        if(code == threadId) {
            if(code >= 0) {
                int key = keyFromKmer(wholeGenome, i, i+config->keylen);
                if(key >= 0) {
                    long location = sizes[key];
                    sites[location] = i;
                    sizes[key]++;
                }
            }
        }
    }
    pthread_exit(NULL);
}
