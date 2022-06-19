//create dummy cars
int A=1;
int B=2;
int C=3;
int D=4;
int F=5;
int G=6;
int H=7;
int I=8;

//create array to store list for car to move
int move_list[4];
//direction of the car
String direction_car[4]={"north","south","west","east"};


int x;
int z;



int signal_wait;

int change =0;



void car_move(void *parameter);
void car_wait(void *parameter);
void car_communicate(void*parameter);


QueueHandle_t Car_Queue;
QueueHandle_t Queue_waiting;
TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
//TaskHandle_t TaskHandle_4;

 








void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(1200);

  //create queue
  Car_Queue = xQueueCreate( 4, sizeof( unsigned int ) );
  //put cars in the queue
  xQueueSendToBack(  Car_Queue, &A, 0);
  xQueueSendToBack(  Car_Queue, &B, 0);
  xQueueSendToBack(  Car_Queue, &C, 0);
  xQueueSendToBack(  Car_Queue, &D, 0);
 
                               
 
 

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
      {  (void) parameter;
             while(1)
                {         
                    //refill car when queue is empty
                      if(uxQueueMessagesWaiting(Car_Queue) == 0 &&  change == 0)
                         {    Serial.println("new car arrive");
                              xQueueSendToBack(  Car_Queue, &F, 0);
                              xQueueSendToBack(  Car_Queue, &G, 0);
                              xQueueSendToBack(  Car_Queue, &H, 0);
                              xQueueSendToBack(  Car_Queue, &I, 0);
                              change =1;
                          }
                    //refill new car when queue is empty
                      if(uxQueueMessagesWaiting(Car_Queue) == 0 &&   change == 1)
                          {   Serial.println("new car arrive");
                              xQueueSendToBack(  Car_Queue, &A, 0);
                              xQueueSendToBack(  Car_Queue, &B, 0);
                              xQueueSendToBack(  Car_Queue, &C, 0);
                              xQueueSendToBack(  Car_Queue, &D, 0);
                              change =0;
                          }
                     // put car in the list to move array
                      if(uxQueueMessagesWaiting(Car_Queue) !=0)
                          {for(int o=0;o<4;o++)
                              {   xQueueReceive(Car_Queue,&x,0);
                                   move_list[o]=x;
                                    Serial.print("car ");
                                    Serial.print(move_list[o] );
                                    Serial.println(" request");
                                    Serial.print("to ");
                                    Serial.print(direction_car[o] );
                                    Serial.println(" ");
                              }
                                    Serial.println("finish request ");    
                          } 
                       vTaskSuspend(TaskHandle_3);
              }
      }
 //task car move 
  void car_move(void*parameter)
  { (void) parameter;
     TickType_t getTick;
     getTick = xTaskGetTickCount();
            while(1)
              { // car move based on list move  
                if(move_list[0]!=0)
                      { Serial.print("car ");
                        Serial.print(move_list[0] );
                        Serial.println(" move");
                        signal_wait=1;
                      }
                  vTaskSuspend(TaskHandle_1);
                  if(move_list[1]!=0)
                      { Serial.print("car ");
                        Serial.print(move_list[1] );
                        Serial.println(" move");
                      }
                   if(move_list[2]!=0)
                      { Serial.print("car ");
                        Serial.print(move_list[2] );
                        Serial.println(" move");
                      }
                   if(move_list[3]!=0)
                      { Serial.print("car ");
                        Serial.print(move_list[3] );
                        Serial.println(" move");
                      }
                   Serial.println("finish move");
                   vTaskResume(TaskHandle_3);S
              }    
}

   
// Task Car Wait 
void car_wait(void*parameter)
  { (void) parameter;
     TickType_t getTick;
     getTick = xTaskGetTickCount();
        while(1)
          { // car wait based on list move and signal wait 
            if(move_list[1]!=0 && signal_wait==1)
                {
                  Serial.print("car ");
                  Serial.print(move_list[1] );
                  Serial.println(" wait");
                  Serial.print("car ");
                  Serial.print(move_list[2] );
                  Serial.println(" wait");
                  Serial.print("car ");
                  Serial.print(move_list[3] );
                  Serial.println(" wait");
                  signal_wait=0;
               }
             vTaskResume(TaskHandle_1);
         }
  }




















    
