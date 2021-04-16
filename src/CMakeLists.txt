add_executable(${PROJECT_NAME} main.cpp rtpmidi.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/rtpmidid/include)
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/rtpmidid/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC -lrtpmidid -lfmt -lavahi-common -lavahi-client)