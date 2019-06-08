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




/* Helper utility macros to string-ify a DDS_InstanceHandle_t (GUID) */
#define DDS_GUID_FMT   "%02x%02x%02x%02x.%02x%02x%02x%02x."\
                       "%02x%02x%02x%02x.%02x%02x%02x%02x"
#define DDS_GUID_BIT(g_,i_) \
    ((unsigned char)((char*)(g_))[i_])

#define DDS_GUID_ARGS(g_) \
    DDS_GUID_BIT(g_,0),  DDS_GUID_BIT(g_,1),  \
    DDS_GUID_BIT(g_,2),  DDS_GUID_BIT(g_,3),  \
    DDS_GUID_BIT(g_,4),  DDS_GUID_BIT(g_,5),  \
    DDS_GUID_BIT(g_,6),  DDS_GUID_BIT(g_,7),  \
    DDS_GUID_BIT(g_,8),  DDS_GUID_BIT(g_,9),  \
    DDS_GUID_BIT(g_,10), DDS_GUID_BIT(g_,11), \
    DDS_GUID_BIT(g_,12), DDS_GUID_BIT(g_,13), \
    DDS_GUID_BIT(g_,14), DDS_GUID_BIT(g_,15)

#endif /* READERS_H_ */
