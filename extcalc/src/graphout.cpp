#include "graphout.h"


////////////////////////////////////////initializeGL/////////////////////////////////////////

void GraphOutput::initializeGL()
{
	qglClearColor( white ); 
	glDeleteLists(axes,1);
	if(pref.graphType==GRAPHPOLAR)
		axes=drawPolarAxes();
	else if(pref.graphType==GRAPH3D)
		axes=draw3dAxes();
	else axes = drawStdAxes();
	dynamicSteps=pref.dynamicSteps;
	dynamicStart=pref.dynamicStart;
	dynamicEnd=pref.dynamicEnd;
	glShadeModel( GL_SMOOTH);
}


///////////////////////////////////////////drawAxes//////////////////////////////////////////

GLuint GraphOutput::drawStdAxes()
{
    GLuint list;
	glDisable(GL_DEPTH_TEST);
    list = glGenLists( 1 );

    glNewList( list, GL_COMPILE );
	//Koordinatensystem

	double xSize=pref.xmax-pref.xmin,ySize=pref.ymax-pref.ymin;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(20.0/xSize,20.0/ySize,1.0f);
	glTranslatef((pref.xmin+pref.xmax)*-0.5f,(pref.ymin+pref.ymax)*-0.5,0.0f);
		
//	MessageBox("xSize: "+QString::number(xSize)+
//			   "ySize: "+QString::number(ySize));
	
	glBegin(GL_LINES);
	
	//Raster
	if(!pref.raster)
	{
		float xLineLen=(pref.xmax-pref.xmin)/80;
		float yLineLen=(pref.ymax-pref.ymin)/80;
		
		float xNull=0.0f;
		float yNull=0.0f;
		if(pref.xmax < 0.0f)
			xNull=pref.xmax;
		else if(pref.xmin > 0.0f)
			xNull=pref.xmin;
		if(pref.ymax < 0.0f)
			yNull=pref.ymax;
		else if(pref.ymin > 0.0f)
			yNull=pref.ymin;
		
		qglColor( QColor(220,220,220) );	
		for(float c=0.0; c<pref.xmax; c+=pref.rasterSizeX)
		{
			glVertex3f(c,yNull-yLineLen,0.0f);
			glVertex3f(c,yNull+yLineLen,0.0f);
		}
		for(float c=0.0; c>pref.xmin; c-=pref.rasterSizeX)
		{
			glVertex3f(c,yNull-yLineLen,0.0f);
			glVertex3f(c,yNull+yLineLen,0.0f);
		}
		for(float c=0.0; c<pref.ymax; c+=pref.rasterSizeY)
		{
			glVertex3f(xNull-xLineLen,c,0.0f);
			glVertex3f(xNull+xLineLen,c,0.0f);
		}
		for(float c=0.0; c>pref.ymin; c-=pref.rasterSizeY)
		{
			glVertex3f(xNull-xLineLen,c,0.0f);
			glVertex3f(xNull+xLineLen,c,0.0f);
		}
	}
	else{
		qglColor( QColor(220,220,220) );	
		for(float c=0.0; c<pref.xmax; c+=pref.rasterSizeX)
		{
			glVertex3f(c,pref.ymin,0.0f);
			glVertex3f(c,pref.ymax,0.0f);
		}
		for(float c=0.0; c>pref.xmin; c-=pref.rasterSizeX)
		{
			glVertex3f(c,pref.ymin,0.0f);
			glVertex3f(c,pref.ymax,0.0f);
		}
		for(float c=0.0; c<pref.ymax; c+=pref.rasterSizeY)
		{
			glVertex3f(pref.xmin,c,0.0f);
			glVertex3f(pref.xmax,c,0.0f);
		}
		for(float c=0.0; c>pref.ymin; c-=pref.rasterSizeY)
		{
			glVertex3f(pref.xmin,c,0.0f);
			glVertex3f(pref.xmax,c,0.0f);
		}
	}
	
	
	if(pref.axis)
	{
		qglColor( QColor(150,150,150) );
		glVertex3f(pref.xmin,0.0f,0.0f);
		glVertex3f(pref.xmax,0.0f,0.0f);
		
		glVertex3f(0.0f,pref.ymin,0.0f);
		glVertex3f(0.0f,pref.ymax,0.0f);
		
		glVertex3f(pref.xmax-xSize*0.015,ySize*0.015,0.0f);
		glVertex3f(pref.xmax,0.0f,0.0f);
		glVertex3f(pref.xmax-xSize*0.015,ySize*-0.015,0.0f);
		glVertex3f(pref.xmax,0.0f,0.0f);
		
		glVertex3f(xSize*0.015,pref.ymax-ySize*0.015,0.0f);
		glVertex3f(0.0f,pref.ymax,0.0f);
		glVertex3f(xSize*-0.015,pref.ymax-ySize*0.015,0.0f);
		glVertex3f(0.0f,pref.ymax,0.0f);
	}
	
	
	glEnd();	
	glEndList();

	return list;
}

GLuint GraphOutput::drawPolarAxes()
{
	GLuint list;

	list = glGenLists( 1 );
	glDisable(GL_DEPTH_TEST);
	glNewList( list, GL_COMPILE );


	double xSize=2.0*pref.radiusMax;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(20.0/xSize,20.0/xSize,1.0f);

	
	double multiplier=1.0;
	if(pref.angle==DEG)
		multiplier=PI/180.0;
	else if(pref.angle==GRA)
		multiplier=PI/200.0;

	

	

	if(pref.raster)
	{
		qglColor( QColor(220,220,220) );
		double angleStep=pref.angleMax/400.0;
		double radiusStep=pref.radiusMax/400.0;
		if(angleStep==0.0)
		{
			return list;
		}
		for(double c=0.0; c<pref.radiusMax+radiusStep; c+=pref.rasterSizeRadius)
		{
			glBegin(GL_LINE_STRIP);
			for(double c1=0.0; c1<=pref.angleMax; c1+=angleStep)
			{
				glVertex3f(cos(c1*multiplier)*c,sin(c1*multiplier)*c,0.0f);
			}
			glEnd();
		}

		glBegin(GL_LINES);
		double outRadius=pref.radiusMax*sqrt(2);
		for(double c=0.0; c<pref.angleMax+angleStep; c+=pref.rasterSizeAngle)
		{
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(cos(c*multiplier)*outRadius,sin(c*multiplier)*outRadius,0.0f);
		}
		glEnd();

	}
	
	if(pref.axis)
	{
		glBegin(GL_LINES);
		qglColor( QColor(150,150,150) );
		glVertex3f(-pref.radiusMax,0.0f,0.0f);
		glVertex3f(pref.radiusMax,0.0f,0.0f);
		
		glVertex3f(0.0f,-pref.radiusMax,0.0f);
		glVertex3f(0.0f,pref.radiusMax,0.0f);
		
		glVertex3f(pref.radiusMax-xSize*0.015,xSize*0.015,0.0f);
		glVertex3f(pref.radiusMax,0.0f,0.0f);
		glVertex3f(pref.radiusMax-xSize*0.015,xSize*-0.015,0.0f);
		glVertex3f(pref.radiusMax,0.0f,0.0f);
		
		glVertex3f(xSize*0.015,pref.radiusMax-xSize*0.015,0.0f);
		glVertex3f(0.0f,pref.radiusMax,0.0f);
		glVertex3f(xSize*-0.015,pref.radiusMax-xSize*0.015,0.0f);
		glVertex3f(0.0f,pref.radiusMax,0.0f);
		glEnd();	
	}
	glEndList();

	return list;
}

