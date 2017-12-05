## Best Practices

### XML App Creation

- Don't use `<domain>` tags for defining a service. It does not scale, 
  since one can't use both `base_name` and `domain_ref` tags at the same 
  time on a `<domain_participant>` tag
   
- Instead define a base `<domain_participant>` that simply declares 
  the common or shared types and topics; this preserves the 
  flexibility and scales well as more services or components are 
  added
 
 - Don't define inline qos policies for endpoints; instead always use a qos 
   profile. Other, there is a higher risk of getting into unintended qos 
   configurations
   

### QoS Profiles

- Always define and use QoS profiles
  - It ensures that they can also be used for application created 
    endpoints, that are not defined a priori in XML files
  - Thus, don't inline QoS policies in XML App Creation Components

- Separate qos policies for participants (in `ParticpantQoSlib`), 
  endpoints (i.e. DataWriter(s) and DataReader(s) in `EndpointQoSLib`), and the
  singleton factory (in `FactoryQoSLib`)

- `ParticpantQoSlib`,  `EndpointQoSLib`, `FactoryQoSLib` are independent hierarchies
   that can extend from the built-in qos profiles
   
- Some `EndpointQoSLib` profiles may have some coupling to the 
  `ParticipantQoSLib`, e.g. for large data; in that case the endpoint qos 
   profile extends or includes the appropriate participant qos profile from 
   `ParticpantQoSlib` 

- For endpoint qos profiles, use topic filters to specify the QoS policies 
  for each topic's DataWriter and DataReader. This also ensures that the qos
  polices will apply to endpoints created in code (i.e. not defined a priori 
  in XML Ap Creation)

- To define service qos profile in `ServiceQoSLib`, extend profiles from 
  `EndpointQoSLib` and use `topic filters` for each topic used by the service. This
   avoids duplication and ensures a compact qos specification.
  
- To define a component's qos profile in `ComponentQoSLib`, extend profiles in 
  `ParticpantQoSlib` and use profiles from `FactoryQoSLib`. This 
   avoids duplication and ensures a compact qos specification.
  
---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
