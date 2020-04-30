#include "Flute/Flute.h"
#include "board.h"
#include "es8388.h"
#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpr/mpr.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "protocol_examples_common.h"

const char* TAG = "FAUST_EXAMPLE";

extern "C" {
void app_main(void);
}

Flute* flute;

void handler(mpr_sig sig, mpr_sig_evt evt, mpr_id inst, int length, mpr_type type,
          const void* value, mpr_time time) {
  const char* signalName = mpr_obj_get_prop_as_str(sig, MPR_PROP_NAME, NULL);
  flute->setParamValue(signalName, *((float*) value));
}

void app_main(void) {
  // ESP_LOGI(TAG, "[ 0 ] Connect to WiFi");
  // // Connect to Wifi
  // ESP_ERROR_CHECK(nvs_flash_init());
  // esp_netif_init();
  // ESP_ERROR_CHECK(esp_event_loop_create_default());
  // ESP_ERROR_CHECK(example_connect());

  // // Disable WiFi power save (huge latency improvements)
  // esp_wifi_set_ps(WIFI_PS_NONE);

  // ESP_LOGI(TAG, "[ 1 ] Create libmapper device");
  // mpr_dev dev = mpr_dev_new("Flute", 0);
  // float freqMin = 20.0f, freqMax = 20000.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "freq", 1, MPR_FLT, "Hz", &freqMin, &freqMax, 0, handler, MPR_SIG_UPDATE);
  // float bendMin = 0.0f, bendMax = 10.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "bend", 1, MPR_FLT, 0, &bendMin, &bendMax, 0, handler, MPR_SIG_UPDATE);
  // float gainMin = 0.0f, gainMax = 1.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "gain", 1, MPR_FLT, 0, &gainMin, &gainMax, 0, handler, MPR_SIG_UPDATE);
  // float envAttackMin = 0.0f, envAttackMax = 30.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "envAttack", 1, MPR_FLT, 0, &envAttackMin, &envAttackMax, 0, handler, MPR_SIG_UPDATE);
  // int sustainMin = 0, sustainMax = 1;
  // mpr_sig_new(dev, MPR_DIR_IN, "sustain", 1, MPR_INT32, 0, &sustainMin, &sustainMax, 0, handler, MPR_SIG_UPDATE);
  // float mouthPositionMin = 0.0f, mouthPositionMax = 1.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "mouthPosition", 1, MPR_FLT, 0, &mouthPositionMin, &mouthPositionMax, 0, handler, MPR_SIG_UPDATE);
  // float vibratoFreqMin = 0.0f, vibratoFreqMax = 10.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "vibratoFreq", 1, MPR_FLT, 0, &vibratoFreqMin, &vibratoFreqMax, 0, handler, MPR_SIG_UPDATE);
  // float vibratoGainMin = 0.0f, vibratoGainMax = 1.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "vibratoGain", 1, MPR_FLT, 0, &vibratoGainMin, &vibratoGainMax, 0, handler, MPR_SIG_UPDATE);
  // float outGainMin = 0.0f, outGainMax = 1.0f;
  // mpr_sig_new(dev, MPR_DIR_IN, "outGain", 1, MPR_FLT, 0, &outGainMin, &outGainMax, 0, handler, MPR_SIG_UPDATE);
  // int gateMin = 0, gateMax = 1;
  // mpr_sig_new(dev, MPR_DIR_IN, "gate", 1, MPR_INT32, 0, &gateMin, &gateMax, 0, handler, MPR_SIG_UPDATE);

  ESP_LOGI(TAG, "[ 2 ] Start audio codec chip");
  audio_board_handle_t board_handle = audio_board_init();
  audio_hal_ctrl_codec(board_handle->audio_hal, AUDIO_HAL_CODEC_MODE_BOTH,
                       AUDIO_HAL_CTRL_START);
  audio_hal_set_volume(board_handle->audio_hal, 90);

  ESP_LOGI(TAG, "[ 3 ] Faust started");

  int SR = 48000;
  int BS = 128;
  flute = new Flute(SR, BS);
  flute->start();
  // flute->setParamValue("gate", 1);

  const uint8_t MAJOR_PENTATONIC[5] = { 0, 2, 4, 7, 9 };

  const uint8_t key = 55;
  flute->keyOn(0, key, 100);
  flute->setParamValue("envAttack", 200);

  while (1) {
    // mpr_dev_poll(dev, 0);
    const uint8_t key2 = 60 + MAJOR_PENTATONIC[esp_random() % 5];
    flute->keyOn(0, key2, 100);
    vTaskDelay(10000);
    flute->keyOff(0, key2, 0);
    vTaskDelay(250);

  }
}
