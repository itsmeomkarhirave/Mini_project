#include <stdio.h>
#include <conio.h>

// omkar
#define main optics_main
#include <graphics.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>

int main()
{
    float f = 120;
    float u = -250;

    int mode = 1;
    int page = 0;

    int graphMode = 0;

    int xParam = 1;
    int yParam = 2;

    initwindow(1000,600,"Optics Virtual Lab");

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        setactivepage(page);
        cleardevice();

        if(GetAsyncKeyState('P') & 0x8000)
            graphMode = 1;

        if(GetAsyncKeyState('O') & 0x8000)
            graphMode = 0;

        if(!graphMode)
        {
            if(GetAsyncKeyState(VK_LEFT)&0x8000) u -= 2;
            if(GetAsyncKeyState(VK_RIGHT)&0x8000) u += 2;

            if(GetAsyncKeyState(VK_UP)&0x8000) f += 1;
            if(GetAsyncKeyState(VK_DOWN)&0x8000) f -= 1;

            if(GetAsyncKeyState('C')) mode = 1;
            if(GetAsyncKeyState('V')) mode = 2;

            if(GetAsyncKeyState('R')) {u=-250;f=120;}

            if(f<20) f=20;
        }

        if(!graphMode)
        {
            setcolor(WHITE);
            line(0,300,1000,300);
            arc(641,300,135,225,200);
            arc(360,300,315,45,200);

            if(mode==1) setcolor(CYAN);
            else setcolor(YELLOW);

            line(500,80,500,520);

            if(mode==1)
            {
                line(490,100,500,80);
                line(510,100,500,80);
                line(490,500,500,520);
                line(510,500,500,520);
                arc(641,300,135,225,200);
                arc(360,300,315,45,200);
            }
            else
            {
                setcolor(BLACK);
                arc(641,300,135,225,200);
                arc(360,300,315,45,200);
                setcolor(WHITE);
                line(490,80,500,100);
                line(510,80,500,100);
                line(490,520,500,500);
                line(510,520,500,500);
            }

            int ox = 500 + u;
            int oy = 240;

            setcolor(WHITE);
            line(ox,300,ox,oy);
            line(ox,oy,ox-10,oy+10);
            line(ox,oy,ox+10,oy+10);

            float F = (mode==1)?f:-f;

            float v=(u*F)/(u-F);
            float m=v/u;
            float h=60*m;

            int ix=500+v;
            int iy=300-h;

            setcolor(GREEN);
            line(ix,300,ix,iy);
            line(ix,iy,ix-10,iy+10);
            line(ix,iy,ix+10,iy+10);

            setcolor(YELLOW);
            line(ox,oy,500,oy);

            if(mode==1)
                line(500,oy,ix,iy);
            else
                line(500,oy,500+f,300);

            setcolor(CYAN);
            line(ox,oy,500,300);

            if(mode==1)
                line(500,300,ix,iy);
            else
                line(500,300,1000,300+(300-oy));

            char s[100];

            sprintf(s,"u = %.1f",u);
            outtextxy(20,20,s);

            sprintf(s,"f = %.1f",f);
            outtextxy(20,50,s);

            sprintf(s,"v = %.1f",v);
            outtextxy(20,80,s);

            if(mode==1)
                outtextxy(20,120,"Convex Lens");
            else
                outtextxy(20,120,"Concave Lens");

            outtextxy(20,160,"Arrows move/change");
            outtextxy(20,180,"Press P for Graph Mode");
        }


        if(graphMode)
        {
            if(GetAsyncKeyState('X') & 0x8000)
            {
                if(GetAsyncKeyState('1')&0x8000) xParam=1;
                if(GetAsyncKeyState('2')&0x8000) xParam=2;
                if(GetAsyncKeyState('3')&0x8000) xParam=3;
                if(GetAsyncKeyState('4')&0x8000) xParam=4;
                if(GetAsyncKeyState('5')&0x8000) xParam=5;
                if(GetAsyncKeyState('6')&0x8000) xParam=6;
            }

            if(GetAsyncKeyState('Y') & 0x8000)
            {
                if(GetAsyncKeyState('1')&0x8000) yParam=1;
                if(GetAsyncKeyState('2')&0x8000) yParam=2;
                if(GetAsyncKeyState('3')&0x8000) yParam=3;
                if(GetAsyncKeyState('4')&0x8000) yParam=4;
                if(GetAsyncKeyState('5')&0x8000) yParam=5;
                if(GetAsyncKeyState('6')&0x8000) yParam=6;
            }

            setcolor(DARKGRAY);

            for(int i=0;i<1000;i+=50)
                line(i,0,i,600);

            for(int i=0;i<600;i+=50)
                line(0,i,1000,i);

            setcolor(WHITE);

            line(0,300,1000,300);
            line(500,0,500,600);

            char label[20];

            for(int i=-10;i<=10;i++)
            {
                int x=500+i*50;
                sprintf(label,"%d",i);
                outtextxy(x,305,label);
            }

            for(int i=-6;i<=6;i++)
            {
                int y=300-i*50;
                sprintf(label,"%d",i);
                outtextxy(505,y,label);
            }

            outtextxy(20,20,"GRAPH MODE");
            outtextxy(20,50,"Parameters:");
            outtextxy(20,70,"1:u");
            outtextxy(20,90,"2:v");
            outtextxy(20,110,"3:m");
            outtextxy(20,130,"4:f");
            outtextxy(20,150,"5:1/u");
            outtextxy(20,170,"6:1/v");

            outtextxy(20,210,"Hold X + number for X axis");
            outtextxy(20,230,"Hold Y + number for Y axis");
            outtextxy(20,250,"Press O to return");

            setcolor(GREEN);

            int prevx=0,prevy=0;
            int first=1;

            for(float U=-400;U<-20;U+=2)
            {
                float F=(mode==1)?f:-f;

                float V=(U*F)/(U-F);
                float M=V/U;

                float param[7];

                param[1]=U;
                param[2]=V;
                param[3]=M*200;
                param[4]=F;
                param[5]=(1/U)*2000;
                param[6]=(1/V)*2000;

                float X=param[xParam];
                float Y=param[yParam];

                int sx=500+X;
                int sy=300-Y;

                if(!first)
                    line(prevx,prevy,sx,sy);

                first=0;

                prevx=sx;
                prevy=sy;
            }
        }

        setvisualpage(page);
        page = 1 - page;

        Sleep(20);
    }

    closegraph();
}
#undef main


