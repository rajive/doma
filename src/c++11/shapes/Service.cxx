/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/**
 * Service.cxx
 *
 * A service implementation.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
 */


#include "Service.hpp"

Service::~Service() {}

void Service::loop(int count /* 0 = forever */)
{
    for (int i = 0; i < count || count == 0; i++) {
    		execute(i);
    }
}
