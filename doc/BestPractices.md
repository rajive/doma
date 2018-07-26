## Best Practices

### XML App Creation

- Don't use `<domain>` tags for defining a service. It does not scale, 
  since one can't use both `base_name` and `domain_ref` tags at the same 
  time on a `<domain_participant>` tag.
   
- Instead define a base `<domain_participant>` that simply declares 
  the common or shared types and topics; this preserves the 
  flexibility and scales well as more services or components are 
  added.
 
 - Don't define inline qos policies for DDS entities; instead always use a qos 
   profile. Otherwise, there is a higher risk of getting into unintended qos 
   configurations. 
   
 - Also, inline qos can't be easily referenced in application
   code for dynamically created DDS entities, but a qos profile can.
   

### QoS Profiles

- Always define QoS in qos profiles.
  - Don't inline QoS in XML App Creation Components.
  - This ensures that the QoS can also be used for DDS entities created 
    dynamically in code (and not defined a priori in XML files).
  - This ensures that the qos are usable also the Connext Tools & Services 
    (Protototper, Recording Service, Routing Service etc.).

- Separate qos policies for participants (in `ParticpantQosLib`), 
  endpoints (i.e. DataWriter(s) and DataReader(s) in `EndpointQosLib`), and the
  singleton factory (in `FactoryQosLib`).

   - `ParticpantQosLib`,  `EndpointQosLib`, `FactoryQosLib` are independent hierarchies
      that can extend from the built-in qos profiles.
   
   - Some `EndpointQosLib` profiles may have some coupling to the 
     `ParticipantQosLib`, e.g. for large data; in that case the endpoint qos 
     profile should extend or include the appropriate participant qos profile 
     from `ParticpantQosLib`.

- For endpoint qos profiles, use topic filters to specify the QoS policies 
  for each topic's DataWriter and DataReader. This  ensures that the qos
  polices will apply to endpoints created in code (i.e. not defined a priori 
  in XML App Creation).
  
- topic_filter should use a wild card so that the policy applies to the 
  DataReader(s) for the base topic name and a derived content filtered topic.
  The content filtered topic name should thus derive from the base
  topic name. For example: "MyTopic/filtered" would name a content filtered
  topic, and a topic_filter="MyTopic*" would apply to both "MyTopic" and 
  "MyTopic/filtered" DataReaders.
  

- To define service qos profile in `ServiceQosLib`, extend profiles from 
  `EndpointQosLib` and use `topic filters` for each topic used by the service. This
   avoids duplication and ensures a compact qos specification.
  
- To define a component's qos profile in `ComponentQosLib`, extend profiles in 
  `ParticpantQosLib` and use profiles from `FactoryQosLib`. This 
   avoids duplication and ensures a compact qos specification.
  
---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