//mandar
#define main interference_main
#include <graphics.h>
#include <math.h>
#include <windows.h>

#define PI 3.14159265
double lambda=20,d=40,L=200;

void drawSource(){
    setcolor(YELLOW);
    circle(100,240,15);
    outtextxy(85,265,"Source");
    for(int i=0;i<5;i++) circle(100,240,20+i*10);
}
void drawSlits(int y1,int y2){
    setcolor(WHITE);
    line(250,50,250,430);
    setfillstyle(SOLID_FILL,BLACK);
    bar(245,y1-10,255,y1+10);
    bar(245,y2-10,255,y2+10);
    outtextxy(230,y1-25,"S1");
    outtextxy(230,y2-25,"S2");
}
void drawWaves(int sx,int sy,int f){
    setcolor(CYAN);
    for(int r=10;r<300;r+=40)
        circle(sx,sy,r+f%40);
}
void drawInterferenceRays(int y1,int y2){
    setcolor(LIGHTBLUE);
    for(int y=60;y<420;y+=20){
        line(255,y1,600,y);
        line(255,y2,600,y);
    }
}
void showValues()
{
    char text[100];
    sprintf(text,"Lambda=%.1f  d=%.1f  L=%.1f",lambda,d,L);
    setcolor(WHITE);
    outtextxy(200,10,text);

    outtextxy(150,460,"A/Z:lambda  S/X:d  D/C:L  R:reset  ESC:exit");
}
void drawScreen(){ setcolor(WHITE); line(600,50,600,430); }
void drawFringes(){
    for(int y=60;y<420;y++){
        double phase=PI*d*(y-240)/(lambda*L);
        double intensity=pow(cos(phase),2);
        setcolor(intensity*15);
        line(600,y,780,y);
    }
}
void handleInput(){
    if(GetAsyncKeyState('A')&0x8000) lambda+=0.2;
    if(GetAsyncKeyState('Z')&0x8000) lambda-=0.2;
    if(GetAsyncKeyState('S')&0x8000) d+=0.5;
    if(GetAsyncKeyState('X')&0x8000) d-=0.5;
    if(GetAsyncKeyState('D')&0x8000) L+=2;
    if(GetAsyncKeyState('C')&0x8000) L-=2;
}
int main(){
    int gd=DETECT,gm; initgraph(&gd,&gm,(char*)"");
    int page=0,frame=0;
    while(!GetAsyncKeyState(VK_ESCAPE)){
        setactivepage(page); cleardevice();
        int y1=240-d/2,y2=240+d/2;
        drawSource(); drawSlits(y1,y2);
        drawWaves(250,y1,frame); drawWaves(250,y2,frame);
        drawInterferenceRays(y1,y2);
        drawScreen(); drawFringes();
        showValues();
        setvisualpage(page);
        page=1-page; frame++;
        handleInput(); Sleep(30);
    }
    closegraph();
}
#undef main


