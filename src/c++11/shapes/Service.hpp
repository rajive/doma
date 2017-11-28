/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/**
 * Service.hpp
 *
 * A service interface.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
 */


#ifndef SERVICE_HPP_
#define SERVICE_HPP_

#include <dds/domain/DomainParticipant.hpp>

class Service {
public:
	/**
	 * Initialize the service, given a fully instantiated
	 * DomainParticipant containing the known endpoints
	 */
	virtual void init(dds::domain::DomainParticipant participant) = 0;

	/**
	 * Work to be done inside the loop
	 * count - the current counter; automatically incremented
	 * 		   every time execute is called
	 */
	virtual void execute(int count) = 0; /* called inside the loop() */

	/**
	 * The main execution loop. Calls execute() count times.
	 * The special value of count = 0 is interpreted as an infinite
	 * loop.
	 *
	 * Default implementation calls execute() and increments a counter.
	 */
	virtual void loop(int count = 0 /* forever */);

	/**
	 * Destroy the service
	 */
	virtual ~Service();
};

#endif /* SERVICE_HPP_ */
