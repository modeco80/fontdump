add_executable(fontdump
		stb_impl.cpp
		main.cpp
		)

set_target_properties(fontdump PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		)

target_link_libraries(fontdump PRIVATE fd::libfont)
