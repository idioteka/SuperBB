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
        threadDatas[i] = SitesCreationThreadData(i, sites, sizes, wholeGenome);
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

int GenomeIndexer::keyFromKmer(string *wholeGenome, long start, long stop) {
    int key = 0;
    for(long i = start; i < stop; i++) {
        char base = (*wholeGenome)[i];
        int code = baseToCode(base);
        if(code < 0) {
            return -1;
        }
        key = ((key<<2) | code);
    }
    return key;
}

int *readArray(string filename, bool write_sum) {
    FILE * pFile;
    long lSize;
    int * buffer;
    
    pFile = fopen ( filename.c_str() , "rb" );
    
    if(!pFile) {
        cout << "File " << filename << " does not exit. Please create index." << endl;
        exit(-1);
    }
    
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    if(write_sum) {
        key_num = lSize/4;
    }
    rewind (pFile);
    
    // allocate memory to contain the whole file:
    buffer = (int*) malloc (sizeof(char)*lSize);
    
    //cout << "Sizes size: " << lSize << endl;
    
    // copy the file into the buffer:
    fread (buffer,1,lSize,pFile);
    /* the whole file is now loaded in the memory buffer. */
    
    // terminate
    fclose (pFile);
    return buffer;
}

int ** readIndexFromFile(string &whole_genome, string genome_ref, string index_loc, bool part_genome, Config &config) {
    
    KEYLEN = config.KEYLEN;
    KEYSPACE = config.KEYSPACE;
    BUILD_NUMBER = config.BUILD_NUMBER;
    
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    long startday = t1.tv_sec;
    long startday2 = t1.tv_usec;
    extractGenomeFromFile(genome_ref, whole_genome);
    gettimeofday(&t2, NULL);
    long endday = t2.tv_sec;
    long endday2 = t2.tv_usec;
    double timefinal = ((endday - startday) * 1000000.0 + (endday2 - startday2))/ 1000000;
    cout << "Genome read: " << timefinal << " seconds." << endl;
    
    t1, t2;
    gettimeofday(&t1, NULL);
    startday = t1.tv_sec;
    startday2 = t1.tv_usec;
    
    string build = to_string(BUILD_NUMBER);
    string loc = index_loc + "//" + "sizes" + build;
    if(part_genome) {
        loc = index_loc + "//" + "6sizes" + build;
    }
    int *sizes = readArray(loc, false);
    
    gettimeofday(&t2, NULL);
    endday = t2.tv_sec;
    endday2 = t2.tv_usec;
    timefinal = ((endday - startday) * 1000000.0 + (endday2 - startday2))/ 1000000;
    cout << "Sizes loaded: " << timefinal << " seconds." << endl;
    
    gettimeofday(&t1, NULL);
    startday = t1.tv_sec;
    startday2 = t1.tv_usec;
    loc = index_loc + "//" + "sites" + build;
    if(part_genome) {
        loc = index_loc + "//" + "6sites" + build;
    }
    int *sites = readArray(loc, true);
    gettimeofday(&t2, NULL);
    endday = t2.tv_sec;
    endday2 = t2.tv_usec;
    
    timefinal = ((endday - startday) * 1000000.0 + (endday2 - startday2))/ 1000000;
    cout << "Sites loaded: " << timefinal << " seconds." << endl;
    
    int **result = new int*[4];
    result[0] = new int[1];
    result[0][0] = KEYSPACE;
    result[1] = sizes;
    result[2] = new int[1];
    result[2][0] = key_num;
    result[3] = sites;
    return result;
}

