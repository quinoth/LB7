#include <windows.h>
#include <gl/gl.h>
#include <math.h>

float vert[] = {1,1,0, 1,-1,0, -1,-1,0, -1,1,0};
float normal_vert[] = {0,0,1, 0,0,1, 0,0,1, 0,0,1};
float xA = 20;
float zA = 0;
POINTFLOAT pos = {0,0};
float theta = 0.0f;

void Chess(int n)
{
    for (int i = -n; i < n; i++)
        for (int j = -n; j < n; j++)
        {
            glPushMatrix();
                if ((i+j) % 2 == 0) glColor3f(0, 0, 0);
                else glColor3f(1,1,1);
                glTranslatef(i*2, j*2, 0);
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glPopMatrix();
        }
}

void Normal(x1,y1,z1, x2,y2,z2, c1,c2,c3)
{
    glEnable(GL_LINE_SMOOTH);
        glLineWidth(5.0f);

    glBegin(GL_LINES);
        glColor3f(c1,c2,c3);
        glVertex3d(x1,y1,z1);
        glVertex3d(x2,y2,z2);
    glEnd();

    glDisable(GL_LINE_SMOOTH);
}

void LightSource()
{
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vert);
        glDrawArrays(GL_TRIANGLE_FAN,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Init_Light()
{
    glEnable(GL_LIGHTING); //общее освещения для всего пространства
    glShadeModel(GL_SMOOTH);
    glPushMatrix();

        //glRotatef(theta, 0,1,0);

        GLfloat light_position[] = { 0.0f, 0.0f, 35.0f, 1.0f }; //позиция источника
        GLfloat light_spot_direction[] = {0.0, 0.0, -1.0, 1.0}; // позиция цели

        GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //параметры
        GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //параметры
        GLfloat light_specular[] = { 0.2f, 0.2f, 0.2f, 32.0f }; //параметры

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50); // конус для
        //направленного источника
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0); // экспонента
        //убывания интенсивности1
        //задействование настроек для источника LIGHT0
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glEnable(GL_LIGHT0); // источник света LIGHT0

        glTranslatef(0,0,15);
        glColor3f(1,1,1);
        LightSource();

        //theta += 0.5f;
    glPopMatrix();

}

void Init_Material()
{
    glEnable(GL_COLOR_MATERIAL); //разрешения использования
    //материала
    glShadeModel(GL_SMOOTH); // сглаживает границы
    GLfloat material_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat material_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 32.0f };
    GLfloat material_shininess[] = { 100.0f }; //блеск материала

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
}