GLuint GraphOutput::draw3dAxes()
{
	GLuint list;
	
	//reset rotation

	list = glGenLists( 1 );
	glEnable(GL_DEPTH_TEST);
	glNewList( list, GL_COMPILE );
	//Koordinatensystem

	double xSize=pref.xmax-pref.xmin,ySize=pref.ymax-pref.ymin,zSize=pref.zmax-pref.zmin;

	
	//tanslate and scale to coordinate system preferences

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-pref.xmax-pref.xmin,-pref.ymax-pref.ymin,-pref.zmax-pref.zmin);
	glScalef(20.0/xSize,20.0/ySize,20.0/zSize);
	
	
	glBegin(GL_LINES);
	
	//Raster
	if(pref.raster)
	{
		qglColor( QColor(220,220,220) );	
		for(float c=0.0; c<pref.xmax; c+=pref.rasterSizeX)		//back side
		{
			glVertex3f(c,pref.ymin,pref.zmax);
			glVertex3f(c,pref.ymax,pref.zmax);
		}
		for(float c=0.0; c>pref.xmin; c-=pref.rasterSizeX)
		{
			glVertex3f(c,pref.ymin,pref.zmax);
			glVertex3f(c,pref.ymax,pref.zmax);
		}
		for(float c=0.0; c<pref.ymax; c+=pref.rasterSizeY)
		{
			glVertex3f(pref.xmin,c,pref.zmax);
			glVertex3f(pref.xmax,c,pref.zmax);
		}
		for(float c=0.0; c>pref.ymin; c-=pref.rasterSizeY)
		{
			glVertex3f(pref.xmin,c,pref.zmax);
			glVertex3f(pref.xmax,c,pref.zmax);
		}
		
		for(float c=0.0; c<pref.xmax; c+=pref.rasterSizeX)	// bottom side
		{
			glVertex3f(c,pref.ymin,pref.zmin);
			glVertex3f(c,pref.ymin,pref.zmax);
		}
		for(float c=0.0; c>pref.xmin; c-=pref.rasterSizeX)
		{
			glVertex3f(c,pref.ymin,pref.zmin);
			glVertex3f(c,pref.ymin,pref.zmax);
		}
		for(float c=0.0; c<pref.zmax; c+=pref.rasterSizeZ)
		{
			glVertex3f(pref.xmin,pref.ymin,c);
			glVertex3f(pref.xmax,pref.ymin,c);
		}
		for(float c=0.0; c>pref.zmin; c-=pref.rasterSizeZ)
		{
			glVertex3f(pref.xmin,pref.ymin,c);
			glVertex3f(pref.xmax,pref.ymin,c);
		}
		
		for(float c=0.0; c<pref.zmax; c+=pref.rasterSizeZ)	//left side
		{
			glVertex3f(pref.xmin,pref.ymin,c);
			glVertex3f(pref.xmin,pref.ymax,c);
		}
		for(float c=0.0; c>pref.zmin; c-=pref.rasterSizeZ)
		{
			glVertex3f(pref.xmin,pref.ymin,c);
			glVertex3f(pref.xmin,pref.ymax,c);
		}
		for(float c=0.0; c<pref.ymax; c+=pref.rasterSizeY)
		{
			glVertex3f(pref.xmin,c,pref.zmin);
			glVertex3f(pref.xmin,c,pref.zmax);
		}
		for(float c=0.0; c>pref.ymin; c-=pref.rasterSizeY)
		{
			glVertex3f(pref.xmin,c,pref.zmin);
			glVertex3f(pref.xmin,c,pref.zmax);
		}
	}
	
	
	if(pref.axis)
	{
		double xAxes=0.0,yAxes=0.0,zAxes=0.0;
		if(pref.xmin > 0.0)
			xAxes=pref.xmin;
		else if(pref.xmax < 0.0)
			xAxes=pref.xmax;
		if(pref.ymin > 0.0)
			yAxes=pref.ymin;
		else if(pref.ymax < 0.0)
			yAxes=pref.ymax;
		if(pref.zmin > 0.0)
			zAxes=pref.zmin;
		else if(pref.xmax < 0.0)
			zAxes=pref.zmax;
		
		qglColor( QColor(150,150,150) );
	//	qglColor( QColor(0,0,0) );
		glVertex3f(pref.xmin,yAxes,zAxes);
		glVertex3f(pref.xmax,yAxes,zAxes);
		
		glVertex3f(xAxes,pref.ymin,zAxes);
		glVertex3f(xAxes,pref.ymax,zAxes);
		
		glVertex3f(xAxes,yAxes,pref.zmin);
		glVertex3f(xAxes,yAxes,pref.zmax);
		
		glVertex3f(pref.xmax-xSize*0.015,yAxes+ySize*0.015,zAxes);
		glVertex3f(pref.xmax,yAxes,zAxes);
		glVertex3f(pref.xmax-xSize*0.015,yAxes+ySize*-0.015,zAxes);
		glVertex3f(pref.xmax,yAxes,zAxes);
		
		glVertex3f(xAxes+xSize*0.015,pref.ymax-ySize*0.015,zAxes);
		glVertex3f(xAxes,pref.ymax,zAxes);
		glVertex3f(xAxes+xSize*-0.015,pref.ymax-ySize*0.015,zAxes);
		glVertex3f(xAxes,pref.ymax,zAxes);
		
		glVertex3f(xAxes+xSize*0.015,yAxes,pref.zmax-zSize*0.015);
		glVertex3f(xAxes,yAxes,pref.zmax);
		glVertex3f(xAxes+xSize*-0.015,yAxes,pref.zmax-zSize*0.015);
		glVertex3f(xAxes,yAxes,pref.zmax);
	}
	



	glEnd();	
	
	glEndList();

	return list;
}

