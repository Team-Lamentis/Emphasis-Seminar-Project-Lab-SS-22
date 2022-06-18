

String CarA = "Car A";
String CarB= "Car B";
String CarC= "Car C";
String CarD= "Car D";
String CarE= "Car E";
String South= "South";
String North = "North";
String East = "East";
String West = "West";
String carNew = "New Car";

String x;
String y;
String z;
String a;

      
int signal_move;
int signal_wait;

QueueHandle_t Car_Queue;
QueueHandle_t Waiting_queue;
QueueHandle_t Direction_queue;


//Task
void car_move(void *parameter);
void car_wait(void *parameter);
void car_communicate(void*parameter);
void newcar_enter(void*parameter);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
TaskHandle_t TaskHandle_4;


//creating task

void setup() {
  // put your setup code here, to run once:

  Car_Queue = xQueueCreate( 5, sizeof( String ) );
  Waiting_queue = xQueueCreate( 5, sizeof( String ) );
  Direction_queue = xQueueCreate( 4, sizeof( String ) );

   

  xQueueSendToBack( Car_Queue,&CarA,100);
  xQueueSendToBack(  Car_Queue,&CarB,100);
  xQueueSendToBack(  Car_Queue,&CarC,100);
  xQueueSendToBack(  Car_Queue,&CarD,100);
  xQueueSendToBack(  Car_Queue,&CarE,100);
  xQueueSendToBack( Direction_queue,&South,100);
  xQueueSendToBack(  Direction_queue,&North,100);
  xQueueSendToBack(  Direction_queue,&East,100);
  xQueueSendToBack(  Direction_queue,&West,100);
    
  
  Serial.begin(1200);

  //CreatingTask
  //Task move is created with priority '1'
  xTaskCreate(car_move, "Car move", 1000, NULL, 1, &TaskHandle_1);
  //Task wait is created with priority '1'
  xTaskCreate(car_wait, "Car wait", 1000, NULL, 1, &TaskHandle_2);
  //Task communication of the car is created with priority '1'
  xTaskCreate(car_communicate, "Car communicate", 1000, NULL, 1, &TaskHandle_3);
  //Task to add car in queue after queue fully utilised with priority '1'
  xTaskCreate(newcar_enter, "Car new", 1000, NULL, 1, &TaskHandle_4);

   
} 

void loop() {}


// task car communicate 
void car_communicate(void*parameter)
      { (void) parameter;
          TickType_t getTick;
          getTick = xTaskGetTickCount();
              while(1)
         
                {      
                        
                               
                      if(uxQueueMessagesWaiting(Car_Queue) != 0 && uxQueueMessagesWaiting(Direction_queue) != 0 )
                      {
xQueueReceive(Car_Queue,&x,0);
xQueueReceive(Direction_queue,&a,0);
                          Serial.println(x);
                          Serial.println("request ");
                          Serial.println("To direction ");
                          Serial.println(a);
                          vTaskDelay(1000 / portTICK_PERIOD_MS);
                         xQueueSendToBack(Waiting_queue ,&x,100);
                         signal_move=1;
                         signal_wait =1;
                                                                            
                      }
                      else{
                         vTaskDelay(300 / portTICK_PERIOD_MS);
                         }
                      //vTaskSuspend(TaskHandle_3);
                 }
       }          
         


//task car move 
void car_move(void*parameter)
  { (void) parameter;
     TickType_t getTick;
     getTick = xTaskGetTickCount();
     signal_move=1;
     
         while(1)
      {  
        
                 if(uxQueueMessagesWaiting( Waiting_queue ) != 0)
                      { 
                        xQueueReceive(Waiting_queue,&y,0);   
                          Serial.println("Move ");
                          Serial.println(y);
                          vTaskDelay(5000 / portTICK_PERIOD_MS);
                      }
                  else 
                      {
                        y = ""; 
                        vTaskDelay(300 / portTICK_PERIOD_MS);       
                      }
      }
  }     
          
// Task Car Wait 
void car_wait(void*parameter)
  { (void) parameter;
     TickType_t getTick;
     getTick = xTaskGetTickCount();
     signal_wait =1;  
        while(1)
          { 
            
                    if(uxQueueMessagesWaiting( Waiting_queue ) != 0 && y!="") //
                      {   xQueuePeek( Waiting_queue,&z,0);

                          Serial.print("Wait ");
                          Serial.println(z);
                          vTaskDelay(2000 / portTICK_PERIOD_MS);


                
           }
           else{
                         vTaskDelay(300 / portTICK_PERIOD_MS);
                         }
          }
    }


void newcar_enter(void*parameter)
 {  
        while(1)
          {
          
              Serial.println("new car is coming");
              String ok = xQueueSend(Car_Queue,&carNew,500);
              puts (ok ? "OK" : "FAILED");
              vTaskDelay(300 / portTICK_PERIOD_MS);
              
          
          }
         
   
 }
