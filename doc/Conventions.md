## Naming Conventions

- Abstract participant names are for the form `ServiceName_InterfaceName`
- Abstract participant base names are derived from participant names by 
  prefixing `BASE_NAME`, thus: `$(BASE_NAME_<name_of_abstract_participant>)`
- Concrete participant name is the name of the component
- Publisher names end with `_pub`. 
- Subscriber names end with `_sub`
- DataWriter names end with `_writer`
- DataReader names end with `_reader`
- Participant Libraries end with `IfLib`
- QoS Libraries end with `QosLib`, for consistency with the builtin
  qos profiles naming conventions `BuiltinQosLibExp`
- Service specific QoS library names: `<service_name>QosLib`
- Service domain qos profile names start with `<service_name>_Root`
- Service interface qos profile names start with `<service_name>_InterfaceName`
- Selected or preferred user QoS profile names start with `User.Selected.`
- "QoS only" xml files end with `_qos.xml`

---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.