-- Global counter (preserved across invocations)  
if not count then count = 0 else count = count + 1  end  

-- Get the writer
local ChatObject_writer = CONTAINER.WRITER['_pub::Chat_writer']

ChatObject_writer.instance['id'] = "Rajive Lua" -- key field  

ChatObject_writer.instance['content'] = "Hello from Lua " .. count

ChatObject_writer:write()

print("Writing", ChatObject_writer.instance['id'], 
                 ChatObject_writer.instance['content'])
