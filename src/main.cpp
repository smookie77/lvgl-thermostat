#include <display.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 19


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


TaskHandle_t displayTask;
TaskHandle_t readTemp;

float tempC = 0;

void displayTask_code(void * params){
        display_setup();
        Serial.printf("\tStarted displayTask!\n");
        for(;;){
                lv_label_set_text(ui_tempLabel, String(tempC).c_str());
                lv_arc_set_value(ui_Arc1, (int)tempC);
                display_loop();
        }
}


void readTemp_code(void * params){
        sensors.begin();
        Serial.printf("\tStarted readTemp task!\n");

        for(;;){
                Serial.print("Requesting temperatures...");
                sensors.requestTemperatures(); // Send the command to get temperatures
                Serial.println("DONE");
                vTaskDelay(3000/portTICK_PERIOD_MS);
                // After we got the temperatures, we can print them here.
                // We use the function ByIndex, and as an example get the temperature from the first sensor only.
                tempC = sensors.getTempCByIndex(0);
              
                // Check if reading was successful
                if (tempC != DEVICE_DISCONNECTED_C)
                {
                  Serial.print("Temperature for the device 1 (index 0) is: ");
                  Serial.println(tempC);
                }
                else
                {
                  Serial.println("Error: Could not read temperature data");
                }
        }
}


void setup(){
        Serial.begin(921600);
        Serial.printf("A DS18B20 demo with lvgl and tft_espi\n");
        Serial.printf("Starting tasks\n");

        xTaskCreatePinnedToCore(readTemp_code, "temperature task", 1024, NULL, 1, &readTemp, 1);
        xTaskCreatePinnedToCore(displayTask_code, "display task", 1024*10, NULL, 1, &displayTask, 0);

}

void loop(){
}


