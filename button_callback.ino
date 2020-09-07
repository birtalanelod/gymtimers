

//===================================================_SINGLE_CLICK_==========================================================
void built_in_bt_clicked() { // CLICK  

 switch (mod){
  
  case 0:  if( preset<NO_OF_QUICK_PRESETS-1){ preset++;                                    //change PRESET OR CountTimeStopped
                                              preset=constrain(preset,0,NO_OF_QUICK_PRESETS-1); 
                                              P=preset+1;   // -2-
                                              dot(0,false);
                                              segment (3, 13, 6); 
                                              segment (2, P, 6);
                                              segment (1, 13, 6);
                                              show_type=3;
                                       }else{ preset=0;
                                              show_type=3;
                                              mod=9;  }   
            break;
  case 1:   mod=2;             // WT PLAY  --> WT PAUSE
            mute=true;
            break;
  case 2:   mod=1;             //  WT PAUSE --> WT PLAY        
            break;
  case 3:   mod=4;             // RT PLAY  --> RT PAUSE
            mute=true;
            break;
  case 4:   mod=3;             // WT PAUSE --> WT PLAY                       
            break;
  case 5:   mod=0;            //RAINBOW  --> STOP
            show_type=3;        
            break;
  case 6:                  // SETUP increment parameters in "RAM"
     switch(setup_item){
      case 0: mem_work_time += sec_increment_value;   
              break;
      case 1: mem_rest_time += sec_increment_value;   //2 p
              break;
      case 2: mem_rounds++; 
              break;
      case 3: mem_buzz_ms +=100;
              break;  
      case 4: mem_buzz_no_sig += 2;
              break;
      case 5: preset++;
              break;
      default:  
              break;
    
  }
      break;
  case 7:   mod=8;   // CT PLAY  --> CT PAUSE
            break;
  case 8:   mod=7;   // CT PAUSE --> CT PLAY                   
            break;
  case 9:   mod=0;   // CT STOPPED
            show_type=3;
            P=preset+1;   // -1-
            dot(0,false);
            segment (3, 13, 6); 
            segment (2, P, 6);
            segment (1, 13, 6);
            break;
  
  
  default:  mod=0;
            break;
          }

} 
//===================================================_DOUBLE CLICK_==========================================================
void built_in_bt_double_clicked() { 
  // This function will be called when the button was pressed 2 times in a short timeframe.

switch (mod){
  case 0:  mod=1;
           buzzer_ms.restart();
           break;   
  case 1:  mod=0;         // WT_PLAY -->  STOPPED 
           show_type=3;
           mute=true;
           break;         
  case 2:  mod=0;         // WT_PAUSE -->  STOPPED 
           show_type=3;
           break;
  case 3:  mod=0;         // RT_PLAY -->  STOPPED 
           show_type=3;
           mute=true;
           break;
  case 4:  mod=0;        // RT_PAUSE -->  STOPPED 
           show_type=3;
           break;
  case 5:  mod=0;        
           show_type=3;
           break;
           
  case 6:  switch(setup_item){ // SETUP decrement parameters in "RAM"
      
              case 0: mem_work_time -= sec_increment_value;
                      break;
              case 1: mem_rest_time -= sec_increment_value; 
                      break;        
              case 2: mem_rounds--; 
                      break;
              case 3: mem_buzz_ms -=100;
                      break;  
              case 4: mem_buzz_no_sig -= 2;
                      break;
              case 5: preset--;
                      break;
              default:  
                       break; 
                       }
            break;

  case 7: mod=9;      // CT_PLAY --> CT_STOPPED 
          count_time=0;  
          break;      
  case 8: mod=9;     // CT_PAUSE -->  CT_STOPPED 
          break;
  case 9: mod=7;    // CT_STOPPED -->  CT_PLAY
          break;
  default: mod=5;    // ANIMATE TO RAINBOW ;)
           break;
   }
}
//===============================================_LONG_PRESS_STOP_=============================================================m

void built_in_bt_long_press_stop(){ //  (press and hold the button , count up to 3 and than release the button to achive this action )

  if (mod==6 ){ setup_item++; }else{mod=6;}
  
  if (setup_item==5){
    setup_item=0;
    write_eeprom=true;
    mod=0;
  }
}
