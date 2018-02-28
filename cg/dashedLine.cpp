#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
int x1,x2;
int yl1,y2;
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);//Sets the color of the window
    glOrtho(-1000.0, 1000.0, -1000.0, 1000.0, -1.0, 1.0);//Sets the size of the plane
}
int mod(int x)
{
    return x>0?x:-x;
}
void Bresenham()
{
    //Swap the points if x1>x2
    if(x2<x1)
    {
        int c=x1;
        x1=x2;
        x2=c;
        c=yl1;
        yl1=y2;
        y2=c;
    }
    int dx=x2-x1;
    int dy=y2-yl1;
    
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);//Color of the vertices
    int x,y=yl1;
    int p=2*dy-dx;
    glBegin(GL_POINTS);

    if(dx>0 && dy>0){
        if(dx>=dy)
         {
            int jump=dx/7;
            for(x=x1,y=yl1;x!=x2;x++)
            {
                int p2=p+2*dy-2*dx;
                if(p2>0)
                {
                     y++;
                }
                else
                {
                    p2=p+2*dy;
                }
                if(((x-x1)/jump)%2==0)
                    glVertex2s(x,y);
                p=p2;
            }
        }
        else
        {   
             p=2*dx-dy;
            int jump=dy/7;
            for(y=yl1,x=x1;y!=y2;y++)
            {
                int p2=p+2*dx-2*dy;
                if(p2>0)
                    x++;
                 else
                    p2=p+2*dx;
                if(((y-yl1)/jump)%2==0)
                    glVertex2s(x,y);
                p=p2;
            }

        }
    }
    else
    {
        dy=mod(dy);
        if(mod(dx)>=mod(dy)) {
            int jump=mod(dx)/7;    
            for(x=x1,y=yl1;x!=x2;x++)
            {
                int p2=p+2*dy-2*dx;
                if(p2>0)
                {
                    y++;
                }
                else
                {
                    p2=p+2*dy;
                }
                if(((x-x1)/jump)%2==0)
                    glVertex2s(x,yl1-(y-yl1));
                p=p2;
    }
    }
    else
    {   
        p=2*dx-dy;
        int jump=mod(dy)/7;
        glBegin(GL_POINTS);
        for(y=yl1,x=x1;y!=2*yl1-y2;y++)
        {
            int p2=p+2*dx-2*dy;
            if(p2>0)
                x++;
            else
                p2=p+2*dx;
            if(((y-yl1)/jump)%2==0)
                glVertex2s(x,2*yl1-y);
            p=p2;
        }

    }
    }
    glEnd();
    glFlush();

}
int main()
{
    int argc=0;
    char **argv;
    scanf("%d %d %d %d",&x1,&yl1,&x2,&y2);
    //printf("%d %d \n",dx,dy);
    //scanf("%d ",&argc);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Window");
    init();
    glutDisplayFunc(Bresenham);
    glutMainLoop();
    return 0;
}

