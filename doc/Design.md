## Interface Definition

A data-oriented interface is defined by:

- an *abstract* participant whose name is the interface name

- inputs: 
  - Subscriber(s) containing DataReaders
  - Subscribers are associated with SubscriberQos
  - DataReader(s) are associated with DataReaderQos

- outputs: 
  - Publishers(s) containing DataWriters
  - Publishers are associated with PublisherQos
  - DataWriters(s) are associated with DataWriterQos  


An abstract participant

- can be be composed with other abstract participants (interfaces)
- does *not* specify a participant_qos 

Abstract participants are composed via inheritance

-  `base_name=$(BASE_NAME_...)` 
- `BASE_NAME__...` environment variable specifies the base interface


## Service Definition

A service is a collection of interfaces. At a minimum a service definition 
includes:

- a service name, say `MyService`

- OPTIONAL: a `<types>` tag 
   - typically using `<include file="...">` tags to load the XML type definitions
     (generated from IDL), that are used by the service 
   - only needed if dynamic types are used by the service or if a concrete service
     is being defined
   - an abstract service can bind the types later when components are defined
   - NOTE: it is a good practice to include this section, so that the service
     definition works with both compiled types and dynamic types

- a `domain_participant_library` named `name=MyService_Library` that contains:

  - a marker interface (i.e. has no inputs and outputs) named `MyService_Root` that 
    - OPTIONAL: `<register_type>` tags
      - registers the types used by the service; this is only needed
        if dynamic types are used (e.g. using scripting in Lua etc.)
      - NOTE: it is a good practice to register the types, so that the service
   	   definition works with both compiled types and dynamic types
   	 - the types can be in a separate file
    - `<topic>` tags for each topic used by the service
    
  - one or more service interfaces  

- a service `qos_profile` named `ServiceQosLib::User.Service.MyService` 
  that defines the endpoint qos policies for all the topics used by the service 
  using topics filters (`topic_filter`)
  - optional *per interface* qos profiles that specialize the 
    service qos profile, e.g. for resources or different ownership strengths etc

- Services can be composed of other services

## Components

A component is an instantiation of a (composite) of service interfaces. It may an
instantiation of a composite service.

A component is a unit of deployment.  

A component's artifacts look similar to those of a service---except that they bind an 
underlying service qos policies and interfaces for a specific deployment.

Typically, there will be one component per unix-style 'process`.

Since composition of XML App Creation is not currently supported out of the box, 
it can be achieved via carefully orchestrated inheritance. The DOMA framework provides
and implementation using scripting and environment variables, described below.

A component binding is configured by defining the environment variables:

- `NAME_Component`     = "component name"
- `DOMAIN_ID_Component` = "domain id"
- `BASE_NAME_Component` = "the *composite* interface to instantiate"


A component's DomainParticipantFactoryQos and DomainParticipantQos
are retrieved from the qos profile 
 `ComponentQosLib::User.Component.$(NAME_Component)` 

This qos profile may customize qos policies for:

- `participant_qos`
- `participant_factory_qos`

---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.