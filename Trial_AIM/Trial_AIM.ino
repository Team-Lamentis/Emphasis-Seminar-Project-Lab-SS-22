
String CarOne,CarTwo;
String queue_car[]= {CarOne,CarTwo};

int signal_move = 0;
int signal_wait = 0;

void car_move(void *parameter);
void car_wait(void *parameter);

//TaskHandle_t TaskHandle_1;
//TaskHandle_t TaskHandle_2;











void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  xTaskCreate(car_move, "Car move", 1000, NULL, 1, NULL);
  xTaskCreate(car_wait, "Car wait", 1000, NULL, 1, NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}


      void car_move(void*parameter)
      {

         



            while(1)
        {
               if(queue_car[0]==CarOne)
          {
            Serial.println("car one arrive");

        (void) parameter;
        signal_move=1;
        Serial.println("car move");
          }

          
      
        }
                       
      }


    void car_wait(void*parameter)
      {


               while(1)
        {
           if(queue_car[1]==CarTwo)
          {
        

            Serial.println("car two arrive");
        (void) parameter;
        signal_wait=1;
        Serial.println("car wait");
        }
        }
          
        
     
        
      }
