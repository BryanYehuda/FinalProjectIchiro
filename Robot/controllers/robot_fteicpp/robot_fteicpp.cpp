#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Camera.hpp>
#include <webots/DistanceSensor.hpp>

#define SPEED 1.285
#define TIME_STEP 64

// All the webots classes are defined in the "webots" namespace
#include <bits/stdc++.h>

using namespace std;
using namespace webots;

double left_speed;
double right_speed;

// void turnRight ()
// {
     // for (i = 0; i < 4 ; i++)
    // {
    // wheels[i]->setPosition(INFINITY); //mau melangkah berapa meter
    // wheels[i]->setVelocity(-2.5);
    // }
    // left_speed = 1.0;
    // right_speed = -1.0;
// }

// void turnLeft ()
// {
    // for (i = 0; i < 4 ; i++)
    // {
    // wheels[i]->setPosition(INFINITY); //mau melangkah berapa meter
    // wheels[i]->setVelocity(-2.5);
    // }
    // left_speed = -1.0;
    // right_speed = 1.0;
// }

int Checking (int a, int c, int b, int d, int flag)
{
    if (flag == 2 && d!=b) {
        if (d>b) {
            // turnLeft();
            return 1;
        }
        else {
            // turnRight();
            return 3;
        }
    }   

    else if (flag == 0 && d!=b) {
        if (d>b) {
            // turnRight();
            return 1;
        }
        else {
            // turnLeft();
            return 3;
        }
    }

    else if (flag == 1 && c!=a) {
        if (c>a) {
            // turnRight();
            return 2;
        }
        else {
            // turnLeft();/
            return 0;
        }
    }

    else if (flag == 3 && c!=a) {
        if (c>a) {
            // turnLeft();
            return 2;
        }
        else {
            // turnRight();
            return 0;
        }
    }
    return flag;
}

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  int timeStep = (int)robot->getBasicTimeStep();
  
  /* Get and enable the distance sensors. */
  DistanceSensor *distanceSensor;
  char ds_names[10] = {"ds0"};
  distanceSensor = robot->getDistanceSensor(ds_names);
  // distanceSensor->enable(timeStep);
  
  int i;
 /* Get and enable camera */
  Camera *camera = robot->getCamera("camera");
  camera->enable(2 * TIME_STEP);
  static int width = camera->getWidth(); 
  static int height = camera->getHeight();
  
  int length = 4 * width * height * sizeof(unsigned char);
  