//utkarsh
#define main superposition_main
#include <graphics.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>

float A1=50,A2=50,L1=200,L2=200,P1=0,P2=0,t=0;
bool pauseSim=false;

int page3=0;

int xParam=1;
int yParam=5;

float getParam(int id,float x)
{
    float k1=2*M_PI/L1;
    float k2=2*M_PI/L2;
    float w=0.08;

    float y1=A1*sin(k1*x-w*t+P1);
    float y2=A2*sin(k2*x-w*t+P2);
    float y=y1+y2;

    switch(id)
    {
        case 1:return x;
        case 2:return t;
        case 3:return y1;
        case 4:return y2;
        case 5:return y;
        case 6:return P1;
        case 7:return P2;
        case 8:return A1;
        case 9:return A2;
        case 10:return L1;
        case 11:return L2;
    }
    return 0;
}

void drawGrid()
{
    int left=650,top=50,right=980,bottom=550;

    setcolor(DARKGRAY);

    for(int x=left;x<=right;x+=20)
        line(x,top,x,bottom);

    for(int y=top;y<=bottom;y+=20)
        line(left,y,right,y);

    setcolor(WHITE);
    rectangle(left,top,right,bottom);

    for(int i=0;i<=10;i++)
    {
        char s[20];

        int x=left+i*33;
        int y=bottom-i*50;

        sprintf(s,"%d",i);
        outtextxy(x-5,bottom+5,s);

        sprintf(s,"%d",i);
        outtextxy(left-25,y-5,s);
    }
}

void drawGraph()
{
    int left=650,top=50,right=980,bottom=550;

    float scaleX=0.5;
    float scaleY=0.5;

    setcolor(GREEN);

    for(float i=0;i<600;i+=1)
    {
        float x=i;

        float xv=getParam(xParam,x);
        float yv=getParam(yParam,x);

        int gx=left + xv*scaleX;
        int gy=bottom - yv*scaleY;

        if(gx>left && gx<right && gy>top && gy<bottom)
            putpixel(gx,gy,GREEN);
    }
}

