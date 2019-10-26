## Organization

The organization scheme for the artifacts is described below. 

### Goals

The goals of organizing the artifacts are to support the following use cases:

- A single component comprised of a single service
- A single component composed from multiple services
- Multiple components composed from multiple services
- Multiple versions of service interfaces and components
- Multiple deployment configurations 
- Aggregation of independently developed services and components
 
 
### Files System Hierarchy

The structure below may be applied per "service" or "(sub-)system". 
A "(sub-)system" is a collection of services and components.

Multiple services or sub-systems can be composed by overlaying them on top of 
a directory structure organized using the scheme below.

- `doc/`  : documentation

NEEDED FOR DEPLOYMENT:

- `if/` : interfaces 
    - per service xml file
    - `component/` : READ_ONLY predefined component definitions for the deployment framework
       - these should not be altered by the framework user
      
- `res/` : common resources 

  - `types/` : data type definitions

  - `qos/` : qos profiles
  
      - `common/`: common qos profiles 
      
      - `services/`: service specific qos profiles 
         - per service xml file
       
      - `components/` : service specific qos profiles 
         - per deployment xml file
      
  - `bin/` : executables 
    - scripts to launch the components
      - may include runtime settings for service compositions
        e.g. a launcher script per component to setup its runtime deployment environment
  
(optional)
       	       
  - `res/`
    - `svc/` : configurations for *Connext Databus* services 
        - `ps/`  : persistence service configurations
        - `rs/`  : routing service configurations  
        - `qs/`  : queuing service configurations 
        - `rec/` : recording service configurations 
        - `rep/` : replay service configurations 
        - `db/`  : database integration service configurations
        - `web/` : web integration service configurations  
 
 NEEDED FOR DEVELOPMENT: in addition to the above
    
 - `src/` : source code (project specific)
 
   - `c++11/` : C++11 source code
   
   - `lua/`   : Lua source code
   
   - `...`

---
Author: Rajive Joshi, Real-Time Innovations Inc. Copyright (C) 2017.
 