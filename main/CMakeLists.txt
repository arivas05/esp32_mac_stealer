set(srcs "main.c" "sd_card_io.c" "ble_discovery.c" "fnv1a.c")

idf_component_register(SRCS ${srcs}
                       PRIV_REQUIRES bt nvs_flash
                       INCLUDE_DIRS "."
                       REQUIRES fatfs sd_card
                       WHOLE_ARCHIVE)

if(NOT CONFIG_SOC_SDMMC_HOST_SUPPORTED)
    fail_at_build_time(sdmmc "No SDMMC Host supported. Please refer README.md for more details")
endif()