void input3()
{
    if(GetAsyncKeyState('W')&0x8000) A1+=0.3;
    if(GetAsyncKeyState('S')&0x8000) A1-=0.3;

    if(GetAsyncKeyState('E')&0x8000) A2+=0.3;
    if(GetAsyncKeyState('D')&0x8000) A2-=0.3;

    if(GetAsyncKeyState('R')&0x8000) L1+=1;
    if(GetAsyncKeyState('F')&0x8000) L1-=1;

    if(GetAsyncKeyState('T')&0x8000) L2+=1;
    if(GetAsyncKeyState('G')&0x8000) L2-=1;

    if(GetAsyncKeyState('A')&0x8000) P1+=0.05;
    if(GetAsyncKeyState('Z')&0x8000) P1-=0.05;

    if(GetAsyncKeyState('Q')&0x8000) P2+=0.05;
    if(GetAsyncKeyState('X')&0x8000) P2-=0.05;

    if(GetAsyncKeyState(VK_SPACE)&1) pauseSim=!pauseSim;

    if(GetAsyncKeyState('X')&0x8000)
    {
        if(GetAsyncKeyState('1')&1)xParam=1;
        if(GetAsyncKeyState('2')&1)xParam=2;
        if(GetAsyncKeyState('3')&1)xParam=3;
        if(GetAsyncKeyState('4')&1)xParam=4;
        if(GetAsyncKeyState('5')&1)xParam=5;
    }

    if(GetAsyncKeyState('Y')&0x8000)
    {
        if(GetAsyncKeyState('1')&1)yParam=1;
        if(GetAsyncKeyState('2')&1)yParam=2;
        if(GetAsyncKeyState('3')&1)yParam=3;
        if(GetAsyncKeyState('4')&1)yParam=4;
        if(GetAsyncKeyState('5')&1)yParam=5;
    }
}

void drawWaves3()
{
    int mid=300;

    float k1=2*M_PI/L1;
    float k2=2*M_PI/L2;
    float w=0.08;

    for(int x=0;x<600;x++)
    {
        float y1=A1*sin(k1*x-w*t+P1);
        float y2=A2*sin(k2*x-w*t+P2);
        float y=y1+y2;

        putpixel(x,mid-y1,CYAN);
        putpixel(x,mid-y2,YELLOW);
        putpixel(x,mid-y,GREEN);
    }
}

void panel2()
{
    char s[100];

    setcolor(WHITE);

    sprintf(s,"A1=%.1f",A1); outtextxy(20,20,s);
    sprintf(s,"A2=%.1f",A2); outtextxy(20,40,s);

    sprintf(s,"L1=%.1f",L1); outtextxy(20,70,s);
    sprintf(s,"L2=%.1f",L2); outtextxy(20,90,s);

    sprintf(s,"P1=%.2f",P1); outtextxy(20,120,s);
    sprintf(s,"P2=%.2f",P2); outtextxy(20,140,s);

    outtextxy(20,180,"W/S A1   E/D A2");
    outtextxy(20,200,"R/F L1   T/G L2");
    outtextxy(20,220,"A/Z P1   Q/X P2");

    outtextxy(20,260,"Hold X + number → X axis");
    outtextxy(20,280,"Hold Y + number → Y axis");

    sprintf(s,"X param=%d",xParam);
    outtextxy(20,320,s);

    sprintf(s,"Y param=%d",yParam);
    outtextxy(20,340,s);
}

int main()
{
    initwindow(1000,600,"Wave Superposition");

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        setactivepage(page3);
        cleardevice();

        input3();

        drawWaves3();

        drawGrid();

        drawGraph();

        panel2();

        if(!pauseSim) t+=1;

        setvisualpage(page3);

        page3=1-page3;

        Sleep(20);
    }

    closegraph();
}

#undef main


//aditya.m
#define main projectile_main
#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <windows.h>

float getParam(int id,float t,float x,float y,float vx,float vy,float angle,float g)
{
    float v=sqrt(vx*vx+vy*vy);

    switch(id)
    {
        case 1: return t;
        case 2: return x;
        case 3: return y;
        case 4: return v;
        case 5: return vx;
        case 6: return vy;
        case 7: return 0.5*v*v;
        case 8: return g*y;
        case 9: return 0.5*v*v + g*y;
        case 10: return angle;
    }
    return 0;
}