void GraphOutput::mouseMoveEvent(QMouseEvent*e)
{
	if(e->state() == Qt::LeftButton)
	{
		if(unlock)
		{
			int moveX=e->x()-mouseX;
			int moveY=e->y()-mouseY;
			
			xRotation+=moveX;
			yRotation+=moveY;
			if(xRotation>360)
				xRotation-=360;
			if(yRotation>360)
				yRotation -=360;
			if(xRotation<0)
			xRotation+=360;
			if(yRotation<0)
			yRotation+=360;
			repaint();
	//		MessageBox("1x: "+QString::number(xRotation)+"\ny: "+QString::number(yRotation));
		}
		mouseX=e->x();
		mouseY=e->y();
	//	MessageBox("2x: "+QString::number(xRotation)+"\ny: "+QString::number(yRotation));
		
	}
}


void GraphOutput::mousePressEvent(QMouseEvent*e)
{
	int iX=e->x();
	int iY=e->y();
	double dX,dY;
	double xSteps=(pref.xmax-pref.xmin)/200.0;
	double ySteps=(pref.ymax-pref.ymin)/200.0;
	
	if(pref.graphType==GRAPHSTD)
	{
		dX=((pref.xmax-pref.xmin)/(double)(geometry().right()-geometry().left()))*(double)iX+pref.xmin; 
		dY=((pref.ymax-pref.ymin)/(double)(geometry().bottom()-geometry().top()))*(double)((geometry().bottom()-geometry().top())-iY)+pref.ymin; 
		dX-=fmod(dX,xSteps);
		dY-=fmod(dY,ySteps);
		emit leftMButtonPressed(dX,dY);
	}
	else if(pref.graphType==GRAPHPOLAR)
	{
		dX=((pref.xmax-pref.xmin)/(double)(geometry().right()-geometry().left()))*(double)iX+pref.xmin; 
		dY=((pref.ymax-pref.ymin)/(double)(geometry().bottom()-geometry().top()))*(double)((geometry().bottom()-geometry().top())-iY)+pref.ymin; 
		dX-=fmod(dX,xSteps);
		dY-=fmod(dY,ySteps);
		double angle, radius;
		angle=atan(dY/dX);
		radius=sqrt(dX*dX+dY*dY);
		
		emit leftMButtonPressed(angle,radius);
	}
	else if(pref.graphType==GRAPH3D)
	{
		if(e->stateAfter()==Qt::LeftButton)
		{
			mouseX=e->x();
			mouseY=e->y();
			unlock=true;
		}
		else unlock=false;
	}
	
	//	MessageBox("X: "+QString::number(dX)+"\nY: "+QString::number(dY));
}

void GraphOutput::mouseReleaseEvent(QMouseEvent*e)
{
	if(e->state() == Qt::LeftButton)
		unlock=false;	
}

void GraphOutput::wheelEvent(QWheelEvent*e)
{

	zMove+=e->delta()/120;
	e->accept();
	repaint();
	if(zMove<-27)
		zMove=-27;

}


