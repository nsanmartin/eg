cmake_minimum_required(VERSION 3.6)
project(hw CXX)

set(RANGES_DIR "~/github/ericniebler/range-v3/")

include_directories(${RANGES_DIR}/include/)

# add_library(range-v3-meta INTERFACE)
# add_library(range-v3::meta ALIAS range-v3-meta)
# target_include_directories(range-v3-meta INTERFACE ${RANGES_DIR}/include/)

add_executable(hw hw.cpp)

add_executable(accumulate_ints accumulate_ints.cpp)
add_executable(any_all_none_of any_all_none_of.cpp)
# add_executable(calendar calendar.cpp)
add_executable(comprehension_conversion comprehension_conversion.cpp)
add_executable(comprehensions comprehensions.cpp)
add_executable(count count.cpp)
add_executable(count_if count_if.cpp)
add_executable(filter_transform filter_transform.cpp)
add_executable(find find.cpp)
add_executable(foo foo.cpp)
add_executable(for_each_assoc for_each_assoc.cpp)
add_executable(for_each_sequence for_each_sequence.cpp)
add_executable(hello hello.cpp)

add_executable(is_sorted is_sorted.cpp)
add_executable(sort_unique sort_unique.cpp)
