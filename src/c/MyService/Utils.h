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

#ifndef _UTILS_H_
#define _UTILS_H_

#ifndef NDEBUG

#define HEAP_PRINT(prefix) \
printf(prefix ": OSAPI_Heap_allocated_byte_count =  %d\n", OSAPI_Heap_get_allocated_byte_count())

#else
#define HEAP_PRINT(prefix)
#endif

#endif /* _UTILS_H_ */
