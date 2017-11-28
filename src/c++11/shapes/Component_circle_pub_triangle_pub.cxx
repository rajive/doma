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

- a service that publishes Circles
- a service that publishes Triangles
*/


#include <iostream>

#include <dds/pub/ddspub.hpp>

#include "Component.hpp"
#include "Service_publisher.hpp"

#include "ShapeType.hpp"

class Service_pub_pub : public Service {
public:
	Service_pub_pub(Service_publisher& publisher1,
				    Service_publisher& publisher2)
	: publisher1_(publisher1),
	  publisher2_(publisher2) {
	}

	virtual void init(dds::domain::DomainParticipant participant) {
		publisher1_.init(participant);
		publisher2_.init(participant);
	}

	virtual void execute(int count) {
		publisher1_.execute(count);
		publisher2_.execute(count);
	}

private:
	Service_publisher& publisher1_;
	Service_publisher& publisher2_;
};

class Component_pub_pub : public Component {
public:
	virtual void register_types() {
		rti::domain::register_type<rti::example::ShapeType>("ShapeType");
	}
};

int main(int argc, char *argv[])
{
	return Component_pub_pub().main(argc, argv,
		"Component_Library::Component",
		*std::make_shared<Service_pub_pub>(
			*std::make_shared<Service_publisher>("Circle_Publisher::CircleWriter"),
			*std::make_shared<Service_publisher>("Triangle_Publisher::TriangleWriter")
		));
}
