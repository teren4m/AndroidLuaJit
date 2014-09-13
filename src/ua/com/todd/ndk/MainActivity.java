package ua.com.todd.ndk;

import java.io.UnsupportedEncodingException;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener {
    
	TextView textView;
	EditText textEdit;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        textEdit = (EditText)findViewById(R.id.editText1);
        textView = (TextView)findViewById(R.id.textView1);
        Button button = (Button)findViewById(R.id.button1);
    	button.setOnClickListener(this);
    	
    }

	@Override
	public void onClick(View v) {
		String string = textEdit.getText().toString();
		Log.i("nativeMake",string);
		
		int i = NativeUtils.nativeMake();
        
		byte[] str = {};
		try {
			str = string.getBytes("UTF-8");
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
        NativeUtils.nativeDofile(str);
        
        
        byte[] c = NativeUtils.getBuffer();
        
        String s = "";
		try {
			s = new String(c, "UTF-8");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			Log.i("oops", "error");
		}
        
        
        
        textView.setText(s);    
	} 
}