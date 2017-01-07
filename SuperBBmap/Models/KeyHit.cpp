//
//  KeyHit.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 07/01/2017.
//  Copyright © 2017 Josip Maric. All rights reserved.
//

#include "KeyHit.hpp"

long KeyHit::keyHitSite() {
    return location - offset;
}
