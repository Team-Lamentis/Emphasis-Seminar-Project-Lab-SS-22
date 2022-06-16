//create two dummy car
String CarOne,CarTwo;
//put the two dummy car in queue
String queue_car[]= {CarOne,CarTwo};


int signal_move;
int signal_wait;
int signal_cartwo_move;

void car_move(void *parameter);
void car_wait(void *parameter);
void car_communicate(void*parameter);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;

//creating task

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(1200);

  //CreatingTask
  //Task move is created with priority '1'
  xTaskCreate(car_move, "Car move", 1000, NULL, 1, &TaskHandle_1);
  //Task wait is created with priority '1'
  xTaskCreate(car_wait, "Car wait", 1000, NULL, 1, &TaskHandle_2);
  //Task communication of the car is created with priority '2'
  xTaskCreate(car_communicate, "Car communicate", 1000, NULL, 2, &TaskHandle_3);

   
} 

void loop() {}


// task car communicate 
void car_communicate(void*parameter)
      { (void) parameter;
         while(1)
          {         if(queue_car[0]==CarOne)
                {   Serial.println("start");
                    Serial.println("car one arrive and communicate");
                    Serial.println("path available");
                }            
                     if(queue_car[1]==CarTwo)
                {    Serial.println("car two arrive and communicate");
                     Serial.println("path not available");
                }                                        
                     vTaskSuspend(TaskHandle_3);
           }
        }          
         





      

//task car move 
void car_move(void*parameter)
  { (void) parameter;
     TickType_t getTick;
     getTick = xTaskGetTickCount();
     signal_move=1;
         while(1)
      {  if(signal_move==1)
          { Serial.println("Car one move");
            vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
            signal_wait =1;
          }
         vTaskSuspend(TaskHandle_1);
       }
   }     
          
// Task Car Wait 
void car_wait(void*parameter)
  { (void) parameter;
     TickType_t getTick;
     getTick = xTaskGetTickCount();
     signal_wait =1;  
        while(1)
          { if(signal_wait==1)
                { Serial.println("Car two wait");
                  vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                  signal_cartwo_move=1;                  
                }
            if(signal_cartwo_move==1)
                {  Serial.println("Car two move");
                   vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                   Serial.println("end");
                   vTaskResume(TaskHandle_3);
                   vTaskResume(TaskHandle_1);
                 }
           }
    }
