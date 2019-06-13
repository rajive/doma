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

#include "Subscriber.h"
#include "Filters.h"

#include "Readers.h"
#include "reda/reda_ptr_sequence.h"

#include "Utils.h"

void
My_Topic_Chat_input(
        void *listener_data,
        DDS_DataReader * reader_untyped) {

    DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
    struct ReaderInfo *reader_info = (struct ReaderInfo*)listener_data;
    struct DDS_SampleInfoSeq info_seq =  DDS_SEQUENCE_INITIALIZER;
    struct My_Type_Chat_ObjSeq sample_seq = DDS_SEQUENCE_INITIALIZER;
    My_Type_Chat_ObjDataReader *reader =
            My_Type_Chat_ObjDataReader_narrow(reader_untyped);

    printf("%s\n", reader_info->reader_name);
    retcode = My_Type_Chat_ObjDataReader_take(reader,
            &sample_seq, &info_seq, DDS_LENGTH_UNLIMITED,
            DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);

    switch (retcode) {
    case DDS_RETCODE_OK: {
        for (int i = 0; i < My_Type_Chat_ObjSeq_get_length(&sample_seq); ++i) {
            struct DDS_SampleInfo* sample_info =
                    DDS_SampleInfoSeq_get_reference(&info_seq, i);
            My_Type_Chat_Obj* sample =
                    My_Type_Chat_ObjSeq_get_reference(&sample_seq, i);
            printf("\tSample: " DDS_GUID_FMT "  istate = %d  seq_no = %d%u\n",
                    DDS_GUID_ARGS(sample_info->instance_handle.octet),
                    sample_info->instance_state,
                    sample_info->publication_sequence_number.high,
                    sample_info->publication_sequence_number.low);
            if (!sample_info->valid_data) {
                printf("\t\t%p\tINVALID DATA\n", sample);
            } else { /* Print Sample */
                printf("\t\tid: %s\n"
                       "\t\tcontent: %s\n",
                        sample->id, sample->content);
            }
        }
        My_Type_Chat_ObjDataReader_return_loan(reader, &sample_seq, &info_seq);
        break;
    }
    default: fprintf(stderr, "\tfailed input, retcode = %d\n", retcode); break;
    };

    My_Type_Chat_ObjSeq_finalize(&sample_seq);
    DDS_SampleInfoSeq_finalize(&info_seq);
    HEAP_PRINT("My_Topic_Chat_input");
}

void
My_Topic_Untyped_input(
        void *listener_data,
        DDS_DataReader * reader_untyped) {

    DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
    struct ReaderInfo *reader_info = (struct ReaderInfo*)listener_data;
    struct DDS_SampleInfoSeq info_seq =  DDS_SEQUENCE_INITIALIZER;

    struct REDA_PtrSeq reda_ptr_seq = DDS_SEQUENCE_INITIALIZER;
    REDA_PtrSeq_initialize(&reda_ptr_seq);
    struct DDS_UntypedSampleSeq* sample_seq_ptr =
                            (struct DDS_UntypedSampleSeq*)&reda_ptr_seq;

    printf("%s\n", reader_info->reader_name);
    retcode = DDS_DataReader_take(reader_untyped,
            sample_seq_ptr, &info_seq, DDS_LENGTH_UNLIMITED,
            DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);

    switch (retcode) {
    case DDS_RETCODE_OK: {
        for (int i = 0; i < DDS_UntypedSampleSeq_get_length(sample_seq_ptr); ++i) {
            struct DDS_SampleInfo* sample_info =
                    DDS_SampleInfoSeq_get_reference(&info_seq, i);
            void* sample = DDS_UntypedSampleSeq_get_reference(sample_seq_ptr, i);
            printf("\tSample: " DDS_GUID_FMT "  istate = %d  seq_no = %d%u\n",
                    DDS_GUID_ARGS(sample_info->instance_handle.octet),
                    sample_info->instance_state,
                    sample_info->publication_sequence_number.high,
                    sample_info->publication_sequence_number.low);
            if (!sample_info->valid_data) {
                printf("\t\t%p\tINVALID DATA\n", sample);
            } else { /* Print Sample */
                printf("\t\t%p\n", sample);
            }
        }
        DDS_DataReader_return_loan(reader_untyped, sample_seq_ptr, &info_seq);
        break;
    }
    default: fprintf(stderr, "\tfailed input, retcode = %d\n", retcode); break;
    };

    DDS_UntypedSampleSeq_finalize(sample_seq_ptr);
    DDS_SampleInfoSeq_finalize(&info_seq);
    HEAP_PRINT("My_Topic_Untyped_input");
}

void
My_Subscriber_on_subscription_matched(
        void *listener_data,
        DDS_DataReader * reader,
        const struct DDS_SubscriptionMatchedStatus *status) {
    if (status->current_count_change > 0) {
        printf("Matched a publisher\n");
    }
    else if (status->current_count_change < 0) {
        printf("Unmatched a publisher\n");
    }
    HEAP_PRINT("My_Subscriber_on_subscription_matched");
}
