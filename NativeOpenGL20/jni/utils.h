#ifndef _utils_H
#define _utils_H
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}

typedef struct{
	size_t size;
	void * point;
}Array;

#endif
//void readStlFileBinary(const char* filePath){
//	char name[80];
//	long facetCount;
//	FILE *file = fopen(filePath,"rb");
//	if(file!=NULL){
//		LOGI("open file success: %s",filePath);
//		if(fread(name,80,1,file)==1){
//			LOGI("read file name success: %s",name);
//			if(fread(&facetCount,4,1,file)==1){
//				LOGI("read length success : %ld",facetCount);
//				char *normals = (char*)malloc(facetCount*sizeof(char)*12);
//				char *vertexs = (char*)malloc(facetCount*sizeof(char)*36);
//				char *attribs = (char*)malloc(facetCount*sizeof(char)*2);
//				int x;
//				for(x=0;x<facetCount;x++){
//					fread(normals+x*12,12,1,file);
//					fread(vertexs+x*36,36,1,file);
//					fread(attribs,2,1,file);
//				}
//	            LOGI("read wile count: x = %d;",x);
//				return;
//			}
//		}
//	}
//	LOGI("read file failure! %s",filePath);
//	fclose(file);
//	return;
//}
//int num;
//float* verts;
//float* vnorms;
//void readStlFileAscii(const char* path)
//{
//    int max=0;
//    bool isbegin=false;
//    long size=0;
//    int nlines=0;
//    int count1=0;
//    int count2=0;
//    FILE* file=fopen(path,"r");
//    fseek(file,0L,SEEK_END);
//    size=ftell(file);
//    fclose(file);
//    file=fopen(path,"r");
//    for (int i=0;i<size;i++)
//    {
//        if(getc(file)=='\n')
//        {
//            nlines++;
//        }
//    }
//    num=nlines/7;
//    rewind(file);
//    while (getc(file) != '\n');
//    verts  = new float[9*num];
//    vnorms = new float[9*num];
//    for (int i=0;i<num;i++)
//    {
//        char x[200]="";
//        char y[200]="";
//        char z[200]="";
//        if(3!=fscanf(file,"%*s %*s %80s %80s %80s\n",x,y,z))
//        {
//            break;
//        }
//        vnorms[count1]=vnorms[count1+3]=vnorms[count1+6]=atof(x);
//        count1++;
//        vnorms[count1]=vnorms[count1+3]=vnorms[count1+6]=atof(y);
//        count1++;
//        vnorms[count1]=vnorms[count1+3]=vnorms[count1+6]=atof(z);
//        count1+=7;
//        fscanf(file,"%*s %*s");
//        if (3!=fscanf(file,"%*s %80s %80s %80s\n",x,y,z))
//        {
//            break;
//        }
//        if (isbegin==false)
//        {
//            isbegin=true;
//            max=atof(z);
//        }
//        verts[count2]=atof(x);
//        count2++;
//        verts[count2]=atof(y);
//        count2++;
//        verts[count2]=atof(z);
//        count2++;
//        if (3!=fscanf(file,"%*s %80s %80s %80s\n",x,y,z))
//        {
//            break;
//        }
//        verts[count2]=atof(x);
//        count2++;
//        verts[count2]=atof(y);
//        count2++;
//        verts[count2]=atof(z);
//        count2++;
//        if (3!=fscanf(file,"%*s %80s %80s %80s\n",x,y,z))
//        {
//            break;
//        }
//        verts[count2]=atof(x);
//        count2++;
//        verts[count2]=atof(y);
//        count2++;
//        verts[count2]=atof(z);
//        count2++;
//        fscanf(file,"%*s");
//        fscanf(file,"%*s");
//    }
//
//}
