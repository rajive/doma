/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/**
 * Component.cxx
 *
 * A component implementation. This is based on the auto-generated
 * example from rtiddsgen.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
 */

#include "Component.hpp"

Component::~Component() {}

int Component::main(int argc, char *argv[],
					const std::string & participant_config_name,
					Service& service)
{

    int domain_id = 0;
    int sample_count = 0; // infinite loop

    if (argc >= 2) {
        domain_id = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    // To turn on additional logging, include <rti/config/Logger.hpp> and
    // uncomment the following line:
    // rti::config::Logger::instance().verbosity(rti::config::Verbosity::STATUS_ALL);

	// register all the compiled types before creating a participant
	this->register_types();

    // Create a DomainParticipant from the named configuration
    rti::domain::DomainParticipantConfigParams params(domain_id);
	dds::domain::DomainParticipant participant =
	 dds::core::QosProvider::Default()->create_participant_from_config(
	        		participant_config_name, params);
    try {
    	service.init(participant);
        service.loop(sample_count);
    } catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in component main(): " << ex.what() << std::endl;
        return -1;
    }

    // RTI Connext provides a finalize_participant_factory() method
    // if you want to release memory used by the participant factory singleton.
    // Uncomment the following line to release the singleton:
    //
    // dds::domain::DomainParticipant::finalize_participant_factory();

    return 0;
}

