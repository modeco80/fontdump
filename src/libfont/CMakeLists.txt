

add_library(fd_font
		RgbaImage.cpp

		FontFile.cpp
		)

target_include_directories(fd_font PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(fd_font PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(fd_font PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		)

# Please use this alias.
add_library(fd::libfont ALIAS fd_font)