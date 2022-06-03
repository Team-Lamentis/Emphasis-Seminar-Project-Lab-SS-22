/////////////////////////////////////////////// create queu ////////////////////////////////////////////////////////////////////////////////
String CarOne,CarTwo;
String queue_car[]= {CarOne,CarTwo};////// tambah car in the queu
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int signal_move = 0;
int signal_wait = 0;

void car_move(void *parameter);
void car_wait(void *parameter);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

//creating task

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  xTaskCreate(car_move, "Car move", 1000, NULL, 1, NULL);
  xTaskCreate(car_wait, "Car wait", 1000, NULL, 1, NULL);
  xTaskCreate(car_communicate, "Car communicate", 1000, NULL, 2, NULL);

   
}

void loop() {}


///////////////////////////////////////////////////////////// task car communicate //////////////////////////////////////////////////////
void car_communicate(void*parameter)
      {
        while(1)
          {
               if(queue_car[0]==CarOne)
                {
                   signal_move= 1;
                   Serial.println("path available");
                   (void) parameter;
                    signal_move=1; Serial.println("car move");
                }


              if(queue_car[1]==CarTwo)
                {
                   signal_wait= 1;
                   Serial.println("path not available");
                   (void) parameter;
                    
                }

               vTaskSuspend(TaskHandle_2); 
          }
                       
      }
      

///////////////////////////////////////////////////////////// task car move ///////////////////////////////////////////////////////////////////////

void car_move(void*parameter)
      { vTaskResume(TaskHandle_1);
        while(1)
          {
               if(signal_move==1)
                {
                   Serial.println("car one arrive");
                   (void) parameter;
                    
                     Serial.println("car move");
                }
          }
                       
      }
      
//////////////////////////////////////////////////////////// Task Car Wait //////////////////////////////////////////////////////////////////////////

void car_wait(void*parameter)
      {    vTaskResume(TaskHandle_1);
           while(1)
               {
                    if(signal_wait==1)
                               {
                                 Serial.println("car two arrive");
                                 (void) parameter;
                                 signal_wait=1;
                                 Serial.println("car wait");
                                }
               }
        
       }
