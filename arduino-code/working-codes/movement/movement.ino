#include<ros.h>
#include<std_msgs/String.h>
#include<std_msgs/Int32.h>

#define pwm1 6
#define pwm2 7
#define dir1 4
#define dir2 5

int flag = 5 ;

ros::NodeHandle nh;
std_msgs::String str_msg;
std_msgs::Int32 int_msg;
ros::Publisher chatter_string("chatter_string", &str_msg);
ros::Publisher chatter_int("chatter_int" , &int_msg);
char hello[13] = "hello world";
int odometry= 7;
void messagecb(const std_msgs:: Int32& toggle_msg)
{ 
 flag=toggle_msg.data; 
}

ros::Subscriber<std_msgs::Int32> sub("/directions", &messagecb);
void setup()
{ 
  nh.initNode();
  nh.advertise(chatter_string);
  nh.advertise(chatter_int);
   pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);

   nh.subscribe(sub);
 }

int stopp()
{
  digitalWrite(dir1 , HIGH);
  digitalWrite(dir2 , HIGH);
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);   
              
  }

int forward()
{ 
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  analogWrite(pwm1, 200);
  analogWrite(pwm2, 200);
  
}
                
int backward()
{
  digitalWrite(dir1 , HIGH);
  digitalWrite(dir2 , HIGH);
  analogWrite(pwm1, 205);
  analogWrite(pwm2, 205);
}

  void loop()
  { str_msg.data=hello;
    int_msg.data=flag;
     chatter_string.publish(&str_msg);
     chatter_int.publish(&int_msg);
     if(flag==5)
         stopp();
      else if(flag==8)
          forward();
      else if(flag==2)
          backward();
    else stopp();      
     nh.spinOnce();
     delay(1000);
        
    }
