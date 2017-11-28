/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/**
 * Service_subscriber.hpp
 *
 * ShapeType subscriber service interface.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
*/

#ifndef SERVICE_SUBSCRIBER_HPP_
#define SERVICE_SUBSCRIBER_HPP_

#include "Service.hpp"

#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
#include "ShapeType.hpp"

class Service_subscriber: public Service {
public:
	Service_subscriber(const std::string& reader_name);

	virtual void init(dds::domain::DomainParticipant participant);

	virtual void execute(int count); /* called inside the loop() */

private:
	const std::string reader_name_;
    dds::sub::DataReader<rti::example::ShapeType> reader_;
    dds::core::cond::WaitSet waitset_;
};

#endif /* SERVICE_SUBSCRIBER_HPP_ */
