package com.cement.opgl.main;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import com.cement.opengl.stl.NativeStlReader;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore.Images.ImageColumns;
import android.support.v4.os.EnvironmentCompat;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

public class MainActivity extends Activity {

	private FileOutputStream fins;
	private NativeStlReader reader;
	private String path;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		reader = new NativeStlReader();
//		 g.v(getClass().getSimpleName(), "........:"+result);
		path = Environment.getExternalStorageDirectory().getAbsolutePath();
		
		
	}

	public  String getRealFilePath(final Uri uri ) {
	    if ( null == uri ) return null;
	    final String scheme = uri.getScheme();
	    String data = null;
	    if ( scheme == null )
	        data = uri.getPath();
	    else if ( ContentResolver.SCHEME_FILE.equals( scheme ) ) {
	        data = uri.getPath();
	    } else if ( ContentResolver.SCHEME_CONTENT.equals( scheme ) ) {
	        Cursor cursor = getContentResolver().query( uri, new String[] { ImageColumns.DATA }, null, null, null );
	        if ( null != cursor ) {
	            if ( cursor.moveToFirst() ) {
	                int index = cursor.getColumnIndex( ImageColumns.DATA );
	                if ( index > -1 ) {
	                    data = cursor.getString( index );
	                }
	            }
	            cursor.close();
	        }
	    }
	    return data;
	}
	public void openFileChooser(){
		Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
		intent.addCategory(Intent.CATEGORY_OPENABLE);
		intent.setType("*/*");
		try {
			startActivityForResult(Intent.createChooser(intent, "请选择一个你喜欢的软件"),1000);
		} catch (android.content.ActivityNotFoundException ex) {
			Toast.makeText(MainActivity.this, "请安装文件管理器", Toast.LENGTH_SHORT).show();
		}
	}
	  @Override  
	    public void onActivityResult(int requestCode, int resultCode, Intent data) {  
	        if (resultCode == Activity.RESULT_OK && requestCode == 1000) {  
	            Uri uri = data.getData(); 
	            String path = getRealFilePath(uri);
	            boolean result = reader.nativeReadFile(path);
	            System.out.println("result: ............................ "+result);
	        }  
	        super.onActivityResult(requestCode, resultCode, data);  
	    }  
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			this.openFileChooser();
			System.out.println(path);
			return true;
		}
		return super.onOptionsItemSelected(item);
	}



}
