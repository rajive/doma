/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/* Component_square_pubsub.cxx

Service composition example. This component implements a service that
is a composition of two other services:

- a service that publishes Squares
- a service that subscribes to Squares

*/


#include <iostream>

#include <dds/pub/ddspub.hpp>

#include "Component.hpp"
#include "Service_subscriber.hpp"
#include "Service_publisher.hpp"

#include "ShapeType.hpp"

class Service_pubsub : public Service {
public:
	Service_pubsub(Service_publisher& publisher,
				  Service_subscriber& subscriber)
	: publisher_(publisher),
	  subscriber_(subscriber) {
	}

	virtual void init(dds::domain::DomainParticipant participant) {
		publisher_.init(participant);
		subscriber_.init(participant);
	}

	virtual void execute(int count) {
		publisher_.execute(count);
		subscriber_.execute(count);
	}

private:
	Service_publisher& publisher_;
	Service_subscriber& subscriber_;
};

class Component_pubsub : public Component {
public:
	virtual void register_types() {
		rti::domain::register_type<rti::example::ShapeType>("ShapeType");
	}
};

int main(int argc, char *argv[])
{
	return Component_pubsub().main(argc, argv,
		"Component_Library::Component",
		*std::make_shared<Service_pubsub>(
			*std::make_shared<Service_publisher>("Square_Pub_publisher::Square_writer"),
			*std::make_shared<Service_subscriber>("Square_Sub_subscriber::Square_reader")
		));
}
