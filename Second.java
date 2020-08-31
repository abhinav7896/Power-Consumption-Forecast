package com.loyalhouse;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

import static android.widget.Toast.*;

public class Second extends AppCompatActivity {


    Button enter;
    EditText txt;
    TextView myText;
    public static OkHttpClient client;
    public static String url;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        enter = (Button)findViewById(R.id.button5);
        txt = (EditText)findViewById(R.id.editText);
        myText = (TextView)findViewById(R.id.textView);
        enter.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {

               client = new OkHttpClient();
               url = txt.getText().toString();
               Request request = new Request.Builder().url(url).build();

               client.newCall(request).enqueue(new Callback() {
                   @Override
                   public void onFailure(Call call, IOException e) {
                       e.printStackTrace();
                   }

                   @Override
                   public void onResponse(Call call, Response response) throws IOException {
                       if(response.isSuccessful()){
                           final String myResponse = response.body().string();
                           Second.this.runOnUiThread(new Runnable() {
                               @Override
                               public void run() {
                                   Intent i = new Intent(Second.this, Third.class);
                                   startActivity(i);

                               }
                           });

                       }
                    else
                       {
                           Second.this.runOnUiThread(new Runnable() {
                               @Override
                               public void run() {
                                   Toast.makeText(getApplicationContext(), "Controller not available", Toast.LENGTH_SHORT);

                               }
                           });
                       }
                   }

               });
           }
           });
       }

}
