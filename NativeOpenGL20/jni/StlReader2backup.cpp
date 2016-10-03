#include <global.h>

struct GLfacets{
	long   size;
	float* normals;
	float* coords;
	char*  attribs;
};

struct GLfacets *facets = NULL;
void readStlFileBinary(const char* filePath);
void readStlFileAscii(const char* path);
bool isAscii(FILE* file){
	char hearder[80];
	fgets(hearder,80,file);
	rewind(file);

	return strstr(hearder,"solid")!= NULL;
}
bool isBinary(FILE* file){
	fseek(file,-24,SEEK_END);
			for (int i = 0; i < 24; i++) {
				if(getc(file)=='\n') {
					return false;
				}
	}
	return true;
}
void readStlFile(const char* path){
	FILE *file = fopen(path,"rb");
	if(file!=NULL){
		if(isAscii(file)){
			LOGI(".................ascii................");
			readStlFileAscii(path);
		}else if(isBinary(file)){
			LOGI(".................binary................");
			readStlFileBinary(path);
		}else{
			LOGI("file is not STL foramtter or it has been bad!");
		}
	}
}
void mallocFacets(size_t count){
	facets->size = count;
	facets->normals = (float*)malloc(count*sizeof(char)*12);
	facets->coords = (float*)malloc(count*sizeof(char)*36);
	facets->attribs = (char*)malloc(count*sizeof(char)*2);
}
void freeFacets(){
	facets->size = 0;
	free(facets->normals);
	facets->normals = NULL;
	free(facets->coords);
	facets->coords = NULL;
	free(facets->attribs);
	facets->attribs = NULL;
}
void writeFacets(FILE* file,size_t count){
	for(int x=0;x<count;x++){
		fread(facets->normals+x*12,12,1,file);
		fread(facets->coords+x*36,36,1,file);
		fread(facets->attribs,2,1,file);
	}
}
void readAsciiStl(FILE* file){
	int num=-1,var = -1;
	long len = -1,count=-1;
	rewind(file);
	for(int num=0;getc(file)!='\0';num++);
	fseek(file,-num,SEEK_CUR);
	const char* name[num];
	fread(name,num,1,file);

	for(int var = 0;feof(file)==0;){
		if(getc(file)!='\0') var++;
		if(var==7) break;
	}

	fseek(file,0,SEEK_END);
	len = ftell(file);
	count = len/var;

	mallocFacets(count);
	fseek(file,num,SEEK_SET);
	for(int i = 0 ;i<count; i++){
		char x[20],y[20],z[20];
		fscanf(file,"%*s %*s %20s %20s %20s\n",x,y,z);
//		facets->normals+i*12+0 = &atof(x);
//		facets->normals+i*12+4 = &atof(y);
//		facets->normals+i*12+8 = &atof(z);
		fscanf(file,"%*s %*s");
		for (int var = 0; var < 3; var++) {
			fscanf(file,"%*s %20s %20s %20s\n",x,y,z);
//			facets->coords+i*12+0 = atof(x);
//			facets->coords+i*12+4 = atof(y);
//			facets->coords+i*12+8 = atof(z);
		}
		fscanf(file,"%*s");
		fscanf(file,"%*s");
	}

}
void readBinaryStl(FILE* file){
	char name[80];
	rewind(file);
	if(fread(name,80,1,file)==1){
		size_t count;
		if(fread(&count,4,1,file)==1){
			mallocFacets(count);
			writeFacets(file,count);
		}
	}
}

long   facet_count;
float* facet_coords;
void readStlFileAscii(const char* path){
    long size=0;
    long nlines=0;
    int index=0;
    FILE* file=fopen(path,"r");
    fseek(file,0L,SEEK_END);
    size=ftell(file);
    fclose(file);
    file=fopen(path,"r");
    for (int i=0;i<size;i++){
        if(getc(file)=='\n') nlines++;
    }
    facet_count=nlines/7;
    rewind(file);
    while (getc(file) != '\n');
    facet_coords = new float[9*facet_count];
    for (int i=0;i<facet_count;i++){
        char x[200]="";
        char y[200]="";
        char z[200]="";
        if(3!=fscanf(file,"%*s %*s %80s %80s %80s\n",x,y,z)) break;
        fscanf(file,"%*s %*s");
        for (int i = 0; i < 3; i++) {
			if (3!=fscanf(file,"%*s %80s %80s %80s\n",x,y,z)) break;
			facet_coords[index++]=atof(x);
			facet_coords[index++]=atof(y);
			facet_coords[index++]=atof(z);
		}
        fscanf(file,"%*s");
        fscanf(file,"%*s");
    }

    fclose(file);
}
void readStlFileBinary(const char* filePath){
	char name[80];
	long facetCount;
	FILE *file = fopen(filePath,"rb");
	if(file!=NULL){
		LOGI("open file success: %s",filePath);
		if(fread(name,80,1,file)==1){
			LOGI("read file name success: %s",name);
			if(fread(&facetCount,4,1,file)==1){
				LOGI("read length success : %ld",facetCount);
				facet_count =facetCount;
				facet_coords = new float[facet_count*9];
				for(int x=0;x<facetCount;x++){
					fseek(file,12,SEEK_CUR);
					fread(facet_coords+x*9,36,1,file);
					fseek(file,2,SEEK_CUR);
				}
			}
		}
	}
	LOGI("read file failure! %s",filePath);
	fclose(file);
}
