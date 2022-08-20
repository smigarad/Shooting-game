cmake_minimum_required(VERSION 3.0.0)
project(Shooter VERSION 0.1.0)

#set(CMAKE_C_COMPILER_WORKS 1)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -flto -ftree-vectorize -march=native -Ofast -mtune=generic -Dvsync_enabled ")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall -Wextra -fsanitize=address -pedantic ")

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
INCLUDE(FindPkgConfig) 

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fsanitize=address -g -fno-omit-frame-pointer -fno-sanitize-recover")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fno-sanitize-recover")



PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
include_directories(${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE /include)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

