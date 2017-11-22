--*****************************************************************************
--*    (c) 2005-2017 Copyright, Real-Time Innovations, All rights reserved.   *
--*                                                                           *
--*         Permission to modify and use for internal purposes granted.       *
--* This software is provided "as is", without warranty, express or implied.  *
--*                                                                           *
--*****************************************************************************
-- Author: Rajive Joshi, real-Time Innovations, Inc.

---ShapesSubscriber
-- Subscribes to all topics found in the participant configuration
-- 
-- HOW TO?
-- rtiddsprototyper 
--   select the participant configuration

-- Globals (preserved across invocations)
if not count then count = 0 else count = count + 1 end
print("*** iteration ", count,  "***")

-- Iterate over all the readers
for name,reader in pairs(CONTAINER.READER) do 

	print("READER", name)
	reader:take()

	for  i, shape in ipairs(reader.samples) do

		print("\t color:", shape['color']) -- key

		if (not reader.infos[i].valid_data) then
			print("\t invalid data!")
		end

		print("\t x:", shape['x']) 
		print("\t y:", shape['y'])
		print("\t shapesize:", shape['shapesize'])

	end
end