void drawGraph(int xParam,int yParam,float u,float angle,float h,float g)
{
    cleardevice();

    setcolor(WHITE);

    int left=120;
    int bottom=550;
    int right=900;
    int top=100;

    int width=right-left;
    int height=bottom-top;

    float theta=angle*3.14159/180;

    float X[500],Y[500];
    int n=0;

    for(float t=0;t<20;t+=0.05)
    {
        float x=u*cos(theta)*t;
        float y=h+u*sin(theta)*t-0.5*g*t*t;

        float vx=u*cos(theta);
        float vy=u*sin(theta)-g*t;

        if(y<0) break;

        X[n]=getParam(xParam,t,x,y,vx,vy,angle,g);
        Y[n]=getParam(yParam,t,x,y,vx,vy,angle,g);

        n++;
    }

    float xmin=X[0],xmax=X[0];
    float ymin=Y[0],ymax=Y[0];

    for(int i=0;i<n;i++)
    {
        if(X[i]<xmin) xmin=X[i];
        if(X[i]>xmax) xmax=X[i];
        if(Y[i]<ymin) ymin=Y[i];
        if(Y[i]>ymax) ymax=Y[i];
    }

    float xscale=width/(xmax-xmin);
    float yscale=height/(ymax-ymin);

    setcolor(DARKGRAY);

    for(int i=0;i<=10;i++)
    {
        int gx=left+i*width/10;
        line(gx,top,gx,bottom);

        int gy=bottom-i*height/10;
        line(left,gy,right,gy);
    }

    setcolor(WHITE);
    line(left,bottom,right,bottom);
    line(left,top,left,bottom);

    char txt[40];

    for(int i=0;i<=10;i++)
    {
        float xv=xmin+(xmax-xmin)*i/10;
        int gx=left+i*width/10;

        sprintf(txt,"%.1f",xv);
        outtextxy(gx-15,bottom+10,txt);
    }

    for(int i=0;i<=10;i++)
    {
        float yv=ymin+(ymax-ymin)*i/10;
        int gy=bottom-i*height/10;

        sprintf(txt,"%.1f",yv);
        outtextxy(left-60,gy-5,txt);
    }

    setcolor(YELLOW);

    for(int i=1;i<n;i++)
    {
        int x1=left+(X[i-1]-xmin)*xscale;
        int y1=bottom-(Y[i-1]-ymin)*yscale;

        int x2=left+(X[i]-xmin)*xscale;
        int y2=bottom-(Y[i]-ymin)*yscale;

        line(x1,y1,x2,y2);
    }

    setcolor(WHITE);

    outtextxy(650,120,"GRAPH LAB");

    outtextxy(650,150,"X + number : X axis");
    outtextxy(650,170,"Y + number : Y axis");

    outtextxy(650,210,"1 time");
    outtextxy(650,230,"2 x");
    outtextxy(650,250,"3 y");
    outtextxy(650,270,"4 speed");
    outtextxy(650,290,"5 vx");
    outtextxy(650,310,"6 vy");
    outtextxy(650,330,"7 KE");
    outtextxy(650,350,"8 PE");
    outtextxy(650,370,"9 Total E");

    outtextxy(650,420,"B back");
}

