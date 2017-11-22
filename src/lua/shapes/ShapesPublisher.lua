--*****************************************************************************
--*    (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.   *
--*                                                                           *
--*         Permission to modify and use for internal purposes granted.       *
--* This software is provided "as is", without warranty, express or implied.  *
--*                                                                           *
--*****************************************************************************
-- Author: Rajive Joshi, real-Time Innovations, Inc.

---ShapeaPublisher
-- Publishes to all topics found in the participant configuration
-- 
-- HOW TO?
-- rtiddsprototyper 
--   select the participant configuration

-- Globals (preserved across invocations)
if count then count = count + 1 
else -- initialize (first time)
  count = 0
  center = 120 radius = 70
end
print("*** iteration ", count,  "***")

-- Iterate over all the writers
for name,writer in pairs(CONTAINER.WRITER) do 

	print("WRITER", name)

  writer.instance['color'] = "GREEN"
  writer.instance['x'] = center + radius * math.sin(count)
  writer.instance['y'] = center + radius * math.cos(count) 
  writer.instance['shapesize'] = 20
  
  writer:write()
end
