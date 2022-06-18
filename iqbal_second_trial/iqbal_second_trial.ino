/////////////////////////////////////////////// create queu ////////////////////////////////////////////////////////////////////////////////
String CarX,CarY,CarZ,CarA;
String queue_car[4]= {CarX,CarY,CarZ,CarA};////// tambah car in the queu
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int signal_move;
int signal_wait;
int signal_cartwo_move;

void car_move(void *parameter);
void car_wait(void *parameter);
void car_communicate(void*parameter);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_3;
TaskHandle_t TaskHandle_4;


//creating task

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(1200);

  xTaskCreate(car_move, "Car move", 1000, NULL, 1, &TaskHandle_1);
 // xTaskCreate(car_wait, "Car wait", 1000, NULL, 1, NULL);
  xTaskCreate(car_communicate, "Car communicate", 1000, NULL, 2, &TaskHandle_3);
  //xTaskCreate(changing_queue, "Change Queue", 1000, NULL, 0, &TaskHandle_4);
   
} 

void loop() {}


///////////////////////////////////////////////////////////// task car communicate //////////////////////////////////////////////////////

void car_communicate(void*parameter)
      {
        (void) parameter;
        
           
    
        while(1)
          {
                 
                if(queue_car[0]==CarX)
                {
                     
                     Serial.println("car X arrive and north");
                    
                     
                                      
                }

          
                
               if(queue_car[1]==CarY)
                {

                     Serial.println("car Y arrive and east");
               
                     
                                      
                }
                if(queue_car[2]==CarZ)
                {
                     
                     Serial.println("car Z arrive and west");
                  
                     
                                      
                }

          vTaskSuspend(TaskHandle_3);
                  
                
               if(queue_car[3]==CarA)
                {

                     Serial.println("car A and south");
                     
                     
                                      
                }
                 


                  


            
          }






      }





      

///////////////////////////////////////////////////////////// task car move ///////////////////////////////////////////////////////////////////////

void car_move(void*parameter)
         
          {
          (void) parameter;
           TickType_t getTick;
           getTick = xTaskGetTickCount();
           signal_move=1;

                while(1)
          {
                 
                if(signal_move==1 && queue_car[0]==CarX )

                {
                    Serial.println("Car X move");
                    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                    signal_wait =1;
                    

                  
                }


                if(signal_move==1 && queue_car[0]==CarY )

                {
                    Serial.println("Car X move");
                    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                    signal_wait =1;
                    

                  
                }
                if(signal_move==1 && queue_car[0]==CarZ )

                {
                    Serial.println("Car X move");
                    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                    signal_wait =1;
                    

                  
                }
                if(signal_move==1 && queue_car[0]==CarA )

                {
                    Serial.println("Car X move");
                    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                    signal_wait =1;
                    

                  
                }
                 vTaskResume(TaskHandle_3);
                

                
                  


            
          }






          }     
          
//////////////////////////////////////////////////////////// Task Car Wait //////////////////////////////////////////////////////////////////////////
/*
void car_wait(void*parameter)
{
                (void) parameter;
               TickType_t getTick;
              getTick = xTaskGetTickCount();
              signal_wait =1;


      
        while(1)
          {
                
                if(signal_wait==1)

                {
                    
                    Serial.println("Car two wait");
                    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);

                    signal_cartwo_move=1;

                  
                }

                
                
                if(signal_cartwo_move==1)
                {


                    Serial.println("Car two move");
                    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);
                    Serial.println("end");
                    vTaskResume(TaskHandle_3);
                    vTaskResume(TaskHandle_1);
                  
                }
                 
                  


            
          }






*/









            
