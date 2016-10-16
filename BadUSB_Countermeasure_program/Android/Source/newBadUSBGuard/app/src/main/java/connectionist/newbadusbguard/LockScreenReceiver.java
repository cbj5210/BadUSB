package connectionist.newbadusbguard;

/**
 * Created by cbj on 2016-09-30.
 */

import android.app.admin.DeviceAdminReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;



public class LockScreenReceiver extends DeviceAdminReceiver{

    @Override
    public void onEnabled(Context context, Intent intent){
        super.onEnabled(context, intent);
        Toast.makeText(context, "BadUSB Detected!", Toast.LENGTH_LONG).show();
    }



}