void projectile_motion()
{
    float u=20;
    float angle=45;
    float h=0;
    float planeAngle=20;
    float g=9.8;

    int mode=1;
    int graphMode=0;

    int xParam=1;
    int yParam=3;

    bool chooseX=false;
    bool chooseY=false;

    initwindow(1000,650,"Projectile Motion");

    int page=0;

    int x0=80;
    int y0=getmaxy()-80;

    float scale=10;

    float t=0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        setactivepage(page);
        cleardevice();

        if(graphMode==0)
        {
            float theta;

            if(mode==1)
                theta=angle*3.14159/180;
            else
                theta=(angle+planeAngle)*3.14159/180;

            float x=u*cos(theta)*t;
            float y=h+u*sin(theta)*t-0.5*g*t*t;

            float screenX=x0+x*scale;
            float screenY=y0-y*scale;

            setcolor(GREEN);

            if(mode==1)
                line(0,y0,getmaxx(),y0);
            else
            {
                float rad=planeAngle*3.14159/180;
                line(0,y0,getmaxx(),y0-tan(rad)*getmaxx());
            }

            setcolor(YELLOW);

            for(float tt=0;tt<t;tt+=0.05)
            {
                float xx=u*cos(theta)*tt;
                float yy=h+u*sin(theta)*tt-0.5*g*tt*tt;

                if(yy<0) break;

                int px=x0+xx*scale;
                int py=y0-yy*scale;

                putpixel(px,py,YELLOW);
            }

            setcolor(RED);
            circle(screenX,screenY,6);
            floodfill(screenX,screenY,RED);

            char info[100];

            setcolor(WHITE);

            sprintf(info,"Velocity %.1f",u);
            outtextxy(700,50,info);

            sprintf(info,"Angle %.1f",angle);
            outtextxy(700,70,info);

            sprintf(info,"Height %.1f",h);
            outtextxy(700,90,info);

            sprintf(info,"Plane %.1f",planeAngle);
            outtextxy(700,120,info);

            outtextxy(700,170,"A/D angle");
            outtextxy(700,190,"W/S velocity");
            outtextxy(700,210,"Q/E height");
            outtextxy(700,230,"1/2 mode");
            outtextxy(700,250,"G graph");

            if(GetAsyncKeyState('G')&1)
            {
                graphMode=1;
                Sleep(200);
            }

            if(mode==1 && y<0)
                t=0;

            t+=0.05;
        }
        else
        {
            drawGraph(xParam,yParam,u,angle,h,g);

            if(GetAsyncKeyState('X')&1) chooseX=true;
            if(GetAsyncKeyState('Y')&1) chooseY=true;

            for(int i=1;i<=9;i++)
            {
                if(GetAsyncKeyState('0'+i)&1)
                {
                    if(chooseX)
                    {
                        xParam=i;
                        chooseX=false;
                    }
                    else if(chooseY)
                    {
                        yParam=i;
                        chooseY=false;
                    }
                }
            }

            if(GetAsyncKeyState('B')&1)
            {
                graphMode=0;
                Sleep(200);
            }
        }

        setvisualpage(page);
        page=1-page;

        if(GetAsyncKeyState('A')&0x8000) angle-=0.3;
        if(GetAsyncKeyState('D')&0x8000) angle+=0.3;
        if(GetAsyncKeyState('W')&0x8000) u+=0.3;
        if(GetAsyncKeyState('S')&0x8000) u-=0.3;
        if(GetAsyncKeyState('Q')&0x8000) h+=0.2;
        if(GetAsyncKeyState('E')&0x8000) h-=0.2;

        if(GetAsyncKeyState('1')&0x8000){mode=1;t=0;}
        if(GetAsyncKeyState('2')&0x8000){mode=2;t=0;}

        if(GetAsyncKeyState('R')&0x8000)
        {
            u=20;
            angle=45;
            h=0;
            planeAngle=20;
            t=0;
        }

        if(angle<1) angle=1;
        if(angle>89) angle=89;
        if(u<1) u=1;
        if(h<0) h=0;

        delay(30);
    }

    closegraph();
}

int main()
{
    projectile_motion();
    return 0;
}
#undef main


//aditya.s
#define main polarisation_main
#include <graphics.h>
#include <math.h>
#include <windows.h>

float A=190,phase=0.5,freq=0.05,t5=0;
int mode5=1;