/* Initialize motors */
  Motor *wheels[4];
  char wheels_names[4][8] = {
      "wheel1", "wheel2", "wheel3", "wheel4"
  };
  for (i = 0; i < 4 ; i++)
  {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY); //mau melangkah berapa meter
    wheels[i]->setVelocity(0.0);
  }
  
  int Start[2] = {1,9};
  int Finish[2] = {18,13};
  int Path[400][2] = 
  {
      {1,8},{1,7},{1,6},{1,5},{1,4},{1,3},{1,2},{1,1},{2,1},{3,1},
      {3,2},{3,3},{3,4},{3,5},{3,6},{3,7},{3,8},{4,8},{5,8},{6,8},
      {7,8},{8,8},{9,8},{10,8},{10,9},{10,10},{10,11},{10,12},{11,12},{12,12},
      {12,11},{12,10},{12,9},{12,8},{12,7},{12,6},{12,5},{12,4},{12,3},{13,3},
      {14,3},{14,4},{14,5},{14,6},{14,7},{14,8},{15,8},{16,8},{17,8},{18,8},
      {18,9},{18,10},{18,11},{17,11},{16,11},{15,11},{14,11},{14,12},{14,13},{15,13},
      {16,13},{17,13},{18,13}
  };
  
  // printf ("FTEI Cerdas\n");
  int k = 0;//perulangan path ke-
  int turn = 0, direction = 0, done_turn = 0, counter, left_counter, right_counter;
  
  // for (int m=0;m<63;m++)
  // {
      // cout<<"("<<Path[m][0]<<","<<Path[m][1]<<")"<<endl;
  // }
    
  while (robot->step(timeStep) != -1) {
  
  double left_speed = SPEED;
  double right_speed = SPEED;
  // double ds_values = distanceSensor->getValue();
 
  /* This is used to refresh the camera. */
  // Camera *image = robot->Camera.getImage();
  
    cout<<"turn:"<<turn<<" direction:"<<direction<<" k:"<<k<<" done_turn:"<<done_turn<<endl;
    if (turn == 0 && done_turn>0)
    {
        done_turn--;
        left_speed=SPEED;
        right_speed=SPEED; 
        cout<<"done_turn:"<<done_turn<<"k:"<<k<<endl;
        if (done_turn==1) 
        {
          done_turn--;
          turn = 0;
          k++;
        } 
    }
        
    else if (turn>0 && direction>0 && done_turn ==0)
    {
        turn--;
        if (direction==100)
        {
            left_speed=SPEED;
            right_speed=-SPEED;
            // direction--;
        }
        else if (direction==200)
        {
            left_speed=-SPEED;
            right_speed=SPEED;
            // direction--;
        }
        if (turn==1) 
        {
            done_turn = 194;
            direction = 0;
            turn--;
            // k++;
        }
    }

    else if (turn==0 && direction==0 && done_turn==0)
    {
        int a, b, c, d;
        if (k==0)
        {
            cout<<"hola masuk"<<endl;
            c = Path[k][0]; 
            a = Start[0];
            d = Path[k][1];
            b = Start[1];
        }
        else if (k>0 && k<63)
        {
            cout<<"woi masuk"<<endl;
            c = Path[k][0]; 
            a = Path[k-1][0];
            d = Path[k][1];
            b = Path[k-1][1];   
        }
        else if (k==63)
        {
            c = Finish[0]; 
            a = Path[k-1][0];
            d = Finish[1];
            b = Path[k-1][1];  
        }
       
            
        int flagtemp1, flagtemp2;
            
        if (k==0) flagtemp2=2;
        flagtemp1 = flagtemp2;
        flagtemp2 = Checking (a, c, b, d, flagtemp1);
        cout<<"flagtemp1="<<flagtemp1<<" flagtemp2="<<flagtemp2<<endl;
        if (flagtemp1==flagtemp2) {
            cout<<"kok masuk"<<endl;
            done_turn = 190;
            direction = 0;
        }  
        else if (flagtemp1 == 2) {
             if (flagtemp2==1) {
                direction = 100; //kiri
                turn = 100;
             }
             else if (flagtemp2==3){
                 direction = 200; //kanan
                 turn = 100;
             }
        }  
        else if (flagtemp1 == 0) {
             if (flagtemp2==1){
                direction = 200;
                turn = 100;
            }   
            else if (flagtemp2==3){
                 direction = 100;
                 turn = 100;
            }
        }
        else if (flagtemp1 == 1) {
            if (flagtemp2==2){
                 direction = 200;
                 turn = 100;
            }
            else if (flagtemp2==0){
                direction = 100;
                turn = 100;
            }
        }
        else if (flagtemp1 == 3) {
            if (flagtemp2==2){
                 direction = 100;
                 turn = 100;
            }
            else if (flagtemp2==0){
                 direction = 200;
                 turn = 100;
            }
        }
     
    }

    wheels[0]->setVelocity(left_speed);
    wheels[1]->setVelocity(right_speed);
    wheels[2]->setVelocity(left_speed);
    wheels[3]->setVelocity(right_speed);
    
    if (k>63)
    {
       for (int i=0; i < width; i++) {
         for (int j=0; j< height; j++)
         {
           if(i==0 && j==0)
           {
             counter = 0;
             left_counter = 0;
             right_counter = 0;
           }
           
         
           int r = camera->imageGetRed(camera->getImage(), width, i, j);
           int g = camera->imageGetGreen(camera->getImage(), width, i, j);
           int b = camera->imageGetBlue(camera->getImage(), width, i, j);
            if (r >= 27 && r <= 37 &&
                 g >= 68 && g <= 78 && 
                 b >= 130 && b <= 140)
            {
               if (i<width/2)
               {
                 left_counter++;
               }
               else
               {
                 right_counter++;
               }
               cout<<"ada biru\n";
               counter++;
            }
         }
       }
        
     
    }
       
        if (counter>=2)
        {
           cout<<"left:"<<left_counter<<" right:"<<right_counter<<endl;
           if (right_counter>left_counter)
           {
             left_speed=-0.1;
             right_speed=0.1;
           }
           else
           {
             left_speed=0.1;
             right_speed=-0.1;
           }
           distanceSensor->enable(timeStep);
           double ds_values = distanceSensor->getValue();
           cout<<"ds_values: "<<ds_values<<endl;
           if ((right_counter==left_counter)&& k>65 && ds_values > 5) 
           {
             left_speed=0.0;
             right_speed=0.0;
             
             for (int x=0; x<4; x++)
             {
               wheels[i]->setPosition(0.0);
               break;
             }
           }
           // for (int x=0; x<4;
           wheels[0]->setVelocity(left_speed);
           wheels[1]->setVelocity(right_speed);
           wheels[2]->setVelocity(left_speed);
           wheels[3]->setVelocity(right_speed);
        }
  }
  
  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
