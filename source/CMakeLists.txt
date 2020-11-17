add_executable(matmult
    matmult.cpp
    )

add_executable(threadID
    threadID.cpp
    )

target_link_libraries(matmult ${LIBRARIES})
target_link_libraries(threadID ${LIBRARIES})

add_executable(tests
    tests.cpp
    )

# generate compile_commands.json
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