void proj(float x,float y,float z,int *sx,int *sy){
    float d=400,f=d/(d+z);
    *sx=500+x*f; *sy=300-y*f;
}
void info5(){
    setcolor(WHITE);
    outtextxy(20,20,"3D POLARISATION WAVE");
    int mode=1;

    if(mode==1) outtextxy(20,50,"Linear");
    if(mode==2) outtextxy(20,50,"Circular");
    if(mode==3) outtextxy(20,50,"Elliptical");

    char s[60];

    sprintf(s,"Amplitude %.0f",A);
    outtextxy(20,90,s);

    sprintf(s,"Phase %.2f",phase);
    outtextxy(20,120,s);

    sprintf(s,"Freq %.2f",freq*20);
    outtextxy(20,150,s);

    outtextxy(20,200,"1 Linear");
    outtextxy(20,220,"2 Circular");
    outtextxy(20,240,"3 Elliptical");

    outtextxy(20,280,"W/S amplitude");
    outtextxy(20,300,"A/D phase");
    outtextxy(20,320,"Q/E frequency");
}

int main(){
    initwindow(1000,600,"3D Polarisation");
    int page=0;
    int first=1;
    int mode=1;
    while(!GetAsyncKeyState(VK_ESCAPE)){
        setactivepage(page); cleardevice();
        if(GetAsyncKeyState('1')) mode=1;
        if(GetAsyncKeyState('2')) mode=2;
        if(GetAsyncKeyState('3')) mode=3;

        if(GetAsyncKeyState('W')&0x8000) A+=0.5;
        if(GetAsyncKeyState('S')&0x8000) A-=0.5;
        if(GetAsyncKeyState('A')&0x8000) phase-=0.03;
        if(GetAsyncKeyState('D')&0x8000) phase+=0.03;
        if(GetAsyncKeyState('Q')&0x8000) freq-=0.001;
        if(GetAsyncKeyState('E')&0x8000) freq+=0.001;

        if(A<10) A=10;
        if(freq<0.01) freq=0.01;

        setcolor(DARKGRAY);
        line(100,300,900,300);

        float px,py;
        for(float z=0; z<800; z+=3)
        {
            float ang=z*freq - t5;

            float x=A*cos(ang);
            float y;

            if(mode==1) y=0;
            if(mode==2) y=A*sin(ang);
            if(mode==3) y=(A/2)*sin(ang+phase);

            int sx,sy;
            proj(x,y,z,&sx,&sy);

            setcolor(CYAN);

            if(!first)
            line(px,py,sx,sy);

            px=sx;
            py=sy;
            first=0;

            int bx,by;
            proj(0,0,z,&bx,&by);
            setcolor(DARKGRAY);
            line(bx,by,sx,sy);
        }

        float ang=-t5;
        float x=A*cos(ang);
        float y;

        if(mode==1) y=0;
        if(mode==2) y=A*sin(ang);
        if(mode==3) y=(A/2)*sin(ang+phase);

        int bx,by;
        proj(0,0,0,&bx,&by);

        int tx,ty;
        proj(x,y,0,&tx,&ty);

        setcolor(YELLOW);
        line(bx,by,tx,ty);

        setcolor(RED);
        circle(tx,ty,5);
        floodfill(tx,ty,RED);

        info5();
        t5+=0.08;
        setvisualpage(page);
        page=1-page;
        Sleep(20);
    }
    closegraph();
}
#undef main



int main(){
    int choice;
    while(1){
        system("cls");
        printf("==== PHYSICS LAB SIMULATOR ====\n\n");
        printf("1. Ray Optics\n");
        printf("2. Double Slit\n");
        printf("3. Wave Superposition\n");
        printf("4. Projectile Motion\n");
        printf("5. Polarisation Wave\n");
        printf("0. Exit\n\n");
        printf("Choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: optics_main(); break;
            case 2: interference_main(); break;
            case 3: superposition_main(); break;
            case 4: projectile_motion(); break;
            case 5: polarisation_main(); break;
            case 0: return 0;
            default: printf("Invalid"); getch();
        }
    }
}
