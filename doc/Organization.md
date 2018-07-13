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
   - `component/` : READ_ONLY predefined component definitions for the deployment 
     framework
      - these should not be altered by the framework user
      
- `res/` : common resources 

  - `types/` : data type definitions

  - `qos/` : qos profiles
  
      - `common/`: common qos profiles 
      
      - `services/`: service specific qos profiles 
         - per service xml file
       
      - `components/` : service specific qos profiles 
         - per deployment xml file
      
 - `run/` : runtime settings for service compositions
    - `<deployment_name>/` : deployment specific runtime configurations
        - scripts that setup the deployment runtime environment for 
          launching components
  
(optional)
 
  - `bin/` : executables 
     - scripts to launch the components
	       
  - `svc/` : Connext DDS platform service configurations 
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
 