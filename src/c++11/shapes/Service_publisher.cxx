/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/**
 * Service_publisher.cxx
 *
 * ShapeType publisher service implementation.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
*/

#include <iostream>

#include <dds/pub/ddspub.hpp>
#include <rti/util/util.hpp> // for sleep()

#include "Service_publisher.hpp"

Service_publisher::Service_publisher(const std::string& writer_name)
	: writer_name_(writer_name), writer_(dds::core::null)
{
}

void Service_publisher::init(dds::domain::DomainParticipant participant)
{
    // Lookup DataWriter
    writer_ = rti::pub::find_datawriter_by_name<
				dds::pub::DataWriter<rti::example::ShapeType> >(
						participant, writer_name_);

	sample_.color("YELLOW");
}

void Service_publisher::execute(int count)
{
	// Modify the data to be written here
	sample_.x(20 + (count*10) % 230);
	sample_.y(20 + (count*10) % 230);
	sample_.shapesize(40);

	std::cout << "Writing ShapeType, count " << count << std::endl;
	writer_.write(sample_);

	rti::util::sleep(dds::core::Duration(4));
}
