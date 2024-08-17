# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (Hiwonder 
	hiwonder.cxx
)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (
	Hiwonder PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)



#target_link_libraries(myapp PRIVATE cactus_rt)
target_link_libraries(Hiwonder 

)
