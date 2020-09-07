void load_training_sets_from_matrix(){
   
   mem_work_time   = presets_matrix[preset][0];                //WT
   mem_rest_time   = presets_matrix[preset][1];                //RT
   mem_rounds      = presets_matrix[preset][2]/10;   //div10     ROUNDS                                 
   mem_buzz_ms     = presets_matrix[preset][3]*10;   //prdct10   sig_ms
   mem_buzz_no_sig = presets_matrix[preset][4]/10;   //div10     sig_#NO
   
   work_time      = mem_work_time;
   rest_time      = mem_rest_time; 
   rounds         = mem_rounds;
   signal_X_times = mem_buzz_no_sig  ;
   // CONST mem_buzz_ms ; 
}

void store_training_sets_to_matrix(){
  
presets_matrix[preset][0] = mem_work_time ;
presets_matrix[preset][1] = mem_rest_time ;
presets_matrix[preset][2] = mem_rounds*10;           //prdct10
presets_matrix[preset][3] = mem_buzz_ms/10;          //div10 
presets_matrix[preset][4] = mem_buzz_no_sig*10;      //prdct10

}

void setup_param(){
  
static int se=0;
static int dec_se=0;
static int sig_no=0;


  switch(setup_item){
      case 0: mem_work_time=constrain(mem_work_time,10,590);    //setup work time 
              work_time= mem_work_time;
              show_time(work_time,1); 
              dot(mod,true);
              break;
      
      case 1: mem_rest_time=constrain(mem_rest_time,10,590);    // setup rest time
              rest_time= mem_rest_time; 
              show_time(rest_time,3); 
              dot(mod,true);
              break;
      
      case 2: mem_rounds=constrain(mem_rounds,1,50);            // setup rounds
              rounds= mem_rounds; 
              show_time(rounds,9);
              segment (3, 12, 9);
              dot(mod,true);
              break;
       
       case 3: mem_buzz_ms=constrain(mem_buzz_ms,100,2500);      // setup buzz ms 
           
            
               se= mem_buzz_ms/1000; 
               dec_se=(mem_buzz_ms%1000)/100; 
               segment (1, 8, OFF); 
               segment (2, dec_se, 5);
               segment (3, se, 5);
               
               dotObj.setPixelColor(0, dotObj.Color( ON, OFF ,ON));
               dotObj.setPixelColor(1, dotObj.Color( OFF, OFF ,OFF));
               dotObj.show();      
               break;
       
       case 4:  mem_buzz_no_sig=constrain(mem_buzz_no_sig,1,20);   // setup buzz no of signals 
                sig_no=(mem_buzz_no_sig/2);
                dotObj.setPixelColor(0, dotObj.Color( OFF, OFF ,OFF));
                dotObj.show(); 
                segment (3, 14, 5);
                segment (2, sig_no, 5);
                segment (1, 8, OFF);
                break;
      
      case 5:  preset=constrain(preset,0,NO_OF_TOTAL_PRESETS-1);  
               P=preset+1;
               segment (3, 11, mod); //P -2
               segment (2, 13, mod);
               segment (1, P, mod);
               break;

      default:  
       Serial.println(F("ERROR::setup_item"));
      break;
    }
}
