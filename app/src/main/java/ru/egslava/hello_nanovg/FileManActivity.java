package ru.egslava.hello_nanovg;

import android.Manifest;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by oleh on 02.12.17.
 */

public class FileManActivity extends AppCompatActivity implements AdapterView.OnItemClickListener,AdapterView.OnItemLongClickListener {
    ListView listView;
    List<File> files;
    FilesAdapter adapter;
    File current;
    private final int requestCode = 7;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.file_activity);
        listView = (ListView) findViewById(R.id.lvFiles);

        findViewById(R.id.btnCreateDir).setOnClickListener(v -> {
            File file ;
            int counter =0;
            do{
                file = new File(current, "NEW_FOLDER" + ((counter == 0) ?"" : (" " + counter )));
                counter++;
            }while (file.exists()&&file.isDirectory());

            boolean mkdir = file.mkdir();
            if(mkdir){
                Toast.makeText(FileManActivity.this,"File created",Toast.LENGTH_SHORT).show();
                loadFiles(current);
            }else{
                Toast.makeText(FileManActivity.this,"Cannot create file",Toast.LENGTH_SHORT).show();
            }
        });
        files = new ArrayList<>();
        adapter = new FilesAdapter(this, android.R.layout.simple_list_item_1, files);


        listView.setAdapter(adapter);
        listView.setOnItemClickListener(this);
        listView.setOnItemLongClickListener(this);
        loadFiles(getFilesDir());
        requestPermission();

    }

    private void loadFiles(File dir) {
        current = dir;
        if (dir.isDirectory()) {
            files.clear();
            files.add(new File("<--"));
            files.addAll(Arrays.asList(current.listFiles()));

            adapter.notifyDataSetChanged();
        } else {

        }
    }

    private void requestPermission() {

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE}, requestCode);
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        File file = files.get(position);
        if (position == 0) {
            loadFiles(current.getParentFile());
        } else {
            loadFiles(current.listFiles()[position - 1]);
        }
        Toast.makeText(this, file.getName(), Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (this.requestCode == requestCode) {
            Toast.makeText(this, "Permission granted", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
        if(position !=0){
            File f = files.get(position);
            boolean delete = f.delete();
            loadFiles(current);
            adapter.notifyDataSetChanged();
            return true;
        }
        return false;
    }
}
