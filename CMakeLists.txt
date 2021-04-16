cmake_minimum_required(VERSION 3.13)
project(rtp_midi_interface)

set(CMAKE_CXX_STANDARD 17)

#find_library(RTP_MIDI_LIB rtpmidid HINTS ${CMAKE_SOURCE_DIR}/3rdparty/rtpmidid/lib)

add_subdirectory(src)