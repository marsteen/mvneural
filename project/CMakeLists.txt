cmake_minimum_required(VERSION 3.10)
project("mvneural")

message("System: ${CMAKE_SYSTEM_NAME}")

include_directories("inc")

set(SRCBASE "src")
set(BINDIR  "./build/bin/${CMAKE_SYSTEM_NAME}")

add_executable(mvneural
           ${SRCBASE}/main.cpp
           ${SRCBASE}/NNeural.cpp
           ${SRCBASE}/NStringTool.cpp
           ${SRCBASE}/CTextFileParser.cpp
)


target_link_libraries(mvneural)
file(MAKE_DIRECTORY ${BINDIR})
set_target_properties(mvneural PROPERTIES OUTPUT_NAME ../${BINDIR}/mvneural)    
