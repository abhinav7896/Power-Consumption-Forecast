package com.loyalhouse;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button deviceControl;
    Button powerCons;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        deviceControl = (Button)findViewById(R.id.button);
        powerCons = (Button)findViewById(R.id.button2);
        deviceControl.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(MainActivity.this, Second.class);
                startActivity(i);
            }
        });
        powerCons.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Uri uri = Uri.parse("http://airaidcom.000webhostapp.com/select.php");
                Intent intent = new Intent(Intent.ACTION_VIEW, uri);
                startActivity(intent);

                //Intent i = new Intent(MainActivity.this, Main2Activity.class);
               // startActivity(i);
            }
        });






    }
}
