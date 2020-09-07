
//------------------------------------------------LYBRARYS_DEPENDENCY-------------------------------------------  
#include <Chrono.h>
#include <Adafruit_NeoPixel.h>
#include "ButtonKing.h"
#include <EEPROM.h>

#define MAX_COUNT_UP_TIME 35939 //(((9h*60 )+59m)*60s)-1s
#define NO_OF_QUICK_PRESETS 5
#define NO_OF_TOTAL_PRESETS 9
//-----------------------------------------=== ESP_8266_D1_Mini_CONNECTIONS===----------------------------------
const byte BUZZER_PIN = D5;      
const byte PIXELS_PIN = D6;        
const byte DOT_PIN = D7;          
const byte BUILTIN_BUTTON_PIN = D4;
const byte NUMPIXELS = 21;            //number of LED's

//-----------------------------------------------OBJIECTS_&_VARIABLES--------------------------------------------
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXELS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dotObj = Adafruit_NeoPixel(2, DOT_PIN, NEO_GRB + NEO_KHZ800);
Chrono timer_ms;                                                          // http://sofapirate.github.io/Chrono/
Chrono buzzer_ms; 
ButtonKing built_in_bt (BUILTIN_BUTTON_PIN , true);

byte c_matrix[10][3] = {           // color matrix referenced by disply stuff and others
  //  R,  G,  B
  {0, 0, 0},                 // MOD 0 STOPPED            BLACK
  {0, 255, 0},               // MOD 1 work_time_play     GREEN
  {0, 150, 70},              // MOD 2 work_time_paused   CIAN
  {255,  0, 0},              // MOD 3 rest_time_play     RED
  {180, 50,0},               // MOD 4 rest_time_paused   ORANGE
  {255, 0, 255},             // MOD 5 rainbow            PURPLE
  {255, 255, 255 },          // MOD 6 setup_mode         WHITE
  {0, 0, 255},               // MOD 7 count_up_play      BLUE
  {50,0, 170},               // MOD 8 count_up_paused    PINKISH
  {255,200,0}                // MOD 9 ct_stopped rounds  YELLOW
};

int presets_matrix[10][5] = {                  //  presets_matrix[set][param]   working sets, load up from eeprom 
  //  0-WT, 1-RT, 2-R/10, 3-BZms, 4-BZ#sg/10
  {300, 30, 40,  400 , 90},         //WS 0 regular training
  {360, 120, 100, 500, 90},         //WS 1 open mat training
  {20,  10, 80 , 200 , 50},         //WS 2 tabata 
  {180, 59, 30 , 400 , 90},         //WS 3
  {240, 59, 40 , 400 , 90},         //WS 4 
  {300, 59, 50 , 400 , 90},         //WS 5 
  {360, 59, 60 , 400 , 90},         //WS 6 
  {420, 59, 70 , 400 , 90},         //WS 7 
  {480, 59, 80 , 400 , 90},         //WS 8 
  {540, 59, 90 , 400 , 90}          //WS 9 

};

const byte sec_increment_value=10;
const byte OFF=0;
const byte ON=255;

// "ROM" or training set parameters read from   presets_matrix[set][param] matrix
int mem_work_time ;   
int mem_rest_time ;  
int mem_rounds  ;   
int mem_buzz_ms  ;   
int mem_buzz_no_sig  ;   

// "RAM" values decremented /incremented during counting 
int work_time ;
int rest_time ;
int rounds ;
int count_time=0;

byte signal_X_times ;
bool buzzer_status=true;
bool mute=false;
int P=0;

byte eeprom_adr=0;
byte eeprom_io=0;
bool write_eeprom=false;

byte preset=0;
byte mod=10;
byte setup_item=0;
int  refresh_ms=1 ;
byte show_type=3;

unsigned long loop_started=0;
unsigned long loop_time=0;


void setup() {

  pinMode(BUZZER_PIN , OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.begin(115200);
  Serial.println();
  Serial.println(F("BBJ TIMER"));
  Serial.print(F("VER: "));
  Serial.println(F(__DATE__)); //2020.08.26
  Serial.print(F("BUILD: "));
  Serial.println(F(__TIME__));
  Serial.println(F("www.gymtimers.hu by Elod Birtalan "));
  
  strip.begin();
  dotObj.begin();
  delay(30);
  dot(5,false); 
  color_wipe (5);
  
  built_in_bt.setClick(built_in_bt_clicked);
  built_in_bt.setDoubleClick(built_in_bt_double_clicked);
  built_in_bt.setLongClickStop(built_in_bt_long_press_stop);


 EEPROM.begin(512);
 read_presets_from_eeprom();
 load_training_sets_from_matrix();  
 
 buzzer_ms.stop();
           
}

void loop() {
//loop_started=millis();

built_in_bt.isClick(); // check built in button if was  short or  doubble pressed or  longpress released  (count up to 3 and than release the button)

Timer();         // light up the LED 's in a time and culture pre-dertiminated logic

if(write_eeprom){
  store_training_sets_to_matrix();
  write_presets_to_eeprom();
  write_eeprom=false;
  Serial.println(F("Checking..."));
  read_presets_from_eeprom();
}

sound();              // drive piezzo buzzer and neighbours into madness 

}
//loop_time=millis()-loop_started;
//Serial.println(loop_time);
