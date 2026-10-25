# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/LinuxDeepl_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/LinuxDeepl_autogen.dir/ParseCache.txt"
  "LinuxDeepl_autogen"
  )
endif()
