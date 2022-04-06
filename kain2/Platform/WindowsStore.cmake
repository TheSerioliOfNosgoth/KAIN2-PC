if(WINDOWS_STORE)

target_link_directories(${PROJECT_NAME} PUBLIC ${ROOT_DIR}/Build_UWP/Emulator/$(Configuration))
target_link_libraries(${PROJECT_NAME} xaudio2.lib)

set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} /ZW")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} /ZW")
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} /ZW")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /ZW")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /ZW")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /ZW")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(PSX_LIB PSX.lib)

endif()