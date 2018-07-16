/*****************************************************************************/
/*     (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.  */
/*                                                                           */
/*         Permission to modify and use for internal purposes granted.       */
/* This software is provided "as is", without warranty, express or implied.  */
/*                                                                           */
/*****************************************************************************/
/* Component_circle_pub_triangle_pub.cxx

Service composition example. This component implements a service that
is a composition of two other services:

- a service that subscribes to Squares
- a service that subscribes to Circles
*/


#include <iostream>

#include <dds/pub/ddspub.hpp>

#include "Component.hpp"
#include "Service_subscriber.hpp"

#include "ShapeType.hpp"

class Service_sub_sub : public Service {
public:
	Service_sub_sub(Service_subscriber& subscriber1,
				    Service_subscriber& subscriber2)
	: subscriber1_(subscriber1),
	  subscriber2_(subscriber2) {
	}

	virtual void init(dds::domain::DomainParticipant participant) {
		subscriber1_.init(participant);
		subscriber2_.init(participant);
	}

	virtual void execute(int count) {
		subscriber1_.execute(count);
		subscriber2_.execute(count);
	}

private:
	Service_subscriber& subscriber1_;
	Service_subscriber& subscriber2_;
};

class Component_sub_sub : public Component {
public:
	virtual void register_types() {
		rti::domain::register_type<rti::example::ShapeType>("ShapeType");
	}
};

int main(int argc, char *argv[])
{
	return Component_sub_sub().main(argc, argv,
		"Component_Library::Component",
		*std::make_shared<Service_sub_sub>(
			*std::make_shared<Service_subscriber>("Square_Sub_subscriber::Square_reader"),
			*std::make_shared<Service_subscriber>("Circle_Sub_subscriber::Circle_reader")
		));
}
