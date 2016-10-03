#include <global.h>


static bool isBinary(FILE* file);
static bool isAscii(FILE* file);
static void readStlFileBinary(FILE* file);
static void readStlFileAscii(FILE* file);

long   facet_count =-1;
float* facet_coords = NULL;;

void readStlFile(const char* path){
	FILE *file = fopen(path,"r");
	if(file!=NULL){
		if(isAscii(file)){
			LOGI(".................ascii................");
			readStlFileAscii(file);
		}else if(isBinary(file)){
			LOGI(".................binary................");
			readStlFileBinary(file);
		}else{
			LOGI("file is not STL foramtter or it has been bad!");
		}
	}
	fclose(file);
}


static void readStlFileAscii(FILE* file){
    long size=0;
    int indexed=0;
    fseek(file,0L,SEEK_END);
    size=ftell(file);
    rewind(file);
    while (getc(file) != '\n');
    int var = 0;
    for(int i = 0;feof(file)==0;++var){
		if(getc(file)!='\0')
		if(++var==7) break;
    }
    facet_count = size/var;

    facet_coords = new float[facet_count*9];
    //facet_coords = (float*)malloc(facet_count*9);
    for (int i=0;i<facet_count;i++){
        char x[20],y[20],z[20];
        fscanf(file,"%*s %*s %*s %*s %*s\n");
        fscanf(file,"%*s %*s");
        for (int j = 0; j < 3; j++) {
			if (3!=fscanf(file,"%*s %20s %20s %20s\n",x,y,z)) break;
			facet_coords[indexed++]=atof(x);
			facet_coords[indexed++]=atof(y);
			facet_coords[indexed++]=atof(z);
//			facet_coords[i*9+j*3+0]=atof(x);
//			facet_coords[i*9+j*3+1]=atof(y);
//			facet_coords[i*9+j*3+2]=atof(z);
		}
        fscanf(file,"%*s");
        fscanf(file,"%*s");
    }
}
static void readStlFileBinary(FILE* file){
	char name[80];
	long facetCount;
	rewind(file);
	if(fread(name,80,1,file)==1){
		LOGI("read file name success: %s",name);
		if(fread(&facetCount,4,1,file)==1){
			LOGI("read length success : %ld",facetCount);
			facet_count =facetCount;
			facet_coords = new float[facet_count*9];
			//facet_coords = (float*)malloc(facet_count*9);
			for(int x=0;x<facetCount;x++){
				fseek(file,12,SEEK_CUR);
				fread(facet_coords+x*9,36,1,file);
				fseek(file,2,SEEK_CUR);
			}
		}
	}
}

static bool isAscii(FILE* file){
	char hearder[80];
	fgets(hearder,80,file);
	rewind(file);

	return strstr(hearder,"solid")!= NULL;
}
static bool isBinary(FILE* file){
	fseek(file,-24,SEEK_END);
			for (int i = 0; i < 24; i++) {
				if(getc(file)=='\n') {
					return false;
				}
	}
	return true;
}
