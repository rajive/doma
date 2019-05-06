/******************************************************************************
#   Copyright 2019 Rajive Joshi, Real-Time Innovations Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#*****************************************************************************/

#include "Readers.h"

#include "Subscriber.h"

struct ReaderInfo READER_INFOS[] = {
        {My_Topic_chat_READER,
                My_Subscriber_on_subscription_matched,
                My_Topic_Chat_input,
                /*My_Type_Chat_Obj_on_before_sample_deserialize,
                My_Type_Chat_Obj_on_before_sample_commit*/
        },
};
