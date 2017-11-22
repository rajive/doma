/**
 * Service_publisher.hpp
 *
 * ShapeType publisher service interface.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
*/

#ifndef SRC_C__11_SERVICE_PUBLISHER_HPP_
#define SRC_C__11_SERVICE_PUBLISHER_HPP_

#include "Service.hpp"

#include <dds/pub/ddspub.hpp>

#include "ShapeType.hpp"

class Service_publisher: public Service {
public:
	Service_publisher(const std::string& writer_name);

	virtual void init(dds::domain::DomainParticipant participant);

	virtual void execute(int count); /* called inside the loop() */

private:
	const std::string writer_name_;
	dds::pub::DataWriter<rti::example::ShapeType> writer_;
    rti::example::ShapeType sample_;
};

#endif /* SRC_C__11_SERVICE_PUBLISHER_HPP_ */
