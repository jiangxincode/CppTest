#include <stdlib.h>
#include <GL/glut.h>


void background(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);//设置背景颜色为黑色
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);//buffer设置为颜色可写

    glBegin(GL_TRIANGLES);//开始画三角形
    glShadeModel(GL_SMOOTH);//设置为光滑明暗模式

    glColor3f(1.0, 0.0, 0.0);//设置第一个顶点为红色
    glVertex2f(-1.0, -1.0);//设置第一个顶点的坐标为（-1.0，-1.0）

    glColor3f(0.0, 1.0, 0.0);//设置第二个顶点为绿色
    glVertex2f(0.0, -1.0);//设置第二个顶点的坐标为（0.0，-1.0）

    glColor3f(0.0, 0.0, 1.0);//设置第三个顶点为蓝色
    glVertex2f(-0.5, 1.0);//设置第三个顶点的坐标为（-0.5，1.0）
    glEnd();//三角形结束

    glFlush();//强制OpenGL函数在有限时间内运行
}

void myReshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);//设置视口

    glMatrixMode(GL_PROJECTION);//指明当前矩阵为GL_PROJECTION
    glLoadIdentity();//将当前矩阵置换为单位阵

    if (w <= h)
        gluOrtho2D(-1.0, 1.5, -1.5, 1.5 * (GLfloat)h / (GLfloat)w);//定义二维正视投影矩阵
    else
        gluOrtho2D(-1.0, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);//指明当前矩阵为GL_MODELVIEW
}

int main(int argc, char** argv)
{
    //用来初始化GLUT库并同窗口系统对话协商。
    glutInit(&argc, argv);
    //用来确定所创建窗口的显示模式。
    //本例中的参数GLUT_SINGLE 指定单缓存窗口，这也是缺省模式，
    //对应的模式为GLUT_DOUBLE 双缓存窗口。
    //参数GLUT_RGB指定颜色RGBA模式，这也是缺省模式，
    //对应的模式为GLUT_INDEX 颜色索引模式窗口。
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //初始化窗口的大小，第一个参数为窗口的宽度，第二个参数为窗口的高度，以像素为单位。
    glutInitWindowSize(400, 400);
    //设置初始窗口的位置，第一个参数为窗口左上角x的坐标，第二个参数为窗口左上角y的坐标，以像素为单位。
    //屏幕的左上角的坐标为（0，0），横坐标向右逐渐增加，纵坐标向下逐渐增加。
    glutInitWindowPosition(200, 200);

    //创建顶层窗口，窗口的名字为扩号中的参数。
    glutCreateWindow("Triangle");

    //这是自己写的函数，设置背景。其实这个函数中的语句可以写在display函数中，但为了使功能块更加清晰，所以把背景这一部分单独提出来。
    background();
    //注册当前窗口的形状变化回调函数。当改变窗口大小时，该窗口的形状改变回调函数将被调用。在此例中就是myReshape指定形状变化函数。
    glutReshapeFunc(myReshape);
    //注册当前窗口的显示回调函数。当一个窗口的图像层需要重新绘制时，GLUT将调用该窗口的的显示回调函数。
    //在此例中的mydisplay就是显示回调函数，显示回调函数不带任何参数，它负责整个图像层的绘制。
    //我们的大部分工作将集中在这个函数中。
    glutDisplayFunc(myDisplay);

    //进入GLUT事件处理循环。glutMainLoop函数在GLUT程序中最多只能调用一次，它一旦被调用就不再返回，并且调用注册过的回调函数。
    //所以这个函数必须放在注册回调函数的后面，此例中为glutReshapeFunc， glutDisplayFunc。
    glutMainLoop();
    return(0);
}
