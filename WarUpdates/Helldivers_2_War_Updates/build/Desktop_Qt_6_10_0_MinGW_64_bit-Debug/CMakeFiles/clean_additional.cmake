# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Helldivers_2_War_Updates_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Helldivers_2_War_Updates_autogen.dir\\ParseCache.txt"
  "Helldivers_2_War_Updates_autogen"
  )
endif()
