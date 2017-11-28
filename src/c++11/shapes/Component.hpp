/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/**
 * Component.hpp
 *
 * A component interface.
 *
 * Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <dds/core/QosProvider.hpp>

#include "Service.hpp"

class Component {
public:
	/**
	 * Register the compiled types for XML App Creation
	 */
	virtual void register_types() = 0;

	/**
	 * Create a participant with the name "participant_config_name",
	 * initialize the service using that participant, and run the
	 * service main loop.
	 *
	 * Default implementation matches that of rtiddsgen
	 * auto-generated code.
	 */
	virtual int main(int argc, char *argv[],
			 	 	 const std::string & participant_config_name,
					 Service& service);

	/**
	 * Destroy the component
	 */
	virtual ~Component();
};

#endif /* COMPONENT_HPP_ */
