# Modular Deployment Architecture

An example showing how to compose independently developed services into 
arbitrary deployment components.

- [Overview](#Overview)
- [How To](#HowTo)
- [Organization](./doc/Organization.md)
- [Design](./doc/Design.md)
- [BestPractices](./doc/BestPractices.md)
- [Conventions](./doc/Conventions.md)


## Overview

The example uses the data types and topics used by the 
[RTI Shapes Demo](https://www.rti.com/downloads/shapes-demo). 

The example defines three services, each comprising of two interfaces. 

- `Square` service: comprising of an interface for publication of squares, and 
  an interface for subscription of squares
  - `if/Square.xml` : the service interfaces

- `Circle` service: comprising of an interface for publication of circles, and 
  an interface for subscription of circles
  - `if/Circle.xml` : the service interfaces
    
- `Triangle` service: comprising of an interface for publication of triangles, 
  and an interface for subscription of triangles
  - `if/Triangle.xml` : the service interfaces


Services can be composed to define new components. In this example, several 
components are defined by composing the above services, located in the 
directory `run/Deployment_example`.

- `square_pub.sh` : a component that implements the `Square` publication service
- `triangle_sub.sh` : a component that implements the `Triangle` subscription  
   service
- `circle_pub_triangle_pub.sh` : a component that implements the `Circle` 
	publication service and the `Triangle` publication service
- `square_sub_circle_sub.sh` : a component that implements the `Square` subscription 
	service and the `Circle` subscription service 
- `square_pub_sub.sh` : a component that implements the `Square` publication 
	service and the `Square` subscription service

A component definition can be implemented in the programming language of 
choice. The example shows component implementations in C++11 and Lua.

- `src/c++11/shapes` : component implementations in C++11
- `src/lua/shapes` : component implementations in Lua

The [RTI Shapes Demo](https://www.rti.com/downloads/shapes-demo) can be used 
to visualize the data produced by the services, and to feed data into the 
services.

The directory structure and organization of the artifacts is described in the 
section [Organization](./doc/Organization.md).


## How To

## Creating a new service 

1. Define the data types used by the service

   1.1 Add the data types to the directory:

		res/types/

   For an example, look 
   at [`res/types/ShapeType.idl`](./res/types/ShapeType.idl).

   1.2 For data types defined in IDL, use `rtiddsgen -convertToXml` to generate
       the equivalent XML representation.

			cd res/types/
			make  
	
2. Define a new service interface: `MyService`
  
   2.1 Add a file `res/qos/services/MyService.xml` and define all the service 
      end-point qos policies. Use a *topic_filter* to specify per topic 
      *DataWriter* and *DataReader* Qos. Reuse the common qos policy libraries
      defined in `if/res/qos/common/`, and expand those common libraries if
      appropriate. For an example, look at 
      [res/qos/services/Square.xml](./res/qos/services/Square.xml)
       
    2.2 Add a file `if/MyService.xml` and define all the service interface(s).
    For an example, look at [if/Square.xml](./if/Square.xml) 

    2.3 Ensure that the service interfaces are using the service qos profile
       for all *DataWriter*, *DataReder*, *Publisher*, and *Subscriber* 
       entities. 
 
 3. Implement the service `MyService`
 
Implement the service in the programming language of choice. This example 
illustrates implementations in C++11 and Lua. 
 
 - `src/c+11/shapes/` : C++11 implementation
   - `Service_publisher[.hpp|cxx]` implements the publication interface
   - `Service_subscriber[.hpp|cxx]` implements the subscription interface

 - `src/c+lua/shapes/` : Lua implementation (using *rtiddsprototyper*)
   - `ServicePublisher.lua` implements the publication interface
   - `ServiceSubscriber.lua` implements the subscription interface
 
 
## Creating a new component
 
4. Define a new component: `MyComponent`

   4.1 Add a file `if/<deployment_name>/MyComponent.sh` and define the service
       composition: 
   - `NAME_Component`
   - `BASE_NAME_Component`
   - `DOMAIN_ID_Component`
   - Continue defining `BASE_NAME_<Service>`, until you reach `Root_Library::Root`
       
      For an example, look at: 
   [run/Deployment_example/square_pub_sub.sh](./run/Deployment_example/square_pub_sub.sh)
     
   4.2 Define the component deployment Qos by adding a profile 
   `User.Selected.Component.MyComponent` in `res/qos/components/`. For an example
   look at [res/qos/components/Deployment_example.xml](./res/qos/components/Deployment_example.xml)
     
   4.3 Specify all the XML files in the environment variable: `NDDS_QOS_PROFILES`.
   For an example, look at: 
   [run/Deployment_example/square_pub_sub.sh](./run/Deployment_example/square_pub_sub.sh)
   

5. Implement the component `MyComponent` 

Implement the component in the programming language of choice. This example 
illustrates implementations in C++11 and Lua. 
 
 - `src/c+11/shapes/` : C++11 implementation
   - `Component_square_pub.cxx` composed of the square publication service
   - `Component_triangle_sub.cxx` composed of the triangle publication service
   - `Component_circle_pub_triangle_pub.cxx` composed of the circle publication
   	    service and the triangle publication service
   - `Component_square_sub_circle_sub.cxx` composed of the square subscription
   	    service and the triangle subscription service
   - `Component_square_pub_sub.cxx` composed of the square publication
   	    service and the square subscription service

   To build the components:
	
		cd run/Deployment_example/
		rm -f ../../src/c++11/shapes/objs/x64Darwin16clang8.0/Component_*  
		make -C ../../src/c++11/shapes
		
 - `src/lua/` : Lua implementation (using *rtiddsprototyper*)
   - `Endpoints.lua` generic component thats simply enumerates the endpoints
       of a components and exits


## Running a component

To run a component

- `cd` to the `run/<deployment_directory>/`
- source the script to run setup the component's runtime environment
- launch the component

For example:

	cd run/Deployment_example/
	. square_pub.sh 
	
	# launch the component: C++
	../../src/c++11/shapes/objs/x64Darwin16clang8.0/Component_square_pub

	# launch the component: Lua
	rtiddsprototyper -luaOnData false -participantName $NAME_Component -cfgName Component_Library::Component -luaFile ../../src/lua/shapes/ShapesPublisher.lua 
 
---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
 