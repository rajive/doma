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

#include "rti_me_c.h"
#include "app_gen/app_gen_plugin.h"
#include "dds_c/dds_c_profile.h"

#include "Databus.h"

struct Databus {
    DDS_DomainParticipant *participant;
    struct ReaderInfo* reader_infos;
    struct WriterInfo* writer_infos;
};

struct Databus *
Databus_create(const char *participant_name) {

    struct Databus *databus = NULL;
    DDS_DomainParticipantFactory *factory = NULL;
    RT_Registry_T *registry = NULL;
    DDS_DomainParticipant *participant = NULL;

    struct APPGEN_FactoryProperty model_xml = APPGEN_FactoryProperty_INITIALIZER;
    model_xml._model = APPGEN_get_library_seq();

    assert((factory = DDS_DomainParticipantFactory_get_instance())
            != NULL
    );
    assert((registry = DDS_DomainParticipantFactory_get_registry(factory))
            != NULL
    );
    assert(APPGEN_Factory_register(registry, &model_xml)); /* register the MAG/Appgen code */
    assert((participant =
            DDS_DomainParticipantFactory_create_participant_from_config(factory,participant_name))
            != NULL
    );
    assert((databus = (struct Databus *)malloc(sizeof(struct Databus)))
            != NULL
    );

    if (databus != NULL) {
        databus->participant = participant;
        databus->reader_infos = NULL;
        databus->writer_infos = NULL;
    }
    return databus;
}

void
Databus_delete(struct Databus *databus) {

    DDS_ReturnCode_t retcode;
    RT_Registry_T *registry = NULL;
    DDS_DomainParticipantFactory *factory = NULL;

    if (databus == NULL || databus->participant == NULL) { return; }

    assert(DDS_DomainParticipant_delete_contained_entities(
            databus->participant)
            == DDS_RETCODE_OK
    );

    assert((factory = DDS_DomainParticipantFactory_get_instance())
            != NULL
    );
    assert(DDS_DomainParticipantFactory_delete_participant(factory, databus->participant)
            == DDS_RETCODE_OK
    );
    databus->participant = NULL;
    free(databus);


    assert((registry = DDS_DomainParticipantFactory_get_registry(factory))
            != NULL
    );
    assert(APPGEN_Factory_unregister(registry, NULL));

    assert(DDS_DomainParticipantFactory_finalize_instance()
            == DDS_RETCODE_OK
    );
}


DDS_ReturnCode_t
Databus_enable(struct Databus *databus) {

    DDS_Entity *entity = DDS_DomainParticipant_as_entity(databus->participant);
    DDS_ReturnCode_t retcode = DDS_Entity_enable(entity);

    switch (retcode) {
    case DDS_RETCODE_OK: break;
    default: fprintf(stderr, "failed to enable participant\n"); break;
    };

    return retcode;
}


