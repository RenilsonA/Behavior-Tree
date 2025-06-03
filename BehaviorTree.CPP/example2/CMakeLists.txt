cmake_minimum_required(VERSION 3.14)
project(TestBehaviorTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")
endif()

include(FetchContent)

FetchContent_Declare(
  BehaviorTree
  GIT_REPOSITORY https://github.com/BehaviorTree/BehaviorTree.CPP.git
  GIT_TAG        master  # ou GIT_TAG 4.5.2, se disponível
)

set(BTCPP_BUILD_TESTS OFF CACHE BOOL "Disable building tests for BehaviorTree.CPP" FORCE)
set(BTCPP_BUILD_EXAMPLES OFF CACHE BOOL "Disable building examples for BehaviorTree.CPP" FORCE)
set(BTCPP_SHARED_LIBS ON CACHE BOOL "Build BehaviorTree.CPP as shared library" FORCE)

FetchContent_MakeAvailable(BehaviorTree)

# Mensagens de depuração (opcionais, podem ser mantidas ou removidas)
message(STATUS "BehaviorTree_SOURCE_DIR: ${BehaviorTree_SOURCE_DIR}")
set(EXPECTED_FILE_LOGGER_PATH "${BehaviorTree_SOURCE_DIR}/include/behaviortree_cpp/loggers/bt_file_logger.h")
if(EXISTS "${EXPECTED_FILE_LOGGER_PATH}")
  message(STATUS "DEBUG: bt_file_logger.h encontrado em: ${EXPECTED_FILE_LOGGER_PATH}")
else()
  message(WARNING "DEBUG: bt_file_logger.h NÃO encontrado em: ${EXPECTED_FILE_LOGGER_PATH}")
endif()

add_executable(main main.cpp)

target_link_libraries(main PRIVATE behaviortree_cpp)

target_include_directories(main PRIVATE
    ${BehaviorTree_SOURCE_DIR}/include
)