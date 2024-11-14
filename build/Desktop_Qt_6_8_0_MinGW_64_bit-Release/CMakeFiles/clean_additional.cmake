# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Graph_ImagingUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Graph_ImagingUI_autogen.dir\\ParseCache.txt"
  "Graph_ImagingUI_autogen"
  )
endif()
