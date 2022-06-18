//create two dummy car

//put the two dummy car in queue
int queue_car[4]= {1,2,3,4};


int signal_move;
int signal_wait;
int signal_cartwo_move;

void car_move(void *parameter);
void car_wait(void *parameter);
void car_communicate(void*parameter);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
TaskHandle_t TaskHandle_4;

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
  xTaskCreate(change_queue, "change queue", 1000, NULL, 0, &TaskHandle_4);

   
} 

void loop() {}


// task car communicate 
void car_communicate(void*parameter)
      { (void) parameter;
         while(1)
          {         if(queue_car[0]!=0)

            {
                Serial.print(queue_car[0] );
                Serial.println(" request to south");
                


              }

              if(queue_car[1]!=0)

            {
                Serial.print(queue_car[1] );
                Serial.println(" request to north ");
                


              }



              if(queue_car[2]!=0)

            {
                Serial.print(queue_car[2] );
                Serial.println(" request to east");
                


              }



                if(queue_car[3]!=0)

            {
                Serial.print(queue_car[3] );
                Serial.println(" request to west");
                


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
      {  


                   if(queue_car[0]!=0)

            {
                
                Serial.print(queue_car[0] );
                Serial.println(" move");
                signal_wait=1;

              }
              vTaskSuspend(TaskHandle_1);

              if(queue_car[1]!=0)

            {
                Serial.print(queue_car[1] );
                Serial.println(" move");
              


              }

                


              if(queue_car[2]!=0)

            {
                Serial.print(queue_car[2] );
                Serial.println(" move");
                

              }
                


                if(queue_car[3]!=0)

            {
                Serial.print(queue_car[3] );
                Serial.println(" move");
               


              }


              vTaskResume(TaskHandle_3);
   }    
  } 
          
// Task Car Wait 
void car_wait(void*parameter)
  {
    
  
    (void) parameter;
  
     TickType_t getTick;
     getTick = xTaskGetTickCount();
     
        while(1)
          { 


            

              if(queue_car[1]!=0 && signal_wait==1)

            {
                Serial.print(queue_car[1] );
                Serial.println(" wait");
                Serial.print(queue_car[2] );
                Serial.println(" wait");
                Serial.print(queue_car[3] );
                Serial.println(" wait");
                signal_wait=0;
              }

              
              vTaskResume(TaskHandle_1);
                vTaskSuspend(TaskHandle_1);
                  vTaskSuspend(TaskHandle_2);
    }



  }
void change_queue(void*parameter)
{
        (void) parameter;

        while(1)
        {
          queue_car[0]=queue_car[1];
          queue_car[1]=queue_car[2];
          queue_car[2]=queue_car[3];
          queue_car[3]=queue_car[0];

           vTaskResume(TaskHandle_3);
             vTaskResume(TaskHandle_2);
              vTaskResume(TaskHandle_1);

          



          
        }

           

  
}



















    
