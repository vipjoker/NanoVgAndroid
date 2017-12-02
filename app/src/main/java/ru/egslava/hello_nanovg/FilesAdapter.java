package ru.egslava.hello_nanovg;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;
import java.sql.Array;
import java.util.List;

/**
 * Created by oleh on 02.12.17.
 */

public class FilesAdapter extends ArrayAdapter<File> {
    public FilesAdapter(@NonNull Context context, int resource, @NonNull List<File> objects) {
        super(context, resource, objects);
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        if(convertView == null){
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.file_item,parent,false);
            Holder holder = new Holder();

            holder.textView = (TextView) convertView.findViewById(R.id.tvItem);
            holder.imageView = (ImageView) convertView.findViewById(R.id.ivItemIcon);
            holder.description = (TextView)convertView.findViewById(R.id.tvItemDesc);
            convertView.setTag(holder);
        }
        Holder holder = (Holder)convertView.getTag();
        File item = getItem(position);
        if(item != null) {
            holder.imageView.setVisibility(item.isDirectory() ? View.VISIBLE : View.GONE);
            holder.textView.setText(item.getName());
            holder.description.setText(String.format("%d Kb",item.length()/1_000));
        }


        return convertView;
    }

    class Holder{
        TextView textView;
        TextView description;
        ImageView imageView;
    }
}
