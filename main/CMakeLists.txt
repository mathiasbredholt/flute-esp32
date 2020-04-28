idf_component_register(SRCS "main.cpp" "${CMAKE_CURRENT_BINARY_DIR}/FaustSawtooth.cpp"
                       INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
                       REQUIRES audio_sal audio_hal esp_dispatcher esp_peripherals display_service)

add_custom_command(OUTPUT FaustSawtooth.h FaustSawtooth.cpp
     COMMAND faust2esp32 -lib ${COMPONENT_DIR}/FaustSawtooth.dsp && unzip -jo FaustSawtooth.zip && rm FaustSawtooth.zip
     DEPENDS ${COMPONENT_DIR}/FaustSawtooth.dsp
     COMMENT "Compiling faust..."
     VERBATIM)

add_custom_target(FaustSawtooth DEPENDS FaustSawtooth.h FaustSawtooth.cpp)
add_dependencies(${COMPONENT_LIB} FaustSawtooth)

set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
     ADDITIONAL_MAKE_CLEAN_FILES FaustSawtooth.h FaustSawtooth.cpp)
