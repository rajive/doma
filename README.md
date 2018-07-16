# Modular Deployment Architecture

An example showing how to compose independently developed services into 
arbitrary deployment components.

- [Overview](#overview)
- [How To](#how-to)
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
directory `run/`.

- `square_pub.sh` : a component that implements the `Square` publication service
- `triangle_sub.sh` : a component that implements the `Triangle` subscription service
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
  
   2.1 Add a file `res/qos/services/MyService_qos.xml` by cloning the template
   [`res/template/TEMPLATE_MyService_qos.xml`](./res/template/TEMPLATE_MyService_qos.xml).
   
   2.2 Define all the service end-point qos policies. Use a *topic_filter* to 
   specify per topic *DataWriter* and *DataReader* Qos. Reuse the common qos 
   policy libraries defined in `res/qos/common/`, and expand those common 
   libraries if appropriate. For an example, look at 
   [`res/qos/services/Square_qos.xml`](./res/qos/services/Square_qos.xml).
       
   2.2 Add a file `if/MyService.xml` by cloning the template
   [res/template/TEMPLATE_MyService.xml](./res/template/TEMPLATE_MyService.xml).
   
   2.3 Define all the service interface(s).
   For an example, look at [if/Square.xml](./if/Square.xml) 

   2.4 Ensure that the service interfaces are using the service qos profile
   for all *DataWriter*, *DataReder*, *Publisher*, and *Subscriber* entities. 
 
 
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

   4.1 Add a file `run/MyComponent.sh` by cloning the template
   [res/template/TEMPLATE_MyComponent.sh](./res/template/TEMPLATE_MyComponent.sh).
   
   4.2 Name the component: `NAME_Component`
      
   4.3 Define the service composition: 
   - `BASE_NAME_Component`
   - Continue defining `BASE_NAME_<Service>`, until you reach `Root_Library::Root`
   
   For an example, look at: 
   [run/square\_pub\_sub.sh](./run/square_pub_sub.sh)
     
   4.4 Add a file `res/qos/components/MyComponent_qos.xml` by cloning the template
   [`res/template/TEMPLATE_MyComponent_qos.xml`](./res/template/TEMPLATE_MyComponent_qos.xml).
   
   4.5 Define the component deployment qos policies. For an example
   look at [`res/qos/components/square_pub_sub_qos.xml`](./res/qos/components/square_pub_sub_qos.xml)
     

5. Implement the component `MyComponent` 

  Implement the component in the programming language of choice. This example 
  illustrates implementations in C++11 and Lua. 
 
  - `src/c+11/shapes/` : C++11 implementation
 
     - `Component_square_pub.cxx` composed of the square publication service
     - `Component_triangle_sub.cxx` composed of the triangle publication service
     - `Component_circle_pub_triangle_pub.cxx` composed of the circle publication service 
     and the triangle publication service
     - `Component_square_sub_circle_sub.cxx` composed of the square subscription
     service and the triangle subscription service
     - `Component_square_pub_sub.cxx` composed of the square publication service and the 
     square subscription service

		
  - `src/lua/` : Lua implementation (using *rtiddsprototyper*)
 
     - `Endpoints.lua` generic component thats simply enumerates the endpoints
       of a components and exits; it is the default component that runs 
       if an executable or lua script is not specified in the component
       launcher command line


## Building a component

Generate the platform specific makefile (per platform)

	cd src/c++11/shapes/
	make makefile/x64Darwin17clang9.0  # look at $NDDSHOME/lib for choices
	  
Build components:
	
	cd src/c++11/shapes/
	make

Clean components:

	cd src/c++11/shapes/
	make clean                        # as needed

## Running a component

To run a component, use its launcher script `MyComponent.sh`:

	./run/MyComponent.sh [<domain_id> [<path_to_executable_or_lua_script>] [project_dir]]

The component's launcher script sets up the correct environment for running
the component.  

The `[project_dir]` is only needed if the launcher script is
not located in the standard location under the `run/` directory. The 
`[project_dir]` should contain the hierarchy with the relevant files:

	[project_dir]/
		if/
		res/
			types/
			qos/

The `[<path_to_executable_or_lua_script>]` specifies the component implementation.

- A value ending in `.lua` is launched as a lua script
  within the `rtiddsprototyper`. Otherwise, it is launched as an executable.
  
- To run `rtiroutingservice` with the component's environment:

		./run/MyComponent.sh <domain_id> <rtiroutingservice> [project_dir]

- To launch a shell with the component's environment:

	  	./run/MyComponent.sh <domain_id> bash [project_dir]

- See [Demo](./doc/Demo.md) for examples
 
---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
 