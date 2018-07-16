## Naming Conventions

- Abstract participant names are for the form `ServiceName_InterfaceName`
- Abstract participant base names are derived from participant names by 
  prefixing `BASE_NAME`, thus: `$(BASE_NAME_<name_of_abstract_participant>)`
- Concrete participant name is the name of the component
- Publisher names end with `_publisher`
- DataWriter names end with `_writer`
- Subscriber names end with `_subscriber`
- DataReader names end with `_reader`
- Participant Libraries end with `_Library`
- QoS Libraries end with `QoSLib`, for consistency with the builtin
  qos profiles naming conventions `BuiltinQosLibExp`
- User defined QoS profile names start with `User.`
- Selected or preferred user QoS profile names start with `User.Selected.`
- Service qos profile names start with `User.Service.`
- Component qos profile names start with `User.Component.`


---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.