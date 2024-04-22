add_executable(main
        hc06.c
        funcoes.c
        main.c
)

target_link_libraries(main pico_stdlib freertos hardware_adc)
pico_add_extra_outputs(main)
