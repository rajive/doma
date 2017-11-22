--*****************************************************************************
--*    (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.   *
--*                                                                           *
--*         Permission to modify and use for internal purposes granted.       *
--* This software is provided "as is", without warranty, express or implied.  *
--*                                                                           *
--*****************************************************************************
-- Author: Rajive Joshi, real-Time Innovations, Inc.

---Endpoints
--    List the endpoints (DataWriters and DataReaders) found in the 
--    participant configuration
--  
-- HOW TO?
-- rtiddsprototyper 
--   select the participant configuration

-- Globals (preserved across invocations)
if not count then count = 0 else count = count + 1 end

if count == 0 then 
  -- Iterate over all the writers
  for name,writer in pairs(CONTAINER.WRITER) do 
    print("WRITER", name)
  end
  
  -- Iterate over all the readers
  for name,writer in pairs(CONTAINER.READER) do 
    print("READER", name)
  end
end

CONTAINER.CONTEXT.intentExit = true 
