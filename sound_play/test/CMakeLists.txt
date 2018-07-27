add_executable(test_sound_play test.cpp)
target_link_libraries(test_sound_play ${catkin_LIBRARIES})
add_dependencies(test_sound_play sound_play_gencpp)
set_target_properties(test_sound_play PROPERTIES OUTPUT_NAME test)

add_executable(orne_say orne_say.cpp)
target_link_libraries(orne_say ${catkin_LIBRARIES})
add_dependencies(orne_say sound_play_gencpp)
set_target_properties(orne_say PROPERTIES OUTPUT_NAME orne_say)
