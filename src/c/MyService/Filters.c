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

#include "Filters.h"

/*i
 * \brief Helper function to filter an My_Type_Chat_Obj sample
 *
 * \param[in]  sample       A My_Type_Chat_Obj data sample to filter
 * \param[out] drop_sample  Out parameter determining whether the sample
 *                          should be filtered out or not.
 */
void 
My_Type_Chat_Obj_filter_sample(
        My_Type_Chat_Obj *sample,
        DDS_Boolean *drop_sample) {

    /* Example filter: drop samples where contents tarts with 'X' */
    *drop_sample = (sample->content[0] == 'X') ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
}

/*i
 * \brief Implementation of \ref DDS_DataReaderListener::on_before_sample_commit
 */
DDS_Boolean
My_Type_Chat_Obj_on_before_sample_commit(
        void *listener_data,
        DDS_DataReader *reader,
        const void *const sample,
        const struct DDS_SampleInfo *const sample_info,
        DDS_Boolean *dropped) {

    My_Type_Chat_Obj *ChatObject_sample = (My_Type_Chat_Obj *)sample;

    My_Type_Chat_Obj_filter_sample(ChatObject_sample, dropped);

    if (*dropped) {
        printf("\nSample filtered, before commit...\n\tDROPPED - id: %s, content %s\n",
               ChatObject_sample->id, ChatObject_sample->content);
    }

    return DDS_BOOLEAN_TRUE;
}



/*ci \brief Unsigned Long type size */
#define UNSIGNED_LONG_SIZE  4

/*i
 * \brief Helper function to deserialize an unsigned long
 *
 * \param[in]  src_buffer      Pointer to CDR stream buffer
 * \param[in]  need_byte_swap  Indicates whether it is needed to swap bytes
 * \param[out] instance        Deserialized unsigned long
 */
void
MySubscriber_deserialize_unsigned_long(
        char **src_buffer,
        RTI_BOOL need_byte_swap,
        DDS_UnsignedLong *instance) {

    RTI_INT32 i;
    if (need_byte_swap) {
        for (i = 3; i >= 0; --i) {
            *((RTI_INT8*)instance + i) = *((*src_buffer)++);
        }
    }
    else {
        *instance = *(RTI_UINT32*)(*src_buffer);
        (*src_buffer) += CDR_LONG_SIZE;
    }
}

/*i
 * \brief Implementation of \ref DDS_DataReaderListener::on_before_sample_deserialize
 */
DDS_Boolean
My_Type_Chat_Obj_on_before_sample_deserialize(
        void *listener_data,
        DDS_DataReader *reader,
        struct NDDS_Type_Plugin *plugin,
        struct CDR_Stream_t *stream,
        DDS_Boolean *dropped) {

    DDS_Boolean result = DDS_BOOLEAN_FALSE;
    DDS_Long id = 0;
    RTI_BOOL need_byte_swap = DDS_BOOLEAN_FALSE;
    char *src_buffer = NULL;

    need_byte_swap = CDR_Stream_is_byte_swapped(stream);
    src_buffer = CDR_Stream_get_current_position_ptr(stream);

    /* deserialize only field 'id', instead of the whole sample */

    if (!CDR_Stream_check_size(stream, UNSIGNED_LONG_SIZE)) {
        printf("Failed to deserialize id. The stream is too short, missing data\n");
        goto done;
    }

    /* Note primitive types must be aligned to their length in the CDR stream.
     * For example, a long must start on a 4-byte boundary. The boundaries are
     * counted from the start of the CDR stream.
     * As the sample 'id' is the first data in the stream it is already aligned.
     * Position 0 (beginning of the stream) is aligned to 4 (size of long).
     */
    MySubscriber_deserialize_unsigned_long(&src_buffer,
            need_byte_swap,
            (DDS_UnsignedLong*)&id);

    /* filter the sample */
    *dropped = (id % 2 == 0) ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;

    if (*dropped) {
        printf("\nSample filtered, before deserialize...\n\tDROPPED - id: %d\n", id);
    }

    result = DDS_BOOLEAN_TRUE;

done:
    return result;
}
