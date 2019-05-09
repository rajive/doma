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

#ifndef READERS_H_
#define READERS_H_

#include "rti_me_c.h"

struct ReaderInfo {
    const char* reader_name;
    DDS_DataReaderListener_SubscriptionMatchedCallback on_subscription_matched;
    DDS_DataReaderListener_DataAvailableCallback on_data_available;
    DDS_DataReaderListener_BeforeSampleDeserializeCallback on_before_sample_deserialize;
    DDS_DataReaderListener_BeforeSampleCommitCallback on_before_sample_commit;
    DDS_DataReader *reader;
};

extern
struct ReaderInfo READER_INFOS[];

extern
const int READER_INFOS_LENGTH;

#endif /* READERS_H_ */
