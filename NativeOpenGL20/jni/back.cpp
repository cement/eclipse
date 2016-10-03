#include 'windows.h'
#include <GLTools.h>    // <a href="http://www.it165.net/Pro/pkgame/" target="_blank" class="keylink">OpenGL</a> toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLBatch                triangleBatch;
GLMatrixStack       modelViewMatix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;
GLShaderManager     shaderManager;
int num;
float* verts;
float* vnorms;
void getstlmodel()
{
    int max=0;
    bool isbegin=false;
    long size=0;
    int nlines=0;
    int count1=0;
    int count2=0;
    FILE* file=fopen('mystl.stl','r');
    fseek(file,0L,SEEK_END);
    size=ftell(file);
    fclose(file);
    file=fopen('mystl.stl','r');
    for (int i=0;i<size;i++)
    {
        if(getc(file)=='
')
        {
            nlines++;
        }
    }
    num=nlines/7;
    rewind(file);
    while (getc(file) != '
');
    verts=new float[9*num];
    vnorms=new float[9*num];
    for (int i=0;i<num;i++)
    {
        char x[200]='';
        char y[200]='';
        char z[200]='';
        if(3!=fscanf(file,'%*s %*s %80s %80s %80s
',x,y,z))
        {
            break;
        }
        vnorms[count1]=vnorms[count1+3]=vnorms[count1+6]=atof(x);
        count1++;
        vnorms[count1]=vnorms[count1+3]=vnorms[count1+6]=atof(y);
        count1++;
        vnorms[count1]=vnorms[count1+3]=vnorms[count1+6]=atof(z);
        count1+=7;
        fscanf(file,'%*s %*s');
        if (3!=fscanf(file,'%*s %80s %80s %80s
',x,y,z))
        {
            break;
        }
        if (isbegin==false)
        {
            isbegin=true;
            max=atof(z);
        }
        verts[count2]=atof(x);
        count2++;
        verts[count2]=atof(y);
        count2++;
        verts[count2]=atof(z);
        count2++;
        if (3!=fscanf(file,'%*s %80s %80s %80s
',x,y,z))
        {
            break;
        }
        verts[count2]=atof(x);
        count2++;
        verts[count2]=atof(y);
        count2++;
        verts[count2]=atof(z);
        count2++;
        if (3!=fscanf(file,'%*s %80s %80s %80s
',x,y,z))
        {
            break;
        }
        verts[count2]=atof(x);
        count2++;
        verts[count2]=atof(y);
        count2++;
        verts[count2]=atof(z);
        count2++;
        fscanf(file,'%*s');
        fscanf(file,'%*s');
    }

}
void SetupRC()
{
    // Black background
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f );

    shaderManager.InitializeStockShaders();
    viewFrame.MoveForward(1000.0f);
     triangleBatch.Begin(GL_TRIANGLES, num*3);
     triangleBatch.CopyVertexData3f(verts);
    triangleBatch.CopyNormalDataf(vnorms);
    triangleBatch.End();

    // Make the torus


}
void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        viewFrame.RotateWorld(m3dDegToRad(-5.0), 1.0f, 0.0f, 0.0f);

    if(key == GLUT_KEY_DOWN)
        viewFrame.RotateWorld(m3dDegToRad(5.0), 1.0f, 0.0f, 0.0f);

    if(key == GLUT_KEY_LEFT)
        viewFrame.RotateWorld(m3dDegToRad(-5.0), 0.0f, 1.0f, 0.0f);

    if(key == GLUT_KEY_RIGHT)
        viewFrame.RotateWorld(m3dDegToRad(5.0), 0.0f, 1.0f, 0.0f);

    // Refresh the Window
    glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 2000.0f);

    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatix, projectionMatrix);
}
void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    modelViewMatix.PushMatrix(viewFrame);
    GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    //shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vRed);
    shaderManager.UseStockShader(GLT_SHADER_DEFAULT_LIGHT, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vRed);

    triangleBatch.Draw();

    modelViewMatix.PopMatrix();


    glutSwapBuffers();
}
int main(int argc, char* argv[])
{
    getstlmodel();
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow('Geometry Test Program');
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, 'GLEW Error: %s
', glewGetErrorString(err));
        return 1;
    }
    SetupRC();
    glutMainLoop();
    return 0;
}
