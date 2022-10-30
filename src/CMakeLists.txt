
add_library(${PROJECT_NAME} RROS.c RROS_TimeCounter.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)