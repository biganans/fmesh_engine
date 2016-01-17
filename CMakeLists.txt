
include(CheckCXXCompilerFlag)

project(fmesh_engine)

cmake_minimum_required(VERSION 2.8.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
if(MSVC)
#TODO

else(MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  if(APPLE)
    set(CMAKE_XCODE_ATTRIBUTE_GCC_C_LANGUAGE_STANDARD "gnu99")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
  set(CMAKE_CXX_FLAGS_DEBUG          "-g -DDEBUG")
  set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
endif(MSVC)

if(APPLE)
  set(CMAKE_C_COMPILER clang)
  set(CMAKE_CXX_COMPILER clang++)
endif()

if(UNIX)
    include_directories(./engine/include ./engine/lib/package  /usr/local/include)
else(UNIX)
  if(MINGW)
    include_directories(./engine/include ./engine/lib/package/ C:/MinGW/opt/include)
    link_directories(C:/MinGW/opt/lib C:/MinGW/lib)
  else(MINGW)
    include_directories(./engine/include ./engine/lib/package/ C:/opt/include)
#    include_directories(./engine/include ./engine/lib/package/ C:/opt/include C:/opt/package/gfx/Include)
    link_directories(C:/opt/lib)
#    link_directories(C:/opt/lib C:/opt/package/gfx/Lib/Win32/Msvc90/Release)
  endif(MINGW)

endif(UNIX)


file(GLOB_RECURSE engine_src engine/src/*.cpp)
add_executable(fmesh_engine ${engine_src})


if(APPLE)
  include_directories(/System/Library/Frameworks)
  find_library(OpenGL_LIBRARY OpenGL)
  mark_as_advanced(OpenGL_LIBRARY)
  add_definitions("-DGL_PROFILE_3_3")
else(APPLE)
  find_package(OpenGL REQUIRED)
  include_directories(${OpenGL_INCLUDE_DIRS})
  link_directories(${OpenGL_LIBRARY_DIRS})
  add_definitions(${OpenGL_DEFINITIONS})
  add_definitions("-DGL_PROFILE_4_4")
endif(APPLE)

if(UNIX)
  find_library(glew_LIBRARY glew)
  find_library(sdl2_LIBRARY sdl2)
  find_library(sdl2_image_LIBRARY sdl2_image)
  find_library(sdl2_ttf_LIBRARY sdl2_ttf)
  find_library(assimp_LIBRARY assimp)
endif()

add_definitions("-DUSE_SDL")
add_definitions("-DUSE_GLEW")
add_definitions("-DGLM_FORCE_RADIANS")
add_definitions("-DGLM_FORCE_CXX11")
add_definitions("-DGLM_PRECISION_MEDIUMP_FOLOAT")

if(UNIX)
  target_link_libraries(fmesh_engine ${OpenGL_LIBRARY} ${glew_LIBRARY} ${sdl2_LIBRARY} ${sdl2_image_LIBRARY} ${sdl2_ttf_LIBRARY} ${assimp_LIBRARY})
else(UNIX)
  if(MINGW)
    add_definitions("-DUSE_PCRE")
    target_link_libraries(fmesh_engine opengl32 glew32 glew32mx sdl2 sdl2_image sdl2_ttf assimp pcrecpp pcre)
  else(MINGW)
    target_link_libraries(fmesh_engine opengl32 glew32 sdl2 sdl2_image sdl2_ttf assimp)
#    target_link_libraries(fmesh_engine opengl32 glew32 sdl2 sdl2_image sdl2_ttf assimp libAS2 libgfx libgfxexpat libgfxrender_gl libgfxsound_fmod)
  endif(MINGW)
endif(UNIX)

CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CXX11)
if(NOT HAS_CXX11)
  message("cxx11 no find")
endif()


file(GLOB SourceIgnoreFiles "${CMAKE_SOURCE_DIR}/*")
set(SourceKeepFiles "${CMAKE_SOURCE_DIR}/engine"
                    "${CMAKE_SOURCE_DIR}/CMakeLists.txt")
list(REMOVE_ITEM SourceIgnoreFiles ${SourceKeepFiles})
# Escape any '.' characters
string(REPLACE "." "\\\\." SourceIgnoreFiles "${SourceIgnoreFiles}")

include(InstallRequiredSystemLibraries)
set(CPACK_SOURCE_IGNORE_FILES "${SourceIgnoreFiles}")
set(FMESH_VERSION_MAJOR 1)
set(FMESH_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_MAJOR "${FMESH_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${FMESH_VERSION_MINOR}")
if(APPLE)
  set(CPACK_BUNDLE_NAME "fmesh_engine")
  #todo
endif()

if(WIN32)
  #todo
endif()

set(CPACK_PACKAGE_NAME "fmesh_engine")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_GENERATOR "TGZ")
include(cpack)


set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS fmesh_engine
  RUNTIME DESTINATION bin)

