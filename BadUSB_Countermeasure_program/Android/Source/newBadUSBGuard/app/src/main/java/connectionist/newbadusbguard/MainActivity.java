package connectionist.newbadusbguard;

import android.app.admin.DevicePolicyManager;
import android.content.ComponentName;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {


    Toast toast;
    DevicePolicyManager mDPM;
    ComponentName compname;

    long current_time;
    long previous_time;
    long time_interval;
    int detect=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        compname = new ComponentName(this, LockScreenReceiver.class);
    }


    public boolean onKeyUp(int keyCode, KeyEvent event) {
       /* switch (keyCode) {
            case KeyEvent.KEYCODE_D:
                //toast = Toast.makeText(this, "DDD", Toast.LENGTH_SHORT);
                //toast.show();
               //mDPM.lockNow();
                //toast = Toast.makeText(this, Long.toString(time_interval), Toast.LENGTH_SHORT);



                return true;
            case KeyEvent.KEYCODE_F:
                toast = Toast.makeText(this, "Key F", Toast.LENGTH_SHORT);
                toast.show();
                return true;
            case KeyEvent.KEYCODE_J:
                toast = Toast.makeText(this, "Key J", Toast.LENGTH_SHORT);
                toast.show();
                return true;
            case KeyEvent.KEYCODE_K:
                toast = Toast.makeText(this, "Key K", Toast.LENGTH_SHORT);
                toast.show();
                return true;
            default:
                return super.onKeyUp(keyCode, event);

        }
        */

        previous_time = current_time;
        current_time = System.currentTimeMillis();
        time_interval = current_time - previous_time;

        if(time_interval<=1000){
            detect = 1;
        }

        if(detect==1){
            toast = Toast.makeText(this, "Time Interval : "+Long.toString(time_interval)+"ms"+"\n"+"BadUSB DETECTED!!!", Toast.LENGTH_LONG);
            toast.show();
            detect=0;
        }

        return true;
    }

}
