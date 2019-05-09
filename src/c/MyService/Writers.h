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

#ifndef WRITERS_H_
#define WRITERS_H_

#include "rti_me_c.h"

typedef void* (*SampleCreate)();
typedef void  (*SampleDelete)(void *);
typedef void  (*SampleOutput)(DDS_DataWriter*, void*);

struct WriterInfo {
    const char* writer_name;
    SampleCreate sample_create_func;
    SampleDelete sample_delete_func;
    SampleOutput sample_output_func;
    DDS_DataWriterListener_PublicationMatchedCallback on_publication_matched;
    DDS_DataWriter *writer;
    void* sample;
};

extern
struct WriterInfo WRITER_INFOS[];

extern
const int WRITER_INFOS_LENGTH;

#endif /* WRITERS_H_ */
