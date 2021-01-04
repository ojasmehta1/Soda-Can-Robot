#include <kipr/botball.h>

//objectType 0 = Can
//objectType 1 = Drop off
int found;

void ReleaseObject();
void CatchObject();
void find(int objectType)
{
    camera_update();
    set_servo_position(0,0);
	if(get_object_count(0) == 1 && objectType == 0) //if you found the can
    {
     motor(0,0);
     motor(1,0);

     //Move depending on the distance of the object relative to the camera
        if (get_object_center_x(0,0) > 83)
            {
            	motor(0,30);
        		motor(1,15);
            printf("Right\n");
            }
            // if object is towards the left side
            else if (get_object_center_x(0,0) < 73)
            {
            	motor(0,15);
        		motor(1,30);
                printf("Left\n");
            }
            // if object is close, stop
            else if((get_object_center_y(0,0) > 15 && get_object_center_y(0,0) < 20) && (get_object_center_x(0,0) > 73 && get_object_center_x(0,0) < 83))
            {
              motor(0,0);
        	    motor(1,0);
             CatchObject();
             find(1);
            }
    }
 	else if(get_object_count(1) == 1 && objectType == 1)
    {
            // if object is towards the left side
            else if (get_object_center_x(1,0) > 68)
            {
            	motor(0,30);
        		motor(1,15);
                printf("Right\n");
            }
            // if object is towards the left side
            else if (get_object_center_x(1,0) < 58)
            {
            	motor(0,15);
        		motor(1,30);
                printf("Left\n");
            }
            // if object is close, stop
            if(get_object_center_y(1,0) > 44)
            {
             motor(0,0);
        	   motor(1,0);
             ReleaseObject();
            }
    }
    else if (found == 1) //find cube
    {
        motor(0,50);
        motor(1,-50);
    }

}

void CatchObject()
{
    int i = 0;
    enable_servos();
    //Grab the object, servo 0
    //Lift the object, servo 1
    while(i < 788)
    {
    set_servo_position(0, i); //Second value is the closing value of servo 0
    msleep(70);
    i++;
    }
    found = 1;
    set_servo_position(1, 555); //Second value is the lifting value of servo 1
}

void ReleaseObject()
{
        //Lower the object, servo 1
        //Release the object, servo 0
    set_servo_position(1, 1119); //Second value is the opening value of servo 1
    set_servo_position(0, 0); //Second value is the lowering value of servo 0
}
int main()
{
    camera_open();
    found = 0;
    while(1){
        camera_update();
    find(0); // Find can
    }
}
