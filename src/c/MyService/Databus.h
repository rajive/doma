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

#ifndef Databus_h
#define Databus_h

#include "Readers.h"
#include "Writers.h"

#undef NDEBUG
#include <assert.h>

struct Databus;

extern struct Databus*
Databus_create(const char *participant_name);

extern void
Databus_delete(struct Databus *databus);

extern DDS_ReturnCode_t
Databus_enable(struct Databus *databus);

/**
 * Create a databus
 * databus      - the databus to initialize
 * reader_infos - the wiring of the inputs to application logic
 * writer_infos - the wiring of the outputs to application logic
 *
 * NOTE: reader_infos and writer_infosshould be a valid pointer as long as the
 *       databus exists; a copy is NOT made for the sake of a minimal footprint
 */
extern void
Databus_initialize(struct Databus* databus,
            struct ReaderInfo reader_infos[],
            struct WriterInfo writer_infos[]);

extern void
Databus_finalize(struct Databus* databus);

extern void
Databus_output(struct Databus* databus, long count);

#endif /* Databus_h */
