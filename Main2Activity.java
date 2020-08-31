package com.loyalhouse;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Request;
import okhttp3.Response;

public class Main2Activity extends AppCompatActivity {


    String url = "http://airaidcom.000webhostapp.com/select.php";
    TextView txt = (TextView)findViewById(R.id.textView2);
   @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        Request request = new Request.Builder().url(url).build();

        Second.client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {

                if(response.isSuccessful()){
                    final String myResponse = response.body().string();
                    myResponse.replaceAll("<br>","\n");
                    Main2Activity.this.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            txt.setText(myResponse);


                        }
                    });

                }
                else{
                    Main2Activity.this.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(getApplicationContext(), "Server not available", Toast.LENGTH_SHORT).show();

                        }
                    });
                }





            }
        });
    }
}