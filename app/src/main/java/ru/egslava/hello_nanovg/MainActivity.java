package ru.egslava.hello_nanovg;

import android.app.Activity;
import android.content.Intent;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends Activity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        AssetManager assets = getAssets();
        copyAssets(assets);
        JNI.setAssets(assets);

        TextView textView = (TextView)findViewById(R.id.logView);


        ((MySurfaceView)findViewById(R.id.surfaceView)).setLogView(textView);




        findViewById(R.id.btnAllocacte).setOnClickListener(v->{
            JNI.allocate();
        });
        findViewById(R.id.btnRemove).setOnClickListener(v->{
            JNI.remove();
        });

        findViewById(R.id.btnFiles).setOnClickListener(v-> startActivity(new Intent(this,FileManActivity.class)));
    }

    private void copyAssets(AssetManager assets) {

        File filesDir = getFilesDir();
        File file = new File(filesDir,"font.ttf");
        try {
            byte [] buffer = new byte[2048];
            InputStream open = assets.open("VarelaRound-Regular.ttf");



            FileOutputStream fileOutputStream = new FileOutputStream(file);
            while (open.read(buffer)!= -1){
                fileOutputStream.write(buffer);
            }

            open.close();
            fileOutputStream.close();

        } catch (IOException e) {
            e.printStackTrace();
        }finally {

        }


        String absolutePath = file.getAbsolutePath();
        JNI.sendFontPath(absolutePath);
        Log.i("Main activity", "copyAssets: " + absolutePath);
    }
}
