/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.cement.jni;



import com.cement.gl2jni.R;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore.Images.ImageColumns;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;


public class GL2JNIActivity extends Activity {

    GL2JNISurfaceView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        mView = new GL2JNISurfaceView(getApplication());
	    setContentView(mView);
	    System.out.println("test github uplooad........");
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
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
			//NativeRenderer.drawStlModel("...");
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	public void openFileChooser(){
		Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
		intent.addCategory(Intent.CATEGORY_OPENABLE);
		intent.setType("*/*");
		try {
			startActivityForResult(Intent.createChooser(intent, "请选择一个你喜欢的软件"),1000);
		} catch (android.content.ActivityNotFoundException ex) {
			Toast.makeText(GL2JNIActivity.this, "请安装文件管理器", Toast.LENGTH_SHORT).show();
		}
	}
	  @Override  
	    public void onActivityResult(int requestCode, int resultCode, Intent data) {  
	        if (resultCode == Activity.RESULT_OK && requestCode == 1000) {  
	            Uri uri = data.getData(); 
	            String path = getRealPath(uri);
	            NativeRenderer.drawStlModel(path);
	            System.out.println("result: ............................ ");
	        }  
	        super.onActivityResult(requestCode, resultCode, data);  
	    } 
	  public  String getRealPath(final Uri uri ) {
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
}
