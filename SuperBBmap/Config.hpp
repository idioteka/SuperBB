//
//  Config.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

#include <stdio.h>

class Config {
public:
    static Config* instance();
    long keylen;
private:
    Config();
    Config(Config const&);
    void operator=(Config const&);
    static Config* pInstance;
};

#endif /* Config_hpp */
