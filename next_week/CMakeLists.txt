FILE(GLOB SRC src/*.cpp)

add_executable(next_week ${SRC})

target_include_directories(next_week PUBLIC ${CMAKE_SOURCE_DIR}/${STB_IMG})