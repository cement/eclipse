#include <stdio.h>

void xgluPerspective( float fovy, float aspect, float near_clip, float far_clip )
{
    const double PI = 3.1415926;
    double TWOPI_OVER_360 = 2.0 * PI / 360.0;
    float half_height = near_clip * (float)tan( fovy * 0.5 * TWOPI_OVER_360 );
    float half_width = half_height * aspect;

}

void xgluLookAt (
                        float eyex,
                        float eyey,
                        float eyez,
                        float centerx,
                        float centery,
                        float centerz,
                        float upx,
                        float upy,
                        float upz)
{
//    vector3_t forward(centerx - eyex, centery - eyey, centerz - eyez);
//    vector3_t up(upx, upy, upz);
//
//    forward.Normalize();
//
//    vector3_t side = forward ^ up;
//    side.Normalize();
//
//    up = side ^ forward;
//
//    float m[4][4];
//
//    m[0][0] = side[0];
//    m[1][0] = side[1];
//    m[2][0] = side[2];
//    m[3][0] = 0.0f;
//
//    m[0][1] = up[0];
//    m[1][1] = up[1];
//    m[2][1] = up[2];
//    m[3][1] = 0.0f;
//
//    m[0][2] = -forward[0];
//    m[1][2] = -forward[1];
//    m[2][2] = -forward[2];
//    m[3][2] = 0.0f;
//
//    m[0][3] = 0.0f;
//    m[1][3] = 0.0f;
//    m[2][3] = 0.0f;
//    m[3][3] = 1.0f;
//
//    glMultMatrixf(&m[0][0]);
//
//    glTranslatef(-eyex, -eyey, -eyez);
}
