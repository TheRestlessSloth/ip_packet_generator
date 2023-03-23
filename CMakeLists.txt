# CMakeList.txt: проект CMake для ip_packet_generator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("ip_packet_generator")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (ip_packet_generator "ip_packet_generator.cpp" "ip_packet_generator.h" "CMDA.h" "CMDA.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ip_packet_generator PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
