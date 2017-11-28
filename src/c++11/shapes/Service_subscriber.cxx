/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/**
 * Service_subscriber.cxx
 *
 * ShapeType subscriber service implementation.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
*/

#include <algorithm>
#include <iostream>

#include <dds/core/QosProvider.hpp>
#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
#include "Service_subscriber.hpp"
// Or simply include <dds/dds.hpp> 

#include "Service_subscriber.hpp"

Service_subscriber::Service_subscriber(const std::string& reader_name)
	: reader_name_(reader_name), reader_(dds::core::null)
{
}

void Service_subscriber::init(dds::domain::DomainParticipant participant)
{
    // Lookup DataReader
	reader_ = rti::sub::find_datareader_by_name<
				dds::sub::DataReader<rti::example::ShapeType> >(
					participant, reader_name_);

    // Create a ReadCondition for any data on this reader and associate a handler
    dds::sub::cond::ReadCondition read_condition(
        reader_,
        dds::sub::status::DataState::any(),
        [this]()
    {
        // Take all samples
        dds::sub::LoanedSamples<rti::example::ShapeType> samples =
        									this->reader_.take();
        for (auto sample : samples){
            if (sample.info().valid()){
                std::cout << sample.data() << std::endl; 
            }   
        }

    } // The LoanedSamples destructor returns the loan
    );

    // Create a WaitSet and attach the ReadCondition
    waitset_ += read_condition;
}

void Service_subscriber::execute(int count)
{
	// Dispatch will call the handlers associated to the WaitSet conditions
	// when they activate
	std::cout << "ShapeType subscriber sleeping for 4 sec..." << std::endl;

	waitset_.dispatch(dds::core::Duration(4)); // Wait up to 4s each time
}
