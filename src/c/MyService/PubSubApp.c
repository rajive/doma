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

#include "Databus.h"
#include "App.h"

#include "Publisher.h"
#include "Writers.h"

#include "Subscriber.h"
#include "Filters.h"
#include "Readers.h"

int
pubsub_app(long sleep_time, long count) {

    struct Databus *databus = NULL;

    assert((databus = Databus_create(My_If_PUBSUB))
            != NULL
    );
    Databus_initialize(databus, READER_INFOS, READER_INFOS_LENGTH,
                                WRITER_INFOS, WRITER_INFOS_LENGTH);

    assert(Databus_enable(databus)
            == DDS_RETCODE_OK
    );

    App_loop(sleep_time, count, (Activity)Databus_output, databus);

done:
    Databus_finalize(databus);
    Databus_delete(databus);

    return 0;
}

int
main(int argc, char **argv) {
    long sleep_time = 1000;
    long count = 0;
    App_arguments(argc, argv, &sleep_time, &count);
    return pubsub_app(sleep_time, count);
}
