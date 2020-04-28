#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "board.h"
#include "es8388.h"
#include "FaustSawtooth.h"

const char* TAG = "FAUST_EXAMPLE";


extern "C" {
    void app_main(void);
}


void app_main(void)
{
    ESP_LOGI(TAG, "[ 1 ] Start audio codec chip");
    audio_board_handle_t board_handle = audio_board_init();
    audio_hal_ctrl_codec(board_handle->audio_hal, AUDIO_HAL_CODEC_MODE_BOTH, AUDIO_HAL_CTRL_START);
    audio_hal_set_volume(board_handle->audio_hal, 50);

    ESP_LOGI(TAG, "[ 2 ] Faust started");

    int SR = 48000;
    int BS = 32;
    FaustSawtooth faustSawtooth(SR,BS);
    faustSawtooth.start();

    
    while(1) {
        faustSawtooth.setParamValue("freq",rand()%(2000-50 + 1) + 50);
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}