void GraphOutput::processStdFunction(QString function,QColor color)
{
    GLuint list;
	char*func;
	func = checkString(function,&pref,vars);

    list = glGenLists( 1 );
    glNewList( list, GL_COMPILE );
	double xStart,xStep;
	xStart=pref.xmin;
	xStep=(pref.xmax-pref.xmin)/200;

	
	int colored=0;
	float height=pref.ymax-pref.ymin;
	middle=pref.ymin+height/2.0;		//calculate middle height
	lowerMiddle=-height/4.0;
	upperMiddle=height/4.0;

	if(color==QColor(1,1,1))
		colored=1;
	else qglColor( color );
	
	double fakt;
	if(pref.angle==DEG)
		fakt=180.0/PI;
	else if(pref.angle==RAD)
		fakt=1.0;
	else fakt=200.0/PI;



	glBegin(GL_LINE_STRIP);
		float y,oldy=0.0;
		QString num,num2;
		Calculate ca1(NULL,func,&pref,vars);
		struct timeval t1,t2;
		bool end=false;

		gettimeofday(&t1,NULL);
		for(int c=0; c<200; c++)
		{
			vars[23][0]=xStart+(double)c*xStep;
			y=ca1.calc();
	//		y=(4*pow(vars[23],3.0)-3*pow(vars[23],2.0)+4*vars[23]-3)/(pow(vars[23],5.0)-3*pow(vars[23],2)+4);
	//		y=sin(vars[23]*fakt);
			if(end)
			{
				if(y >pref.ymin && y < pref.ymax)
				{
					glBegin(GL_LINE_STRIP);
					end=false;
					if(colored)
						setGLColor(oldy);
					glVertex3f(xStart+(double)(c-1)*xStep,oldy,0.0f);
					if(colored)
						setGLColor(y);
					glVertex3f(xStart+(double)c*xStep,y,0.0f);
				}
				else oldy=y;
			}
			else {
				if(colored)
					setGLColor(y);
				glVertex3f(xStart+(double)c*xStep,y,0.0f);
				if(y>pref.ymax || y<pref.ymin)
				{
					glEnd();
					end=true;
					oldy=y;
				}
			}
			
		}
		gettimeofday(&t2,NULL);

	glEnd();
    glEndList();
	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	MessageBox(  "Sekunden:      "+QString::number(seconds)+
//			   "\nMicrosekunden: "+QString::number(usecs));
	perror(QString::number(seconds)+"s "+QString::number(usecs)+"us ");
	delete[]func;
   objects.NewItem(list);
}


void GraphOutput::processPolarFunction(QString function,QColor color)
{
	GLuint list;
	char*func;
	func = checkString(function,&pref,vars);

	list = glGenLists( 1 );
	glNewList( list, GL_COMPILE );
	double xStart,xStep;
	xStart=0;
	double multiplier=1.0;
	xStep=pref.angleMax/200.0;
	if(pref.angle==DEG)
	{
		multiplier=PI/180.0;
	}
	else if(pref.angle==GRA)
	{
		multiplier=PI/200.0;
	}
	
	int colored=0;
	float height=pref.radiusMax*2.0;
	middle=0.0;		//calculate middle height
	lowerMiddle=-height/4.0;
	upperMiddle=height/4.0;

	if(color==QColor(1,1,1))
		colored=1;
	else qglColor( color );


	glBegin(GL_LINE_STRIP);
	float oldr=0.0,r,x,y,oldx=0.0,oldy=0.0;
	QString num,num2;
	Calculate ca1(NULL,func,&pref,vars);
	struct timeval t1,t2;
	bool end=false;

	gettimeofday(&t1,NULL);
	for(int c=0; c<=200; c++)
	{
		vars[23][0]=xStart+(double)c*xStep;
		r=ca1.calc();
		x=cos(vars[23][0]*multiplier)*r;
		y=sin(vars[23][0]*multiplier)*r;
		if(end)
		{
			if(y >pref.ymin && y < pref.ymax)
			{
				glBegin(GL_LINE_STRIP);
				end=false;
				if(colored)
					setGLColor(oldr);
				glVertex3f(oldx,oldy,0.0f);
				if(colored)
					setGLColor(r);
				glVertex3f(x,y,0.0f);
			}
			else {
				oldy=y;
				oldx=x;
				oldr=r;
			}
		}
		else {
			if(colored)
				setGLColor(r);
			glVertex3f(x,y,0.0f);
			if(y>pref.ymax || y<pref.ymin)
			{
				glEnd();
				end=true;
				oldy=y;
				oldx=x;
				oldr=r;
			}
		}
			
	}
	gettimeofday(&t2,NULL);

	glEnd();
	glEndList();
	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	MessageBox(  "Sekunden:      "+QString::number(seconds)+
//			   "\nMicrosekunden: "+QString::number(usecs));
	delete[]func;
	objects.NewItem(list);
}

void GraphOutput::processParameterFunction(QString function,QColor color)
{
	GLuint list;
	char*func1,*func2;
	QString f1,f2;
	int sep=function.find("\\");
	if(sep==-1)
	{
		f1="";
		f2="";
	}
	else {
		f1=function.left(sep);
		f2=function.right(function.length()-1-sep);
	}
	func1 = checkString(f1,&pref,vars);
	func2 = checkString(f2,&pref,vars);

	list = glGenLists( 1 );
	glNewList( list, GL_COMPILE );
	double xStart,xStep;
	xStart=pref.parameterStart;
	xStep=(pref.parameterEnd-pref.parameterStart)/(double)pref.parameterSteps;

	qglColor( color );

	glBegin(GL_LINE_STRIP);
	float x,y,oldx=0.0,oldy=0.0;
	QString num,num2;
	Calculate ca1(NULL,func1,&pref,vars);
	Calculate ca2(NULL,func2,&pref,vars);
	struct timeval t1,t2;
	bool end=false;

	gettimeofday(&t1,NULL);
	for(int c=0; c<pref.parameterSteps; c++)
	{
		vars[19][0]=xStart+(double)c*xStep;
		x=ca1.calc();
		y=ca2.calc();
		if(end)
		{
			if(y >pref.ymin && y < pref.ymax && x>pref.xmin && x<pref.xmax)
			{
				glBegin(GL_LINE_STRIP);
				end=false;
				glVertex3f(oldx,oldy,0.0f);
				glVertex3f(x,y,0.0f);
			}
			else {
				oldx=x;
				oldy=y;
			}
		}
		else {
			glVertex3f(x,y,0.0f);
			if(y>pref.ymax || y<pref.ymin || x>pref.xmax || x<pref.xmin)
			{
				glEnd();
				end=true;
				oldx=x;
				oldy=y;
			}
		}
			
	}
	gettimeofday(&t2,NULL);

	glEnd();
	glEndList();
	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	MessageBox(  "Sekunden:      "+QString::number(seconds)+
//			   "\nMicrosekunden: "+QString::number(usecs));
	delete[]func1;
	delete[]func2;
	objects.NewItem(list);
}


void GraphOutput::setGLColor(float y)
{
	y-=middle;

	float r,g,b;
	if(y>upperMiddle)
	{
		r=1.0;
		g=1.0-(y-upperMiddle)/(upperMiddle);
		b=0.0;
	}
	else if(y>0.0)
	{
		r=(y/upperMiddle);
		g=1.0;
		b=0.0;

	}
	else if(y>lowerMiddle)
	{
		r=0.0;
		g=1.0;
		b=(y/lowerMiddle);
	}
	else
	{
		r=0.0;
		g=1.0-(y-lowerMiddle)/(lowerMiddle);
		b=1.0;
	}
	
	glColor3f(r,g,b);
}



void GraphOutput::process3dFunction(QString function,QColor color)
{
	static int rasterSize=50;
	GLuint list;
	char*func;
	func = checkString(function,&pref,vars);
	int colored=0;

	list = glGenLists( 1 );
	glNewList( list, GL_COMPILE );
	double xStart,xStep,zStart,zStep;
	xStart=pref.xmin;
	zStart=pref.zmin;
	xStep=(pref.xmax-pref.xmin)/rasterSize;
	zStep=(pref.zmax-pref.zmin)/rasterSize;
	
	float height=pref.ymax-pref.ymin;
	middle=pref.ymin+height/2.0;		//calculate middle height
	lowerMiddle=-height/4.0;
	upperMiddle=height/4.0;

	if(color==QColor(1,1,1))
		colored=1;
	else qglColor( color );

	//Code for 3D-graphs with lines
	
	glBegin(GL_LINES);
	glMatrixMode(GL_MODELVIEW);
	float y;
	float lastY[rasterSize+1];
	QString num,num2;
	Calculate ca1(NULL,func,&pref,vars);
	struct timeval t1,t2;

	gettimeofday(&t1,NULL);
	vars[25][0]=zStart;
	vars[23][0]=xStart;
	lastY[0]=ca1.calc();
	for(int c=1; c<=rasterSize;c++)
	{
		vars[25][0]=zStart+(double)c*zStep;
		y=ca1.calc();
		if((y > pref.ymin&&y<pref.ymax) || (lastY[c-1] > pref.ymin && lastY[c-1] < pref.ymax))
		{
			double newZStep=zStep,oldZStep=0.0,newY=y,oldY=lastY[c-1];
			if(y<pref.ymin && lastY[c-1]>pref.ymin)
			{
				newY=pref.ymin;
				newZStep=zStep*(oldY-pref.ymin)/(oldY-y);
			}
			else if(y>pref.ymax && lastY[c-1]<pref.ymax)
			{
				newY=pref.ymax;
				newZStep=zStep*(pref.ymax-oldY)/(y-oldY);
			}
			else if(y>pref.ymin && lastY[c-1]<pref.ymin)
			{
				oldY=pref.ymin;
				oldZStep=zStep*(pref.ymin-oldY)/(y-oldY);
			}
			else if(y<pref.ymax && lastY[c-1]>pref.ymax)
			{
				oldY=pref.ymax;
				oldZStep=zStep*(oldY-pref.ymax)/(oldY-y);
			}
			oldZStep+=zStep*(c-1)+zStart;
			newZStep+=zStep*(c-1)+zStart;
			if(colored)
				setGLColor(oldY);
			glVertex3f(xStart,oldY,oldZStep);
			if(colored)
				setGLColor(newY);
			glVertex3f(xStart,newY,newZStep);
		}
		lastY[c]=y;
	}
	for(int c=1; c<=rasterSize; c++)
	{
		vars[23][0]=xStart+(double)c*xStep;
		vars[25][0]=zStart;
		y=ca1.calc();
		if((y > pref.ymin&&y<pref.ymax) || (lastY[0] > pref.ymin && lastY[0] < pref.ymax))
		{
			double newXStep=xStep,oldXStep=0.0,newY=y,oldY=lastY[0];
			if(y<pref.ymin && lastY[0]>pref.ymin)
			{
				newY=pref.ymin;
				newXStep=xStep*(oldY-pref.ymin)/(oldY-y);
			}
			else if(y>pref.ymax && lastY[0]<pref.ymax)
			{
				newY=pref.ymax;
				newXStep=xStep*(pref.ymax-oldY)/(y-oldY);
			}
			else if(y>pref.ymin && lastY[0]<pref.ymin)
			{
				oldY=pref.ymin;
				oldXStep=xStep*(pref.ymin-oldY)/(y-oldY);
			}
			else if(y<pref.ymax && lastY[0]>pref.ymax)
			{
				oldY=pref.ymax;
				oldXStep=xStep*(oldY-pref.ymax)/(oldY-y);
			}
			oldXStep+=xStep*(c-1)+xStart;
			newXStep+=xStep*(c-1)+xStart;
			if(colored)
				setGLColor(oldY);
			glVertex3f(oldXStep,oldY,zStart);
			if(colored)
				setGLColor(newY);
			glVertex3f(newXStep,newY,zStart);
		}
		lastY[0]=y;
		for(int c1=1; c1<=rasterSize; c1++)
		{
			vars[25][0]=zStart+(double)c1*zStep;
			y=ca1.calc();


			if((y > pref.ymin&&y<pref.ymax) || (lastY[c1] > pref.ymin && lastY[c1] < pref.ymax))
			{
				double newXStep=xStep,oldXStep=0.0,newY=y,oldY=lastY[c1];
				if(y<pref.ymin && lastY[c1]>pref.ymin)
				{
					newY=pref.ymin;
					newXStep=xStep*(oldY-pref.ymin)/(oldY-y);
				}
				else if(y>pref.ymax && lastY[c1]<pref.ymax)
				{
					newY=pref.ymax;
					newXStep=xStep*(pref.ymax-oldY)/(y-oldY);
				}
				else if(y>pref.ymin && lastY[c1]<pref.ymin)
				{
					oldY=pref.ymin;
					oldXStep=xStep*(pref.ymin-oldY)/(y-oldY);
				}
				else if(y<pref.ymax && lastY[c1]>pref.ymax)
				{
					oldY=pref.ymax;
					oldXStep=xStep*(oldY-pref.ymax)/(oldY-y);
				}
				oldXStep+=xStep*(c-1)+xStart;
				newXStep+=xStep*(c-1)+xStart;
				if(colored)
					setGLColor(oldY);
				glVertex3f(oldXStep,oldY,zStart+c1*zStep);
				if(colored)
					setGLColor(newY);
				glVertex3f(newXStep,newY,zStart+c1*zStep);
			}
			if((y > pref.ymin&&y<pref.ymax) || (lastY[c1-1] > pref.ymin && lastY[c1-1] < pref.ymax))
			{
				double newZStep=zStep,oldZStep=0.0,newY=y,oldY=lastY[c1-1];
				if(y<pref.ymin && lastY[c1-1]>pref.ymin)
				{
					newY=pref.ymin;
					newZStep=zStep*(oldY-pref.ymin)/(oldY-y);
				}
				else if(y>pref.ymax && lastY[c1-1]<pref.ymax)
				{
					newY=pref.ymax;
					newZStep=zStep*(pref.ymax-oldY)/(y-oldY);
				}
				else if(y>pref.ymin && lastY[c1-1]<pref.ymin)
				{
					oldY=pref.ymin;
					oldZStep=zStep*(pref.ymin-oldY)/(y-oldY);
				}
				else if(y<pref.ymax && lastY[c1-1]>pref.ymax)
				{
					oldY=pref.ymax;
					oldZStep=zStep*(oldY-pref.ymax)/(oldY-y);
				}
				oldZStep+=zStep*(c1-1)+zStart;
				newZStep+=zStep*(c1-1)+zStart;
				if(colored)
					setGLColor(oldY);
				glVertex3f(c*xStep+xStart,oldY,oldZStep);
				if(colored)
					setGLColor(newY);
				glVertex3f(c*xStep+xStart,newY,newZStep);
			}
			lastY[c1]=y;
		}
	}
	gettimeofday(&t2,NULL);

	glEnd();
	/*
	// Code for 3D-graphs with polygons
	glMatrixMode(GL_MODELVIEW);
	float y;
	float lastY[rasterSize+1];
	QString num,num2;
	Calculate ca1(NULL,func,&pref,vars);
	struct timeval t1,t2;
	bool end=false;

	gettimeofday(&t1,NULL);
	vars[25]=zStart;
	vars[23]=xStart;
	lastY[0]=ca1.calc();
	for(int c=1; c<=rasterSize;c++)
	{
		vars[25]=zStart+(double)c*zStep;
		lastY[c]=ca1.calc();
	}
	for(int c=1; c<=rasterSize;c++)
	{
		vars[23]=xStart+c*xStep;
		glBegin(GL_TRIANGLE_STRIP);
		for(int c1=0; c1<=rasterSize; c1++)
		{
			vars[25]=zStart+c1*zStep;
			y=ca1.calc();
			if((y > pref.ymin&&y<pref.ymax) || (lastY[c1] > pref.ymin && lastY[c1] < pref.ymax))
			{
				if(end)
				{
					glBegin(GL_TRIANGLE_STRIP);
					end=false;
				}
				if(colored)
					setGLColor(lastY[c1]);
				glVertex3f(xStart+(c-1)*xStep,lastY[c1],vars[25]);
				if(colored)
					setGLColor(y);
				glVertex3f(xStart+(c)*xStep,y,vars[25]);
			}
			else {
				glEnd();
				end=true;
			}

			lastY[c1]=y;
		}
		glEnd();
	}
	//end
	*/	
	glEndList();

	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	MessageBox(  "Sekunden:      "+QString::number(seconds)+
//			   "\nMicrosekunden: "+QString::number(usecs));
	delete[]func;
	objects.NewItem(list);
}


void GraphOutput::processInequaityFunction(QString function,QColor color,int type,QString iFunction,QColor iColor,int iType)
{
	bool showIntersection=false;
	if(iFunction!=QString(""))
		showIntersection=true;
		
    GLuint list;
	char*func;
	func = checkString(function,&pref,vars);

    list = glGenLists( 1 );
    glNewList( list, GL_COMPILE );
	double xStart,xStep;
	xStart=pref.xmin;
	xStep=(pref.xmax-pref.xmin)/200;
	double endLine;
	
	int colored=0;
	float height=pref.ymax-pref.ymin;
	middle=pref.ymin+height/2.0;		//calculate middle height
	lowerMiddle=-height/4.0;
	upperMiddle=height/4.0;

	if(color==QColor(1,1,1))
		colored=1;
	else qglColor( color );
	
	if(type==GRAPHIEGE || type==GRAPHIEG)
		endLine=pref.ymax;
	else endLine=pref.ymin;
	struct timeval t1,t2;
	if(showIntersection)
	{
		float y,oldy=0.0;
		QString num,num2;
		Calculate ca1(NULL,func,&pref,vars);
		bool end=false;
		
		glBegin(GL_LINE_STRIP);
		if(color==QColor(1,1,1))
			colored=1;
		else qglColor( color );
		for(int c=0; c<200; c++)
		{
			vars[23][0]=xStart+(double)c*xStep;
			y=ca1.calc();
			if(end)
			{
				if(y >pref.ymin && y < pref.ymax)
				{
					glBegin(GL_LINE_STRIP);
					end=false;
					if(colored)
						setGLColor(oldy);
					glVertex3f(xStart+(double)(c-1)*xStep,oldy,0.0f);
					if(colored)
						setGLColor(y);
					glVertex3f(xStart+(double)c*xStep,y,0.0f);
				}
				else oldy=y;
			}
			else {
				if(colored)
					setGLColor(y);
				glVertex3f(xStart+(double)c*xStep,y,0.0f);
				if(y>pref.ymax || y<pref.ymin)
				{
					glEnd();
					end=true;
					oldy=y;
				}
			}
		}
		glEnd();
		
		char*func2=checkString(iFunction,&pref,vars);
		Calculate ca2(NULL,func2,&pref,vars);
		
		glBegin(GL_LINE_STRIP);
		if(iColor==QColor(1,1,1))
			colored=1;
		else qglColor( iColor );
		for(int c=0; c<200; c++)
		{
			vars[23][0]=xStart+(double)c*xStep;
			y=ca2.calc();
			if(end)
			{
				if(y >pref.ymin && y < pref.ymax)
				{
					glBegin(GL_LINE_STRIP);
					end=false;
					if(colored)
						setGLColor(oldy);
					glVertex3f(xStart+(double)(c-1)*xStep,oldy,0.0f);
					if(colored)
						setGLColor(y);
					glVertex3f(xStart+(double)c*xStep,y,0.0f);
				}
				else oldy=y;
			}
			else {
				if(colored)
					setGLColor(y);
				glVertex3f(xStart+(double)c*xStep,y,0.0f);
				if(y>pref.ymax || y<pref.ymin)
				{
					glEnd();
					end=true;
					oldy=y;
				}
			}
		}
		glEnd();
		qglColor(QColor(120,120,255));
		bool sameOrientation=false;
		if((iType==GRAPHIEGE || iType==GRAPHIEG) && (type==GRAPHIEGE || type==GRAPHIEG) ||
				  (iType==GRAPHIELE || iType==GRAPHIEL) && (type==GRAPHIELE || type==GRAPHIEL))
			sameOrientation=true;
		

		xStep=(pref.xmax-pref.xmin)/400;
		glBegin(GL_TRIANGLE_STRIP);
		end=false;
		double y1,y2;
		double oldy1=0.0,oldy2=0.0;
		for(int c=0; c<400; c++)
		{
			vars[23][0]=xStart+(double)c*xStep;
			y1=ca1.calc();
			y2=ca2.calc();

			if(y1<pref.ymax && y1>pref.ymin && (
			(y1<endLine && y2>y1 && y2<pref.ymax) ||
			(y1>endLine && y2<y1 && y2>pref.ymin) || 
			(sameOrientation && y2<pref.ymax && y2>pref.ymin))
			)
			{
				if(end)
				{
					glBegin(GL_TRIANGLE_STRIP);
					if(sameOrientation)
					{
						if((oldy2>oldy1 && oldy2>endLine) || (oldy2<endLine && oldy1>oldy2))
							glVertex3f(xStart+(double)(c-1)*xStep,oldy1,0.0);
						else glVertex3f(xStart+(double)(c-1)*xStep,oldy2,0.0);
						glVertex3f(xStart+(double)(c-1)*xStep,endLine,0.0);
						if((y2>y1 && y2>endLine) ||  (y2<endLine && y1>y2))
							glVertex3f(xStart+(double)c*xStep,y1,0.0);
						else glVertex3f(xStart+(double)c*xStep,y2,0.0);
						glVertex3f(xStart+(double)c*xStep,endLine,0.0);
					}
					else {
						glVertex3f(xStart+(double)(c-1)*xStep,oldy1,0.0);
						glVertex3f(xStart+(double)(c-1)*xStep,oldy2,0.0);
						glVertex3f(xStart+(double)c*xStep,y1,0.0);
						glVertex3f(xStart+(double)c*xStep,y2,0.0);
					}
					end=false;
				}
				else 
				{					
					if(sameOrientation)
					{
						if((y2>y1 && y2>endLine) ||  (y2<endLine && y1>y2))
							glVertex3f(xStart+(double)c*xStep,y1,0.0);
						else glVertex3f(xStart+(double)c*xStep,y2,0.0);
						glVertex3f(xStart+(double)c*xStep,endLine,0.0);
					}
					else {
						glVertex3f(xStart+(double)c*xStep,y1,0.0);
						glVertex3f(xStart+(double)c*xStep,y2,0.0);
					}
				}
			}
			else {
				if(end)
				{
					oldy1=y1;
					oldy2=y2;
				}
				else 
				{
					glEnd();
					oldy1=y1;
					oldy2=y2;
					end=true;
				}
			}
		}
		glEnd();
		
		glEndList();
	}
	else 
	{
		glBegin(GL_TRIANGLE_STRIP);
			float y,oldy=0.0;
			QString num,num2;
			Calculate ca1(NULL,func,&pref,vars);
			bool end=false;
	
		for(int c=0; c<200; c++)
		{
			vars[23][0]=xStart+(double)c*xStep;
			y=ca1.calc();
	
			if(colored)
				setGLColor(y);

			if(y<pref.ymin)
				y=pref.ymin;
			if(y>pref.ymax)
				y=pref.ymax;
					
			glVertex3f(xStart+(double)c*xStep,y,0.0f);
			glVertex3f(xStart+(double)c*xStep,endLine,0.0f);


		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0,0.0,0.0);
		for(int c=0; c<200; c++)
		{
			vars[23][0]=xStart+(double)c*xStep;
			y=ca1.calc();
			if(end)
			{
				if(y >pref.ymin && y < pref.ymax)
				{
					glBegin(GL_LINE_STRIP);
					end=false;
					glVertex3f(xStart+(double)(c-1)*xStep,oldy,0.0f);
					glVertex3f(xStart+(double)c*xStep,y,0.0f);
				}
				else oldy=y;
			}
			else {
				glVertex3f(xStart+(double)c*xStep,y,0.0f);
				if(y>pref.ymax || y<pref.ymin)
				{
					glEnd();
					end=true;
					oldy=y;
				}
			}
		}
		glEnd();
		glEndList();
	}
	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	MessageBox(  "Sekunden:      "+QString::number(seconds)+
//			   "\nMicrosekunden: "+QString::number(usecs));
	delete[]func;
   objects.NewItem(list);
}



///////////////////////////////////////////paintGL///////////////////////////////////////////

void GraphOutput::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if(pref.graphType==GRAPH3D)
	{
		glFrustum(-10.0,10.0,-10.0,10.0,1.0,100.0);
		glScalef(1.0,1.0,-0.05);
		glTranslatef(0.0,0.0,37.0+(float)zMove);
		glRotatef(xRotation,0.0f,1.0f,0.0f);
		glRotatef(yRotation,1.0f,0.0f,0.0f);
	}
	else 
	{
		glFrustum(-10.0,10.0,-10.0,10.0,1.0,100.0);
		glTranslatef(0.0,0.0,-1.0);
	}

	glCallList(axes);
//	for(int c=0; c<objects.GetLen(); c++)
//		glCallList(objects[c]);

//	perror("\n");
//	for(int c=0; c<drawRules.GetLen(); c++)
//		for(int c1=0; c1<drawRules[c][0]; c1++)
//			perror("DrawRules: "+QString::number(c)+" indices: "+QString::number(drawRules[c][c1+1]));
//	perror("\n");	
	for(int c=0; c<drawRules.GetLen(); c++)
	{
		if(dynamicPos<drawRules[c][0])
		{
			glCallList(objects[drawRules[c][dynamicPos+1]]);
		}
		else 
		{
			glCallList(objects[drawRules[c][drawRules[c][0]]]);
		}
		
	
	}
		


	qglColor(QColor(100,100,255));
	for(int c=0; c<additionalObjects.GetLen(); c++)
		glCallList(additionalObjects[c]);

	if(pref.label)
	{
		QFont stdFont("Helvetica");
		stdFont.setPixelSize(8);

		

		double xTrans=(pref.xmax-pref.xmin)/80;
		double yTrans=(pref.ymax-pref.ymin)/80;
		double staticX=xTrans,staticY=yTrans;
		if(pref.xmax < xTrans)
			staticX=pref.xmax-3*xTrans;
		else if(pref.xmin > -xTrans)
			staticX=pref.xmin+xTrans;
		if(pref.ymax < yTrans)
			staticY=pref.ymax-3*yTrans;
		else if(pref.ymin > -yTrans)
			staticY=pref.ymin+yTrans;
				
		qglColor( QColor(220,220,220) );
		for(float c=0; c<pref.xmax; c+=pref.rasterSizeX)
			renderText(c-xTrans,staticY,0.0f,QString::number(c,'g',3),stdFont);
		for(float c=0; c>pref.xmin; c-=pref.rasterSizeX)
			renderText(c-xTrans,staticY,0.0f,QString::number(c,'g',3),stdFont);
		
		for(float c=0; c<pref.ymax; c+=pref.rasterSizeY)
			renderText(staticX,c-yTrans,0.0f,QString::number(c,'g',3),stdFont);
		for(float c=0; c>pref.ymin; c-=pref.rasterSizeY)
			renderText(staticX,c-yTrans,0.0f,QString::number(c,'g',3),stdFont);
		
		if(pref.graphType == GRAPH3D)
		{
			double zTrans=(pref.zmax-pref.zmin)/80;
			double staticZ=zTrans;
			if(pref.zmax < zTrans)
				staticZ=pref.zmax-3*zTrans;
			else if(pref.zmin > -zTrans)
				staticZ=pref.zmin+zTrans;
			for(float c=0; c<pref.zmax; c+=pref.rasterSizeZ)
				renderText(staticX,staticY,c-zTrans,QString::number(c,'g',3),stdFont);
			for(float c=0; c>pref.zmin; c-=pref.rasterSizeZ)
				renderText(staticX,staticY,c-zTrans,QString::number(c,'g',3),stdFont);	
			
			
		}
	}
}


//////////////////////////////////////////resizeGL///////////////////////////////////////////

void GraphOutput::resizeGL( int w, int h )
{
    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -10.0, 10.0, -10.0, 10.0, 5.0, 15.0 );
    glMatrixMode( GL_MODELVIEW );
}

///////////////////////////////////////////clearGL///////////////////////////////////////////

void GraphOutput::clearGL()
{
	while(objects.GetLen() > 0)
	{
		glDeleteLists(objects[0],1);
		objects.DeleteItem(0);
	}

	while(drawRules.GetLen() > 0)
	{
		delete[]drawRules[0];
		drawRules.DeleteItem(0);
	}
	isDynamic=false;
	timer->stop();

}

void GraphOutput::setPref(Preferences newPref)
{
	pref=newPref;
	initializeGL();
}



void GraphOutput::processFunction(int index)
{

	int ruleIndex=drawRules.GetLen();
	if(index==ineq2)
		return;
	
	if(!pref.dynamicFunctions[index])
	{
		drawRules.NewItem(new int[2]);
		drawRules[ruleIndex][0]=1;
		switch(pref.functionTypes[index])
		{
			case GRAPHPOLAR:
				processPolarFunction(pref.functions[index],pref.functionColors[index]);
				drawRules[ruleIndex][1]=objects.GetLen()-1;
				break;
			case GRAPHPARAMETER:
				processParameterFunction(pref.functions[index],pref.functionColors[index]);
				drawRules[ruleIndex][1]=objects.GetLen()-1;
				break;
			case GRAPH3D:
				process3dFunction(pref.functions[index],pref.functionColors[index]);
				drawRules[ruleIndex][1]=objects.GetLen()-1;
				break;
			case GRAPHIEG:
			case GRAPHIEGE:
			case GRAPHIEL:
			case GRAPHIELE:
				if(index==ineq1)
					processInequaityFunction(pref.functions[index],pref.functionColors[index],pref.functionTypes[index],pref.functions[ineq2],pref.functionColors[ineq2],pref.functionTypes[ineq2]);
				else processInequaityFunction(pref.functions[index],pref.functionColors[index],pref.functionTypes[index]);
				drawRules[ruleIndex][1]=objects.GetLen()-1;
				break;
			default:
				processStdFunction(pref.functions[index],pref.functionColors[index]);
				drawRules[ruleIndex][1]=objects.GetLen()-1;
				break;
		}
	}
	else 
	{
		drawRules.NewItem(new int[2+dynamicSteps]);
		drawRules[ruleIndex][0]=dynamicSteps+1;
		isDynamic=true;
		switch(pref.functionTypes[index])
		{

			case GRAPHPOLAR:
				for(int c=0; c<=dynamicSteps; c++)
				{
					vars[0][0]=dynamicStart+c*((dynamicEnd-dynamicStart)/(dynamicSteps));
					processPolarFunction(pref.functions[index],pref.functionColors[index]);
					drawRules[ruleIndex][c+1]=objects.GetLen()-1;
				}
				break;
			case GRAPHPARAMETER:
				for(int c=0; c<=dynamicSteps; c++)
				{
					vars[0][0]=dynamicStart+c*((dynamicEnd-dynamicStart)/(dynamicSteps));
					processParameterFunction(pref.functions[index],pref.functionColors[index]);
					drawRules[ruleIndex][c+1]=objects.GetLen()-1;
				}
				break;
			case GRAPH3D:
				for(int c=0; c<=dynamicSteps; c++)
				{
					vars[0][0]=dynamicStart+c*((dynamicEnd-dynamicStart)/(dynamicSteps));
					process3dFunction(pref.functions[index],pref.functionColors[index]);
					drawRules[ruleIndex][c+1]=objects.GetLen()-1;
				}
				break;
			case GRAPHIEG:
			case GRAPHIEGE:
			case GRAPHIEL:
			case GRAPHIELE:
				for(int c=0; c<=dynamicSteps; c++)
				{
					vars[0][0]=dynamicStart+c*((dynamicEnd-dynamicStart)/(dynamicSteps));
					if(index==ineq1)
						processInequaityFunction(pref.functions[index],pref.functionColors[index],pref.functionTypes[index],pref.functions[ineq2],pref.functionColors[ineq2],pref.functionTypes[ineq2]);
					else processInequaityFunction(pref.functions[index],pref.functionColors[index],pref.functionTypes[index]);
					drawRules[ruleIndex][c+1]=objects.GetLen()-1;
				}
				break;
			default:
				for(int c=0; c<=dynamicSteps; c++)
				{
					vars[0][0]=dynamicStart+c*((dynamicEnd-dynamicStart)/(dynamicSteps));
					processStdFunction(pref.functions[index],pref.functionColors[index]);
					drawRules[ruleIndex][c+1]=objects.GetLen()-1;
				}
				break;
		}
		timer->start(pref.dynamicDelay*10,false);
	}
//	perror("\n");
//	for(int c=0; c<drawRules.GetLen(); c++)
//		for(int c1=0; c1<drawRules[c][0]; c1++)
//			perror("DrawRules: "+QString::number(c)+" indices: "+QString::number(drawRules[c][c1+1]));
//	perror("\n");	
}

void GraphOutput::drawHorizontalLine(double y)
{
	GLuint list;
	list = glGenLists( 1 );
	
	glNewList( list, GL_COMPILE );
	glBegin(GL_LINES);
	glVertex3f(pref.xmin,y,0.0f);
	glVertex3f(pref.xmax,y,0.0f);
	glEnd();
	glEndList();
	additionalObjects.NewItem(list);
	repaint();
}


void GraphOutput::drawVerticalLine(double x)
{
	GLuint list;
	list = glGenLists( 1 );
	
	glNewList( list, GL_COMPILE );
	glBegin(GL_LINES);
	glVertex3f(x,pref.ymin,0.0f);
	glVertex3f(x,pref.ymax,0.0f);
	glEnd();
	glEndList();
	additionalObjects.NewItem(list);
	repaint();
}

void GraphOutput::drawCircle(double radius)
{
	GLuint list;
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);
	glBegin(GL_LINE_STRIP);
	double step=PI/200;
	for(int c=0; c<=400; c++)
	{
		glVertex3f(cos((double)c*step)*radius,sin((double)c*step)*radius,0.0f);
	}
	glEnd();
	glEndList();
	additionalObjects.NewItem(list);
	repaint();
}
void GraphOutput::drawPolarLine(double angle)
{
	GLuint list;
	list=glGenLists(1);
	glNewList(list,GL_COMPILE);
	glBegin(GL_LINES);
	glVertex3f(cos(angle)*2.0*pref.radiusMax,sin(angle)*2.0*pref.radiusMax,0.0f);
	glVertex3f(cos(angle)*-2.0*pref.radiusMax,sin(angle)*-2.0*pref.radiusMax,0.0f);
	glEnd();
	glEndList();
	additionalObjects.NewItem(list);
	repaint();
}
void GraphOutput::draw3dXLine(double y,double z)
{
	if(y<pref.ymin || y>pref.ymax || z<pref.zmin || z>pref.zmax)
		return;
	GLuint list;
	list = glGenLists( 1 );
	
	glNewList( list, GL_COMPILE );
	glBegin(GL_LINES);
	glVertex3f(pref.xmin,y,z);
	glVertex3f(pref.xmax,y,z);
	glEnd();
	glEndList();
	additionalObjects.NewItem(list);
	repaint();
}

void GraphOutput::draw3dYLine(double x,double z)
{
	if(x<pref.ymin || x>pref.ymax || z<pref.zmin || z>pref.zmax)
		return;
	GLuint list;
	list = glGenLists( 1 );
	
	glNewList( list, GL_COMPILE );
	glBegin(GL_LINES);
	glVertex3f(x,pref.ymin,z);
	glVertex3f(x,pref.ymax,z);
	glEnd();
	glEndList();
	additionalObjects.NewItem(list);
	repaint();	
	
	
}
void GraphOutput::draw3dZLine(double x,double y)
{
	if(x<pref.ymin || x>pref.ymax || y<pref.zmin || y>pref.zmax)
		return;
	GLuint list;
	list = glGenLists( 1 );
	
	glNewList( list, GL_COMPILE );
	glBegin(GL_LINES);
	glVertex3f(x,y,pref.zmin);
	glVertex3f(x,y,pref.zmax);
	glEnd();
	glEndList();
	additionalObjects.NewItem(list);
	repaint();	
	
	
}
	
void GraphOutput::removeLines()
{
	while(additionalObjects.GetLen() > 0)
		additionalObjects.DeleteItem(0);
	ineq1=ineq2=-1;
	repaint();
}

void GraphOutput::resetRotation()
{
	xRotation=yRotation=0;
	zMove=0;
}

void GraphOutput::timerSlot()
{
	static bool forward=true;
	if(pref.moveUpDown)
	{
		if(forward)
		{
			dynamicPos++;
			if(dynamicPos >= dynamicSteps)
				forward=false;
		}
		else {
			dynamicPos--;
			if(dynamicPos <=0)
				forward=true;
		}
			
	}
	else {
		dynamicPos++;
		if(dynamicPos > dynamicSteps)
			dynamicPos=0;
	}
	repaint();
}

void GraphOutput::inequaityIntersectionSlot(int i1, int i2)
{
	ineq1=i1;
	ineq2=i2;
}



