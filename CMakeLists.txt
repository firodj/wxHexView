cmake_minimum_required (VERSION 3.9)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

project (wxHexView)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(wxHexView_SOURCE_FILES
  Source/wxHexView.cpp
  Source/wxHexView.h
)
message(STATUS "wxWidgets LIB: ${wxWidgets_LIBRARIES}")
add_library(wxHexView ${wxHexView_SOURCE_FILES})
target_include_directories(wxHexView INTERFACE Source)
# set_property(TARGET wxHexView PROPERTY CXX_STANDARD 11)

add_executable(wxHexView_test WIN32 Test/main.cpp
  Test/DummyDataProvider.h
)
# set_property(TARGET wxHexView_test PROPERTY CXX_STANDARD 11)
target_link_libraries(wxHexView_test PRIVATE ${wxWidgets_LIBRARIES}
  wxHexView)

if (WIN32)
  # set stuff for windows
else ()
  target_compile_options(wxHexView PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>)
  target_compile_options(wxHexView_test PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++>)

  # set_target_properties(wxHexView PROPERTIES 
  #   COMPILE_FLAGS "-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++"
  #   LINK_FLAGS "-mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++"
  # target_link_options(wxHexView PRIVATE
  #   -mmacosx-version-min=10.9 -std=gnu++11 -stdlib=libc++)
  # set_target_properties(gui PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif ()