void
Databus_initialize(struct Databus* databus,
        struct ReaderInfo reader_infos[],
        struct WriterInfo writer_infos[]) {

    if (writer_infos != NULL) {
        databus->writer_infos = writer_infos;
        int length = sizeof(*writer_infos)/sizeof(struct WriterInfo);
        for (int i = 0; i < length; ++i) {

            /* lookup DataWriter if a (non-NULL) writer_name is specified */
            if (writer_infos[i].writer_name != NULL) {
                writer_infos[i].writer = DDS_DomainParticipant_lookup_datawriter_by_name(
                        databus->participant,
                        writer_infos[i].writer_name);
                assert(writer_infos[i].writer != NULL);
            }

            /* set DataWriter listener if specified */
            if (writer_infos[i].writer != NULL) {
                struct DDS_DataWriterListener dw_listener = DDS_DataWriterListener_INITIALIZER;
                DDS_UnsignedLong dw_status_mask = DDS_STATUS_MASK_NONE;
                if (writer_infos[i].on_publication_matched != NULL) {
                    dw_listener.on_publication_matched = writer_infos[i].on_publication_matched;
                    dw_status_mask |= DDS_PUBLICATION_MATCHED_STATUS;
                }
                assert(DDS_DataWriter_set_listener(writer_infos[i].writer, &dw_listener,
                        dw_status_mask)
                        == DDS_RETCODE_OK
                );
            }

            /* create sample if a (non-NULL) sample_create_func is specified */
            if (writer_infos[i].sample_create_func != NULL) {
                writer_infos[i].sample = writer_infos[i].sample_create_func();
                assert(writer_infos[i].sample != NULL);
            }
        }
    }

    if (reader_infos != NULL) {
        databus->reader_infos = reader_infos;
        int length = sizeof(*reader_infos)/sizeof(struct ReaderInfo);
        for (int i = 0; i < length; ++i) {

            /* lookup DataWriter if a (non-NULL) writer_name is specified */
            if (reader_infos[i].reader_name != NULL) {
                reader_infos[i].reader = DDS_DomainParticipant_lookup_datareader_by_name(
                        databus->participant,
                        reader_infos[i].reader_name);
                assert(reader_infos[i].reader != NULL);
            }

            /* set DataReader listener if specified */
            if (reader_infos[i].reader != NULL) {
                struct DDS_DataReaderListener dr_listener = DDS_DataReaderListener_INITIALIZER;
                DDS_UnsignedLong dr_status_mask = DDS_STATUS_MASK_NONE;
                if (reader_infos[i].on_subscription_matched != NULL) {
                    dr_listener.on_subscription_matched = reader_infos[i].on_subscription_matched;
                    dr_status_mask |= DDS_SUBSCRIPTION_MATCHED_STATUS;
                }
                if (reader_infos[i].on_data_available != NULL) {
                    dr_listener.on_data_available = reader_infos[i].on_data_available;
                    dr_status_mask |= DDS_DATA_AVAILABLE_STATUS;
                }

                dr_listener.on_before_sample_deserialize = reader_infos[i].on_before_sample_deserialize;
                dr_listener.on_before_sample_commit      = reader_infos[i].on_before_sample_commit;

                assert(DDS_DataReader_set_listener(reader_infos[i].reader, &dr_listener,
                        dr_status_mask)
                        == DDS_RETCODE_OK
                );
            }
        }
    }
}

void
Databus_finalize(struct Databus* databus) {

    databus->reader_infos = NULL;

    if (databus->writer_infos) {
        struct WriterInfo *writer_infos = databus->writer_infos;
        int length = sizeof(*writer_infos)/sizeof(struct WriterInfo);
        for (int i = 0; i < length; ++i) {
            /* delete sample if a (non-NULL) sample_delete_func is specified */
            if (writer_infos[i].sample != NULL && writer_infos[i].sample_delete_func != NULL) {
                writer_infos[i].sample_delete_func(writer_infos[i].sample);
                writer_infos[i].sample = NULL;
            }
        }
    }
    databus->writer_infos = NULL;
}

void
Databus_output(struct Databus* databus, long count) {
    DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
    struct WriterInfo *writer_infos = databus->writer_infos;

    int length = sizeof(*writer_infos)/sizeof(struct WriterInfo);
    for (int i = 0; i < length; ++i) {
        printf("%s: writing sample %ld\n", writer_infos[i].writer_name, count);

        /* call the output function for each writer, if specified */
        if (writer_infos[i].sample_output_func != NULL) {
            writer_infos[i].sample_output_func(writer_infos[i].writer,
                                               writer_infos[i].sample, count);

        /* call the untyped write function on the datawriter */
        } else {
            retcode = DDS_DataWriter_write(writer_infos[i].writer, writer_infos[i].sample, &DDS_HANDLE_NIL);
            switch (retcode) {
            case DDS_RETCODE_OK: break;
            default: fprintf(stderr, "failed to write\n"); break;
            };
        }
    }
}
