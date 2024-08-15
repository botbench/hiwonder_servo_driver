# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (Hiwonder 
	hiwonder.cxx
	comms_handler.cxx 
)

find_package(JetsonGPIO)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (
	Hiwonder PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	/usr/include/libserial
)

include(FetchContent)
FetchContent_Declare(
	cactus_rt
	GIT_REPOSITORY https://github.com/botbench/cactus-rt.git
	GIT_TAG master
)
FetchContent_MakeAvailable(cactus_rt)


#target_link_libraries(myapp PRIVATE cactus_rt)
target_link_libraries(Hiwonder 
	PUBLIC serial
	PUBLIC JetsonGPIO::JetsonGPIO	
	PUBLIC cactus_rt
)
