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

#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include "rti_me_c.h"

#include "MyServiceSupport.h"
#include "Filters.h"

extern void
My_Topic_Chat_input(
        void *listener_data,
        DDS_DataReader * reader);

void
My_Topic_Untyped_input(
        void *listener_data,
        DDS_DataReader * reader_untyped);

extern void
My_Subscriber_on_subscription_matched(
        void *listener_data,
        DDS_DataReader * reader,
        const struct DDS_SubscriptionMatchedStatus *status);

#endif /* SUBSCRIBER_H_ */
