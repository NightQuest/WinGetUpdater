cmake_minimum_required(VERSION 3.20)
project(WinGetUpdater)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

set(base_files
		src/Application.cpp
		src/Application.h
		src/WinGetHandler.cpp
		src/WinGetHandler.h
		src/preCompiled.cpp
		src/preCompiled.h)

set(source_files
		${base_files})

add_executable(WinGetUpdater WIN32 ${source_files})

if(MSVC)
	source_group("" FILES ${base_files}) # Set a group for Visual Studio
	add_definitions(-DUNICODE -D_UNICODE) # Make sure we're using the Unicode WinAPI
	set_property(TARGET WinGetUpdater PROPERTY VS_DPI_AWARE "PerMonitor")
endif()

target_precompile_headers(WinGetUpdater PUBLIC src/preCompiled.h)

install(TARGETS WinGetUpdater RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
