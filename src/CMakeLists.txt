
add_library(${PROJECT_NAME}_lib RROS.c RROS_TimeCounter.c)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)