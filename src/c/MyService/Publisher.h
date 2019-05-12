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

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "rti_me_c.h"

#include "res/types/MyServiceSupport.h"
#include "res/types/ChatSupport.h"

extern void
My_Topic_Chat_output(DDS_DataWriter* writer_untyped, void* sample_untyped);

extern void
My_Topic_Untyped_output(DDS_DataWriter* writer_untyped, void* sample_untyped);

extern void
My_Publisher_on_publication_matched(
        void *listener_data,
        DDS_DataWriter * writer,
        const struct DDS_PublicationMatchedStatus *status);

#endif /* PUBLISHER_H_ */