void Draw_Prism(){
const int N = 13;

GLfloat vertices[(N * 3) * 2 + 6];
GLfloat normals[(N * 3) * 2 + 6];

for(int i = 0; i < N + 1; ++i){
    float angle = 2.0f * M_PI * i / N;
    float x = 3.0f * cos(angle);
    float y = 3.0f * sin(angle);
    float z = 0.0f;

    vertices[i * 3] = x;
    vertices[i * 3 + 1] = y;
    vertices[i * 3 + 2] = z;

    normals[i * 3] = x;
    normals[i * 3 + 1] = y;
    normals[i * 3 + 2] = z;

}

float new_x = 0.0f;
float new_y = 0.0f;
float new_z = 0.0f;

vertices[N * 3] = new_x;
vertices[N * 3 + 1] = new_y;
vertices[N * 3 + 2] = new_z;

for(int i = 0; i < N + 1; ++i){
    float angle = 2.0f * M_PI * i / N;
    float x = 3.0f * cos(angle);
    float y = 3.0f * sin(angle);
    float z = 2.0f;

    vertices[(i + N + 1) * 3] = x;
    vertices[(i + N + 1) * 3 + 1] = y;
    vertices[(i + N + 1) * 3 + 2] = z;

    normals[(i + N + 1) * 3] = x;
    normals[(i + N + 1) * 3 + 1] = y;
    normals[(i + N + 1) * 3 + 2] = z;
}

new_z = 2.0f;

vertices[(N * 2 + 1) * 3] = new_x;
vertices[(N * 2 + 1) * 3 + 1] = new_y;
vertices[(N * 2 + 1) * 3 + 2] = new_z;

GLuint indices[] = {
    0,1,13,
    1,2,13,
    2,3,13,
    3,4,13,
    4,5,13,
    5,6,13,
    6,7,13,
    7,8,13,
    8,9,13,
    9,10,13,
    10,11,13,
    11,12,13,
    12,0,13,

    14,15,27,
    15,16,27,
    16,17,27,
    17,18,27,
    18,19,27,
    19,20,27,
    20,21,27,
    21,22,27,
    22,23,27,
    23,24,27,
    24,25,27,
    25,26,27,
    26,14,27,

    0,14,1,
    1,14,15,
    1,15,2,
    2,15,16,
    2,16,3,
    3,16,17,
    3,17,4,
    4,17,18,
    4,18,5,
    5,18,19,
    5,19,6,
    6,19,20,
    6,20,7,
    7,20,21,
    7,21,8,
    8,21,22,
    8,22,9,
    9,22,23,
    9,23,10,
    10,23,24,
    10,24,11,
    11,24,25,
    11,25,12,
    12,25,26,
    12,26,0,
    0,26,14

};
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, normals);
        glVertexPointer(3, GL_FLOAT, 0, vertices);

        glDrawElements(GL_TRIANGLES, 156, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(0.2f, 1.0f, 0.15f, 0.3f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawElements(GL_TRIANGLES, 156, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_BLEND);

}

void Prisms(){
    int num = 6;
    GLfloat transparency[6] = {1.0f, 0.8f, 0.6f, 0.4f, 0.3f, 0.1f};
    GLfloat positions[6][3] = {{-10,0,0}, {-4,-8,0}, {4,-8,0}, {10,0,0}, {4,8,0}, {-4,8,0}};
    for(int i = 0; i < num; ++i){
        glPushMatrix();
        glTranslatef(positions[i][0], positions[i][1], positions[i][2]);
        glColor4f(0.0f,0.0f,1.0f,transparency[i]);
        Draw_Prism();
        glPopMatrix();
    }
}

void Draw_Cube(){
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f
};
GLuint indices[] = {
    0, 1, 2,
    2, 3, 0,
    1, 5, 6,
    6, 2, 1,
    7, 6, 5,
    5, 4, 7,
    4, 0, 3,
    3, 7, 4,
    4, 5, 1,
    1, 0, 4,
    3, 2, 6,
    6, 7, 3
};
GLfloat normals[] = {
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,

    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
};
    glColor3f(1,1,1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}



void ShowWorld()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT,0,&normal_vert);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        Chess(50);
        glColor3f(0,0,0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        Normal(0,0,0, 10,0,0, 1,0,0);
        Normal(0,0,0, 0,10,0, 0,1,0);
        Normal(0,0,0, 0,0,10, 0,0,1);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void MoveCamera()
{
    if (GetKeyState(VK_UP) < 0) xA = ++xA > 180 ? 180 : xA;
    if (GetKeyState(VK_DOWN) < 0) xA = --xA < 0 ? 0 : xA;
    if (GetKeyState(VK_LEFT) < 0) zA++;
    if (GetKeyState(VK_RIGHT) < 0) zA--;

    float angle = -zA / 180 * M_PI;
    float speed = 0;
    if (GetKeyState('W') < 0) speed = 0.15;
    if (GetKeyState('S') < 0) speed = -0.15;
    if (GetKeyState('A') < 0) {speed = 0.15; angle -= M_PI*0.5; }
    if (GetKeyState('D') < 0) {speed = 0.15; angle += M_PI*0.5; }
    if (speed != 0)
    {
        pos.x += sin(angle) * speed;
        pos.y += cos(angle) * speed;
    }

    glRotatef(-xA, 1,0,0);
    glRotatef(-zA, 0,0,1);
    glTranslatef(-pos.x, -pos.y, -3);
}


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1024,
                          1024,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1, -1,1, 2,150);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.53f, 0.81f, 0.98f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix();
                MoveCamera();

                Init_Light();
                Init_Material();

                ShowWorld();

                glTranslatef(0.0,0.0,1.0);
                glScalef(2,2,2);
                Draw_Cube();

                glTranslatef(0.0,0.0,-0.5);
                glScalef(0.5,0.5,0.5);
                Prisms();


            glPopMatrix();

            SwapBuffers(hDC);

            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);



}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

