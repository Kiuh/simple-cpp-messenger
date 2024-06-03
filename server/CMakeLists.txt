cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME server)

project(${PROJECT_NAME})

set(LOCAL_SRCS "")
aux_source_directory(src LOCAL_SRCS)

# Boost
set(BOOST_DETECTED_TOOLSET "gcc")
find_package(Boost REQUIRED COMPONENTS system thread filesystem)

# Executables
add_executable(${PROJECT_NAME} ${LOCAL_SRCS})

# Link
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
