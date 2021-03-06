//
//  Utils.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include "Config.hpp"

using namespace std;

static bool debug = true;

void print(string content);
void debugPrint(string content);

int baseToCode(char base);

int keyspace();

vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

string matchStringToCigarString(string matchString);
string cigarStringToMatchString(string cigarString);
    
#endif /* Utils_hpp */
