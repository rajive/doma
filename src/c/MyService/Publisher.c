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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rti_me_c.h"

#include "Publisher.h"

#include "Utils.h"

void My_Topic_Chat_output(DDS_DataWriter* writer_untyped, void* sample_untyped,
                          long count) {

    My_Type_Chat_ObjDataWriter *writer = My_Type_Chat_ObjDataWriter_narrow(writer_untyped);
    My_Type_Chat_Obj *sample = (My_Type_Chat_Obj *)sample_untyped;
    DDS_ReturnCode_t retcode = DDS_RETCODE_OK;

    strncpy(sample->id, "Rajive (xml micro C)", My_Type_Chat_MAX_SIZE);
    snprintf(sample->content, My_Type_Chat_MAX_SIZE, "Hello World %ld", count);
    printf("\t%s %s\n", sample->id, sample->content);

    retcode = My_Type_Chat_ObjDataWriter_write(writer, sample, &DDS_HANDLE_NIL);
    switch (retcode) {
    case DDS_RETCODE_OK: break;
    default: fprintf(stderr, "\tfailed output, retcode = %d\n", retcode); break;
    };
    HEAP_PRINT("My_Topic_Chat_output");
}

void My_Topic_Untyped_output(DDS_DataWriter* writer_untyped, void* sample_untyped,
                             long count) {

    DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
    retcode = DDS_DataWriter_write(writer_untyped, sample_untyped, &DDS_HANDLE_NIL);
    switch (retcode) {
    case DDS_RETCODE_OK: break;
    default: fprintf(stderr, "\tfailed output, retcode = %d\n", retcode); break;
    };
    HEAP_PRINT("My_Topic_Untyped_output");
}

void
My_Publisher_on_publication_matched(
        void *listener_data,
        DDS_DataWriter * writer,
        const struct DDS_PublicationMatchedStatus *status) {
    if (status->current_count_change > 0) {
        printf("Matched a subscriber\n");
    }
    else if (status->current_count_change < 0) {
        printf("Unmatched a subscriber\n");
    }
    HEAP_PRINT("My_Publisher_on_publication_matched");
}
