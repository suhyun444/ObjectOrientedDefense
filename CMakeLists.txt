cmake_minimum_required(VERSION 3.20)
project(ObjectOrientedDefense)

set(CMAKE_CXX_STANDARD 17)

# 버전 3 요구를 2로 낮춤
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(ood ${SOURCES}
        src/MostAdvancedTargeting.cpp)

# SFML 2.x 타겟 링킹 방식 적용
target_link_libraries(ood PRIVATE sfml-graphics sfml-window sfml-system)

# 매 빌드마다 data 디렉토리를 실행파일 옆에 복사
add_custom_target(copy_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:ood>/data
)