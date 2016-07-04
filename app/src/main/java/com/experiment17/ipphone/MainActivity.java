package com.experiment17.ipphone;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Button button = (Button) findViewById(R.id.button);
        if (button != null) {
            button.setOnClickListener(new View.OnClickListener() {
                public void onClick(View view) {
                    EditText edittext1 = (EditText) findViewById(R.id.editText);
                    EditText edittext2 = (EditText) findViewById(R.id.editText2);

                    String ip = edittext1.getText().toString();

                    String portString = edittext2.getText().toString();
                    int port = Integer.parseInt(portString);

                    MyAsyncTask task = new MyAsyncTask(ip, port);
                    task.execute(1);
                }
            });
        }
    }
}
