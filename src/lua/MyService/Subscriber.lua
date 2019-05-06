-- Get the reader
local ChatObject_reader = CONTAINER.READER['_sub::Chat_reader']

ChatObject_reader:take()

for  i, chat_object in ipairs(ChatObject_reader.samples) do

  if (ChatObject_reader.infos[i].valid_data) then

    print(chat_object['id'], chat_object['content'])

  end

end
