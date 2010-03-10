/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         graphout.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "graphout.h"
#include <pthread.h>
//Added by qt3to4:
#include <QCustomEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QWheelEvent>

////////////////////////////////////////initializeGL/////////////////////////////////////////

void GraphOutput::initializeGL()
{
  QListIterator<ObjectInfo*> i(objectInfo);
  ObjectInfo*currentObject;
  int c;

	makeCurrent();
	glClearColor( 1.0,1.0,1.0,1.0 );
//	qglClearColor(white ); 
	if(axes!=0xffffffff)
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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	if(texture==0xffffffff)
	{
		glGenTextures(1,&texture);
		generateTexture();
	}
	if(drawState!=DRAWNONE)
		generateTexture();
	
	glDisable(GL_TEXTURE_2D);
	if(drawScreenshot)
	{
		int type;
		//start processing
    for(c=0; c<20; c++)
		{
			if(pref.activeFunctions[c])
			{
				type=pref.functionTypes[c];
				if(type==GRAPHIEGE)
					type=GRAPHIEG;
				else if(type==GRAPHIELE)
					type=GRAPHIEL;
				processFunction(pref.functions[c],"",type,pref.functionColors[c],pref.logicFunctions[c],pref.dynamicFunctions[c]);
				if(type==GRAPHIEL || type==GRAPHIEG)
					processFunction(pref.functions[c],"",GRAPHSTD,QColor(0,0,0),pref.logicFunctions[c],pref.dynamicFunctions[c]);
			}
		}
		
		//graph calculation (without multithreading)
    while(i.hasNext())
		{
      currentObject=i.next();

      for(c=0; c<currentObject->dataLength; c++)
      {
        if(!currentObject->objectData[c].processed)
        {
          processGraph(currentObject,c,threadData,vars);
          currentObject->objectData[c].processed=true;
        }
      }
		}

		//create gl lists
		createGLLists();
		paintGL();
	}
}


///////////////////////////////////////////drawAxes//////////////////////////////////////////

GLuint GraphOutput::drawStdAxes()
{
		
	double xSize=pref.xmax-pref.xmin,ySize=pref.ymax-pref.ymin;
	int xSteps=(int)(xSize/pref.rasterSizeX);
	if(xSteps>200)
		pref.rasterSizeX=xSize/200;
	int ySteps=(int)(ySize/pref.rasterSizeY);
	if(ySteps>200)
		pref.rasterSizeY=ySize/200;
	
    GLuint list;
	glDisable(GL_DEPTH_TEST);
    list = glGenLists( 1 );

    glNewList( list, GL_COMPILE );
	//Koordinatensystem



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
		for(float c=0; c>pref.xmin; c-=pref.rasterSizeX)
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

	int radiusSteps=(int)(pref.radiusMax/pref.rasterSizeRadius);
	if(radiusSteps>200)
		pref.rasterSizeRadius=pref.radiusMax/200.0;
	int angleSteps=(int)(pref.angleMax/pref.rasterSizeAngle);
	if(angleSteps>200)
		pref.rasterSizeAngle=pref.angleMax/200.0;	

	

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
		double outRadius=pref.radiusMax*sqrt(2.0);
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
	
		double xSize=pref.xmax-pref.xmin,ySize=pref.ymax-pref.ymin,zSize=pref.zmax-pref.zmin;
		int xSteps=(int)(xSize/pref.rasterSizeX);
		if(xSteps>200)
			pref.rasterSizeX=xSize/200;
		int ySteps=(int)(ySize/pref.rasterSizeY);
		if(ySteps>200)
			pref.rasterSizeY=ySize/200;
		int zSteps=(int)(zSize/pref.rasterSizeZ);
		if(zSteps>200)
			pref.rasterSizeZ=zSize/200;
		GLuint list;
	
	//reset rotation

	list = glGenLists( 1 );
	glEnable(GL_DEPTH_TEST);
	glNewList( list, GL_COMPILE );
	//Koordinatensystem


	
	//tanslate and scale to coordinate system preferences

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(-pref.xmax-pref.xmin,-pref.ymax-pref.ymin,-pref.zmax-pref.zmin);
//	glTranslatef(-xSize/2-pref.xmin,-ySize/2-pref.ymin,-zSize/2-pref.zmin);
//	glScalef(20.0/xSize,20.0/ySize,20.0/zSize);
	
	glBegin(GL_LINES);
	
	//Raster
	if(pref.raster)
	{

		qglColor( QColor(220,220,220) );

		for(float c=pref.xmin-fmod(pref.xmin,pref.rasterSizeX)+pref.rasterSizeX; c<pref.xmax; c+=pref.rasterSizeX)		
		{
			glVertex3f(c,pref.ymin,pref.zmax);//back side
			glVertex3f(c,pref.ymax,pref.zmax);
			glVertex3f(c,pref.ymin,pref.zmin);// bottom side
			glVertex3f(c,pref.ymin,pref.zmax);
		}

		for(float c=pref.ymin-fmod(pref.ymin,pref.rasterSizeY)+pref.rasterSizeY; c<pref.ymax; c+=pref.rasterSizeY)			
		{
			glVertex3f(pref.xmin,c,pref.zmax);//back side
			glVertex3f(pref.xmax,c,pref.zmax);
			glVertex3f(pref.xmin,c,pref.zmin);//left side
			glVertex3f(pref.xmin,c,pref.zmax);
		}

		for(float c=pref.zmin-fmod(pref.zmin,pref.rasterSizeZ)+pref.rasterSizeZ; c<pref.zmax; c+=pref.rasterSizeZ)	
		{
			glVertex3f(pref.xmin,pref.ymin,c);// bottom side
			glVertex3f(pref.xmax,pref.ymin,c);
			glVertex3f(pref.xmin,pref.ymin,c);//left side
			glVertex3f(pref.xmin,pref.ymax,c);
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
		int width=geometry().right()-geometry().left();
		int height=geometry().bottom()-geometry().top();

		QPen pen(drawColor,drawPen);
		pen.setCapStyle(Qt::RoundCap);

		if(drawState!=DRAWNONE)
		{
			switch(drawState)
			{
				case DRAWFREE:
				{
			/*		draw->begin(this);
					if(drawColor.red()==0 && drawColor.green()==0 && drawColor.blue()==0)
						pen.setColor(QColor(255,255,255));
					draw->setPen(pen);
					draw->drawLine(mouseX,mouseY,e->x(),e->y());
					draw->end();
				*/	if(drawColor.red()==0 && drawColor.green()==0 && drawColor.blue()==0)
						pen.setColor(QColor(0,0,0));
	
					pen.setWidth(drawPen);
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawLine(mouseX*TEXTURESIZE/width,mouseY*TEXTURESIZE/height,e->x()*TEXTURESIZE/width,e->y()*TEXTURESIZE/height);
					draw->end();
					mouseX=e->x();
					mouseY=e->y();

					break; 
				}
				case DRAWLINE:
				{
					(*drawMap)=backupDrawMap->copy();
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawLine(mouseX*TEXTURESIZE/width,mouseY*TEXTURESIZE/height,e->x()*TEXTURESIZE/width,e->y()*TEXTURESIZE/height);
					draw->end();
					break;
				}
				case DRAWRECT:
				{
					(*drawMap)=backupDrawMap->copy();
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawRect(mouseX*TEXTURESIZE/width,mouseY*TEXTURESIZE/height,e->x()*TEXTURESIZE/width-mouseX*TEXTURESIZE/width,e->y()*TEXTURESIZE/height-mouseY*TEXTURESIZE/height);
					draw->end();
					break;
				}
				case DRAWCIRCLE:
				{
					(*drawMap)=backupDrawMap->copy();
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawEllipse(mouseX*TEXTURESIZE/width,mouseY*TEXTURESIZE/height,e->x()*TEXTURESIZE/width-mouseX*TEXTURESIZE/width,e->y()*TEXTURESIZE/height-mouseY*TEXTURESIZE/height);
					draw->end();
					break;
				}
				case DRAWTEXT:
				{
					(*drawMap)=backupDrawMap->copy();
					QFont drawFont=draw->font();
					draw->begin(drawMap);
					draw->setPen(pen);
					drawFont.setPixelSize(8+3*drawPen);
					draw->setFont(drawFont);
					draw->drawText(e->x()*TEXTURESIZE/width,e->y()*TEXTURESIZE/height,drawString);
					draw->end();
					break;
				}
			}
			generateTexture();
			repaint();
		}
	}
	else if(e->state() == Qt::RightButton)
	{
		if(pref.graphType==GRAPH3D)
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
			}
			mouseX=e->x();
			mouseY=e->y();
		}
		
		int iX=e->x()-mouseX,iY=e->y()-mouseY;
		double dX,dY;

		
		if(pref.graphType==GRAPHSTD)
		{
			double xSteps=(pref.xmax-pref.xmin)/PRECISION2D;
	//		double ySteps=(pref.ymax-pref.ymin)/PRECISION2D;
			dX=((pref.xmax-pref.xmin)/(double)(geometry().right()-geometry().left()))*(double)iX; 
			dY=((pref.ymax-pref.ymin)/(double)(geometry().bottom()-geometry().top()))*(double)iY; 
			dX-=fmod(dX,xSteps);
		//	dY-=fmod(dY,ySteps);
			oldXMin=pref.xmin;
			oldXMax=pref.xmax;
			pref.xmax-=dX;
			pref.xmin-=dX;
			pref.ymax+=dY;
			pref.ymin+=dY;
			glDeleteLists(axes,1);
			axes=drawStdAxes();
		//	clearGL();
		//	emit redrawSignal();
			if(updateFunctions(oldXMin,oldXMax))
			{
				mouseX=e->x();
			}
			mouseY=e->y();
			repaint(); 
		}
		
	}
}


void GraphOutput::mousePressEvent(QMouseEvent*e)
{
	int iX=e->x();
	int iY=e->y();
	double dX,dY;
	double xSteps=(pref.xmax-pref.xmin)/200.0;
	double ySteps=(pref.ymax-pref.ymin)/200.0;
	mouseX=e->x();
	mouseY=e->y();
	if(e->stateAfter()==Qt::LeftButton)
	{
		if(drawState!=DRAWNONE)
		{
			int width=geometry().right()-geometry().left();
			int height=geometry().bottom()-geometry().top();

			previewPen=drawPen*width/TEXTURESIZE;
			if(previewPen<1)
				previewPen=1;
			QPen pen(drawColor,previewPen);
			pen.setCapStyle(Qt::RoundCap);

			if(backMap[BACKSTEPS-1]!=NULL)
				delete backMap[BACKSTEPS-1];
			for(int c=BACKSTEPS-1; c>0; c--)
				backMap[c]=backMap[c-1];
			backMap[0]=drawMap;
			drawMap=new QPixmap(drawMap[0]);
			backCursor=0;

			switch(drawState)
			{
				case DRAWFREE:
					if(drawColor.red()==0 && drawColor.green()==0 && drawColor.blue()==0)
						pen.setColor(drawColor);
					
					pen.setWidth(drawPen);
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawPoint(e->x()*TEXTURESIZE/width,e->y()*TEXTURESIZE/height);
					draw->end();
					break;
				case DRAWLINE:
				case DRAWRECT:
				case DRAWTEXT:
				case DRAWCIRCLE:
					backupDrawMap=new QPixmap(drawMap[0]);
					break;
			}
			
			generateTexture();
			repaint();
		}
		else if(pref.graphType==GRAPHSTD)
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
			if(dX<0)
				angle+=PI;
			else if(dX>0 && dY<0)
				angle+=2*PI;
			else if(dX==0)
			{
				if(dY>0)
				angle=PI/2.0;
				else angle=3.0*PI/2.0;
			}
					
			if(pref.angle==DEG)
				angle*=180.0/PI;
			else if(pref.angle==GRA)
				angle*=200.0/PI;
			radius=sqrt(dX*dX+dY*dY);
			
			emit leftMButtonPressed(angle,radius);
		}
	}
	else if(e->stateAfter()==Qt::RightButton)
	{
		if(pref.graphType==GRAPH3D)
		unlock=true;
	}
	
	// MessageBox("X: "+QString::number(dX)+"\nY: "+QString::number(dY));
}

void GraphOutput::mouseReleaseEvent(QMouseEvent*e)
{
	if(e->state() == Qt::LeftButton)
	{
		unlock=false;
		if(drawState!=DRAWNONE)
		{
			int width=geometry().right()-geometry().left();
			int height=geometry().bottom()-geometry().top();
			QPen pen(drawColor,drawPen);
			pen.setCapStyle(Qt::RoundCap);
			switch(drawState)
			{
				case DRAWFREE:
					break;
				case DRAWLINE:
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawLine(mouseX*TEXTURESIZE/width,mouseY*TEXTURESIZE/height,e->x()*TEXTURESIZE/width,e->y()*TEXTURESIZE/height);
					draw->end();
					delete backupDrawMap;
					break;
				case DRAWRECT:
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawRect(mouseX*TEXTURESIZE/width,mouseY*TEXTURESIZE/height,e->x()*TEXTURESIZE/width-mouseX*TEXTURESIZE/width,e->y()*TEXTURESIZE/height-mouseY*TEXTURESIZE/height);
					draw->end();
					delete backupDrawMap;
					break;
				case DRAWCIRCLE:
					draw->begin(drawMap);
					draw->setPen(pen);
					draw->drawEllipse(mouseX*TEXTURESIZE/width,mouseY*TEXTURESIZE/height,e->x()*TEXTURESIZE/width-mouseX*TEXTURESIZE/width,e->y()*TEXTURESIZE/height-mouseY*TEXTURESIZE/height);
					draw->end();
					delete backupDrawMap;
					break;
				case DRAWTEXT:
				{
					repaint();
				
					QFont drawFont=draw->font();
					int oldWidth=drawFont.pixelSize();
					
					draw->begin(drawMap);
					draw->setPen(pen);
					drawFont.setPixelSize(8+3*drawPen);
					draw->setFont(drawFont);
					draw->drawText(e->x()*TEXTURESIZE/width,e->y()*TEXTURESIZE/height,drawString);
					drawFont.setPixelSize(oldWidth);
					draw->setFont(drawFont);
					draw->end();
					delete backupDrawMap;
					break;
				}
			}
			generateTexture();
			repaint();

		}
	}
	if(e->state() == Qt::RightButton && pref.graphType==GRAPHSTD)
		emit prefChange(pref);
}

void GraphOutput::wheelEvent(QWheelEvent*e)
{
	if(pref.graphType==GRAPH3D)
	{
		zMove+=e->delta()/120;
		e->accept();
		repaint();
		if(zMove<-27)
			zMove=-27;
	}
	else if(pref.graphType==GRAPHPOLAR)
	{
		
		
		pref.radiusMax+=pref.radiusMax/(e->delta()/4);
		pref.xmin=pref.radiusMax*-1.0;
		pref.xmax=pref.radiusMax;
		pref.ymin=pref.radiusMax*-1.0;
		pref.ymax=pref.radiusMax;
		oldXMin=pref.xmin;
		oldXMax=pref.xmax;
		glDeleteLists(axes,1);
		axes=drawPolarAxes();
		updateFunctions(pref.xmin-6*pref.radiusMax,pref.xmax-6*pref.radiusMax);
		repaint();
		emit prefChange(pref);
		
	}
	else 
	{
		double xSize=(pref.xmax-pref.xmin);
		double ySize=(pref.ymax-pref.ymin);
		pref.xmin+=xSize/(e->delta()/4);
		pref.xmax-=xSize/(e->delta()/4);
		
		pref.ymin+=ySize/(e->delta()/4);
		pref.ymax-=ySize/(e->delta()/4);
		oldXMin=pref.xmin;
		oldXMax=pref.xmax;
		glDeleteLists(axes,1);
		axes=drawStdAxes();
		updateFunctions(pref.xmin-3*xSize,pref.xmax-3*xSize);
		repaint();
		emit prefChange(pref);
		
	}

}


void GraphOutput::customEvent(QCustomEvent*ev)
{

	switch(ev->type())
	{
		case SIGTHREADSYNC:
//			qDebug("main process "+QString::number(pthread_self()));
			threadTimerSlot();
			break;
		case SIGPRINT:	
			free(ev->data());
			break;
		case SIGCLEARTEXT:
			break;
		case SIGGETKEY:
		{
			char*strBuf=new char[2];
			strBuf[1]=(char)0;
			strBuf[0]=(char)0;
			threadData->data=strBuf;
			break;
		}
		case SIGKEYSTATE:
		{
			char*strBuf=new char[1];
			strBuf[0]=(char)0;
			threadData->data=strBuf;
			break;
		}
		case SIGGETLINE:
		{
			char*strBuf=new char[2];
			strBuf[1]=(char)0;
			strBuf[0]=(char)0;
			threadData->data=strBuf;
			break;
		}
		case SIGSETTEXTPOS:
			free(ev->data());
			break;
		case SIGFINISHED:		//script stopped
			{
				break;
			}
		case SIGDEBUG:
		{
			free(ev->data());
			break;
		}
		default:
		{
			break;
		}
	}

}

void GraphOutput::processStdFunction(ObjectInfo*obj, int index,ThreadSync*td,Variable*va)
{
  char*func=obj->function;

	double xStart,xStep;
	Number result;
	xStart=pref.xmin;
	xStep=(pref.xmax-pref.xmin)/PRECISION2D;

	QString num,num2;

	struct timeval t1,t2;
	
	double* coordinates=new double[PRECISION2D*2+2];
  obj->objectData[index].coordinates=coordinates;
  obj->objectData[index].coordinateLength=PRECISION2D;
  if(obj->logic)
	{
		Script ca1(NULL,func,&pref,va,td);
		gettimeofday(&t1,NULL);
		td->vars[0][0].type=NFLOAT;
    td->vars[0][0].fval=obj->objectData[index].dynamicParameter;
		for(int c=0; c<PRECISION2D; c++)
		{
			td->vars[23][0].type=NFLOAT;
			td->vars[23][0].fval=xStart+(double)c*xStep;
			coordinates[2*c]  =td->vars[23][0].fval.real();
			result=ca1.exec();
			convertToFloat(&result);
			coordinates[2*c+1]=result.fval.real();
		}
		gettimeofday(&t2,NULL);
	}
	else 
	{
		Calculate ca1(NULL,func,&pref,va);
		gettimeofday(&t1,NULL);
		
    va[0]=obj->objectData[index].dynamicParameter;
		for(int c=0; c<PRECISION2D; c++)
		{
			va[23]=xStart+(double)c*xStep;
			coordinates[2*c]  =va[23];
			coordinates[2*c+1]=ca1.calc();
		}
		gettimeofday(&t2,NULL);
	}

	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	objectInfo[index].processed=true;
}


void GraphOutput::processPolarFunction(ObjectInfo*obj,int index,ThreadSync*threadData,Variable*vars)
{
	char*func;
  func = obj->function;

	double xStart,xStep;
	xStart=0;
	double multiplier=1.0;
	xStep=pref.angleMax/PRECISION2D;
	if(pref.angle==DEG)
	{
		multiplier=PI/180.0;
	}
	else if(pref.angle==GRA)
	{
		multiplier=PI/200.0;
	}

	double* coordinates=new double[PRECISION2D*2+2];
  obj->objectData[index].coordinates=coordinates;
  obj->objectData[index].coordinateLength=PRECISION2D+1;
//	perror("Polar function index: "+QString::number(index));

	float r;
	QString num,num2;
	struct timeval t1,t2;
  if(obj->logic)
	{
		Number r;
		long double x;
		Script ca1(NULL,func,&pref,vars,threadData);
		
		gettimeofday(&t1,NULL);
		
		threadData->vars[0][0].type=NFLOAT;
    threadData->vars[0][0].fval=obj->objectData[index].dynamicParameter;
		for(int c=0; c<=PRECISION2D; c++)
		{
			x=xStart+(double)c*xStep;
			threadData->vars[23][0].type=NFLOAT;
			threadData->vars[23][0].fval=x;

			r=ca1.exec();
			convertToFloat(&r);
      coordinates[2*c]  =cos(x*multiplier)*r.fval.real();
      coordinates[2*c+1]=sin(x*multiplier)*r.fval.real();
			
		}
		gettimeofday(&t2,NULL);
	}
	else {
		Calculate ca1(NULL,func,&pref,vars);
    vars[0]=obj->objectData[index].dynamicParameter;
		gettimeofday(&t1,NULL);
		for(int c=0; c<=PRECISION2D; c++)
		{
			vars[23]=xStart+(double)c*xStep;
			r=ca1.calc();
      coordinates[c*2]=cos(vars[23]*multiplier)*r;
      coordinates[c*2+1]=sin(vars[23]*multiplier)*r;
		}
		gettimeofday(&t2,NULL);
	}

	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	objectInfo[index].processed=true;
}

void GraphOutput::processParameterFunction(ObjectInfo*obj,int index,ThreadSync*threadData,Variable*vars)
{
	char*func1,*func2;
  func1 = obj->function;
  func2 = obj->function2;

	double xStart,xStep;
	xStart=pref.parameterStart;
	xStep=(pref.parameterEnd-pref.parameterStart)/(double)pref.parameterSteps;

	double* coordinates=new double[pref.parameterSteps*2];
  obj->objectData[index].coordinates=coordinates;
  obj->objectData[index].coordinateLength=pref.parameterSteps;

	QString num,num2;
	struct timeval t1,t2;
	
  if(obj->logic)
	{
		Number result;
		Script ca1(NULL,func1,&pref,vars,threadData);
		Script ca2(NULL,func2,&pref,vars,threadData);
		gettimeofday(&t1,NULL);
		
		threadData->vars[0][0].type=NFLOAT;
    threadData->vars[0][0].fval=obj->objectData[index].dynamicParameter;
		
		for(int c=0; c<pref.parameterSteps; c++)
		{
			threadData->vars[19][0].type=NFLOAT;
			threadData->vars[19][0].fval=xStart+(double)c*xStep;
			result=ca1.exec();
			convertToFloat(&result);
      coordinates[2*c]=result.fval.real();
			threadData->vars[19][0].type=NFLOAT;
			threadData->vars[19][0].fval=xStart+(double)c*xStep;
			result=ca2.exec();
			convertToFloat(&result);
      coordinates[2*c+1]=result.fval.real();
		}
	}
	else {
    Calculate ca1(NULL,func1,&pref,vars);
    Calculate ca2(NULL,func2,&pref,vars);
    vars[0]=obj->objectData[index].dynamicParameter;
    gettimeofday(&t1,NULL);
    for(int c=0; c<pref.parameterSteps; c++)
    {
      vars[19]=xStart+(double)c*xStep;
      coordinates[2*c]=ca1.calc();
      coordinates[2*c+1]=ca2.calc();
    }
    gettimeofday(&t2,NULL);
	}

	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	objectInfo[index].processed=true;
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



void GraphOutput::process3dFunction(ObjectInfo*obj,int index,ThreadSync*threadData,Variable*vars)
{


	char*func;
  func = obj->function;


	double xStart,xStep,zStart,zStep;
	xStart=pref.xmin;
	zStart=pref.zmin;
	xStep=(pref.xmax-pref.xmin)/PRECISION3D;
	zStep=(pref.zmax-pref.zmin)/PRECISION3D;


	double*coordinates=new double[PRECISION3D*PRECISION3D];
  obj->objectData[index].coordinates=coordinates;
  obj->objectData[index].coordinateLength=PRECISION3D;

	QString num,num2;
	struct timeval t1,t2;
  if(obj->logic)
	{
		Number result;
		Script ca1(NULL,func,&pref,vars,threadData);
		gettimeofday(&t1,NULL);

		threadData->vars[0][0].type=NFLOAT;
    threadData->vars[0][0].fval=obj->objectData[index].dynamicParameter;

		for(int c=0; c<PRECISION3D; c++)
		{
			threadData->vars[25][0].type=NFLOAT;
			threadData->vars[25][0].fval=zStart+c*zStep;
			for(int c1=0; c1<PRECISION3D; c1++)
			{
				threadData->vars[23][0].type=NFLOAT;
				threadData->vars[23][0].fval=xStart+c1*xStep;
				result=ca1.exec();
				convertToFloat(&result);
				coordinates[PRECISION3D*c+c1]=result.fval.real();
			}
		}
	}
	else {
		Calculate ca1(NULL,func,&pref,vars);
    vars[0]=obj->objectData[index].dynamicParameter;
		gettimeofday(&t1,NULL);
	
		for(int c=0; c<PRECISION3D; c++)
		{
			vars[25]=zStart+c*zStep;
			for(int c1=0; c1<PRECISION3D; c1++)
			{
				vars[23]=xStart+c1*xStep;
				coordinates[PRECISION3D*c+c1]=ca1.calc();
			}
		}
	}

	gettimeofday(&t2,NULL);



	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
	
//	objectInfo[index].processed=true;
}


void GraphOutput::processInequalityFunction(ObjectInfo*obj,int index,ThreadSync*threadData,Variable*vars)
{
	//types:
	//GRAPHIEG: both greather
	//GRAPHIEL: both less
	//GRAPHIEGE: first greather, second less

	char*func,*func2;
  func = obj->function;
  func2= obj->function2;

	double xStart,xStep;
	xStart=pref.xmin;
	xStep=(pref.xmax-pref.xmin)/PRECISION2D;
	double endLine;

  if(obj->type==GRAPHIEGE || obj->type==GRAPHIEG)
		endLine=pref.ymax;
	else endLine=pref.ymin;
	struct timeval t1,t2;

	double* coordinates;
  if(obj->type==GRAPHIEG || obj->type==GRAPHIEL)
		coordinates=new double[PRECISION2D*2+2];
	else coordinates=new double[PRECISION2D*3+3];
  obj->objectData[index].coordinates=coordinates;
  obj->objectData[index].coordinateLength=PRECISION2D+1;

	float x,y1,y2;
	QString num,num2;
	Calculate *ca1=NULL,*ca2=NULL;
	Script*s1=NULL,*s2=NULL;
	Number result;
  if(obj->logic)
	{
		
		threadData->vars[0][0].type=NFLOAT;
    threadData->vars[0][0].fval=obj->objectData[index].dynamicParameter;
		
		s1=new Script(NULL,func,&pref,vars,threadData);	
		s2=new Script(NULL,func2,&pref,vars,threadData);	
	}
	else {
    vars[0]=obj->objectData[index].dynamicParameter;

		ca1=new Calculate(NULL,func,&pref,vars);
		ca2=new Calculate(NULL,func2,&pref,vars);
	}
	for(int c=0; c<=PRECISION2D; c++)
	{
		x=xStart+(double)c*xStep;

    if(obj->logic)
		{
			threadData->vars[23][0].type=NFLOAT;
			threadData->vars[23][0].fval=x;
			result=s1->exec();
			y1=result.fval.real();
			threadData->vars[23][0].type=NFLOAT;
			threadData->vars[23][0].fval=x;
			result=s2->exec();
			y2=result.fval.real();
		}
		else {
			vars[23]=x;
			y1=ca1->calc();
			y2=ca2->calc();
		}
    if(obj->type==GRAPHIEG)
		{
      coordinates[2*c]=x;
			if(y1>=y2)
        coordinates[2*c+1]=y1;
      else coordinates[2*c+1]=y2;
		}
    else if(obj->type==GRAPHIEL)
		{
      coordinates[2*c]=x;
			if(y1<=y2)
        coordinates[2*c+1]=y1;
      else coordinates[2*c+1]=y2;
		}
		else
		{
			if(y1<=y2)
			{
        coordinates[3*c]=x;
        coordinates[3*c+1]=y1;
        coordinates[3*c+2]=y2;
			}
      else coordinates[3*c+1]=coordinates[3*c+2]=0.0;
		}
	}


	
	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}

  if(obj->logic)
	{
		delete s1;
		delete s2;	
	}
	else {
		delete ca1;
		delete ca2;
	}
}

void GraphOutput::processComplexFunction(ObjectInfo*obj,int index,ThreadSync*threadData,Variable*vars)
{
	char*func;
  func = obj->function;

	double zStart,zStep;
	double* coordinates;
  if(obj->type==GRAPHCOMP3D)
	{
		zStart=pref.zmin;
		coordinates=new double[pref.nyquistSteps*3+3];
		zStep=(pref.zmax-pref.zmin)/(double)pref.nyquistSteps;
	}
	else {
		zStart=pref.nyquistStart;
		coordinates=new double[pref.nyquistSteps*2+2];
		zStep=(pref.nyquistEnd-pref.nyquistStart)/(double)pref.nyquistSteps;
	}

	QString num,num2;
	bool oldcpref=pref.complex;
	pref.complex=true;
	Script ca1(NULL,func,&pref,vars,threadData);
	pref.complex=oldcpref;
	struct timeval t1,t2;
	Number result;

  obj->objectData[index].coordinates=coordinates;
  obj->objectData[index].coordinateLength=pref.nyquistSteps;

	
	threadData->vars[0][0].type=NFLOAT;
  threadData->vars[0][0].fval=obj->objectData[index].dynamicParameter;
	
	gettimeofday(&t1,NULL);
	threadData->vars[25][0].type=NFLOAT;
  if(obj->type==GRAPHCOMP3D)
	{
		for(int c=0; c<=pref.nyquistSteps; c++)
		{
			threadData->vars[25][0].fval=Complex(zStart+(double)c*zStep,0.0);
			result=ca1.exec();
      coordinates[3*c+2]  =threadData->vars[25][0].fval.real();
      coordinates[3*c]=result.fval.real();
      coordinates[3*c+1]=result.fval.imag();
		}
	}
	else {
		for(int c=0; c<=pref.nyquistSteps; c++)
		{
			if(pref.logNyquistSteps)
				threadData->vars[25][0].fval=Complex(pow(10,zStart+(double)c*zStep),0.0);
			else threadData->vars[25][0].fval=Complex(zStart+(double)c*zStep,0.0);
			result=ca1.exec();
      coordinates[2*c]=result.fval.real();
      coordinates[2*c+1]=result.fval.imag();
		}
	}

	gettimeofday(&t2,NULL);

	int seconds,usecs;
	seconds=t2.tv_sec-t1.tv_sec;
	usecs=t2.tv_usec-t1.tv_usec;
	if(seconds > 0 && usecs < 0)
	{
		seconds--;
		usecs=1000000+usecs;
	}
//	objectInfo[index].processed=true;
}


///////////////////////////////////////////paintGL///////////////////////////////////////////

void GraphOutput::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    QListIterator<ObjectInfo*>i(objectInfo);
    ObjectInfo*obj;

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	if(graphProcess)
	{
		qglColor(QColor(100,100,100));
		QFont waitFont("Helvetica");
		QString text=tr("Processing ...");
		waitFont.setPixelSize(16);
		QFontMetrics f(waitFont);
		
		int x=(width()-f.width(text))/2;
		renderText(x,height()/2,text,waitFont);
		return;
	}
	
	if(pref.graphType==GRAPH3D)
	{
		glFrustum(-10.0,10.0,-10.0,10.0,1.0,100.0);
		glScalef(1.0,1.0,-0.05);
		glTranslatef(0.0,0.0,37.0+(float)zMove);
		glRotatef(xRotation,0.0f,1.0f,0.0f);
		glRotatef(yRotation,1.0f,0.0f,0.0f);	
		glScalef(20.0/(pref.xmax-pref.xmin),20.0/(pref.ymax-pref.ymin),20.0/(pref.zmax-pref.zmin));
		glTranslatef(((pref.xmax-pref.xmin)/2+pref.xmin)*-1,((pref.ymax-pref.ymin)/2+pref.ymin)*-1,((pref.zmax-pref.zmin)/2+pref.zmin)*-1);

	}
	else 
	{
	//	double xSize=pref.xmax-pref.xmin,ySize=pref.ymax-pref.ymin;
		glFrustum(-10.0,10.0,-10.0,10.0,1.0,100.0);
		glTranslatef(0.0,0.0,-1.0);
		
	//	glScalef(20.0/xSize,20.0/ySize,1.0f);
	//	glTranslatef((pref.xmin+pref.xmax)*-0.5f,(pref.ymin+pref.ymax)*-0.5,0.0f);
	}

	glCallList(axes);
//	for(int c=0; c<objects.GetLen(); c++)
//		glCallList(objects[c]);

//	perror("\n");
//	for(int c=0; c<drawRules.GetLen(); c++)
//		for(int c1=0; c1<drawRules[c][0]; c1++)
//			perror("DrawRules: "+QString::number(c)+" indices: "+QString::number(drawRules[c][c1+1]));
//	perror("\n");
  while(i.hasNext())
	{
    obj=i.next();
    if(dynamicPos<obj->dataLength)
		{
      if(obj->objectData[dynamicPos].glCreated)
        glCallList(obj->objectData[dynamicPos].glObject);
      else qDebug("No GL list");
		}
		else {
      if(obj->objectData[0].glCreated)
        glCallList(obj->objectData[0].glObject);
      else qDebug("No GL list");
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
		double zTrans=(pref.zmax-pref.zmin)/80;
		double staticZ=zTrans;
		if(pref.zmax < zTrans)
			staticZ=pref.zmax-3*zTrans;
		else if(pref.zmin > -zTrans)
			staticZ=pref.zmin+zTrans;
				
			
		if(pref.xmax < xTrans)
			staticX=pref.xmax-3*xTrans;
		else if(pref.xmin > -xTrans)
			staticX=pref.xmin+xTrans;
		if(pref.ymax < yTrans)
			staticY=pref.ymax-3*yTrans;
		else if(pref.ymin > -yTrans)
			staticY=pref.ymin+yTrans;
		if(pref.graphType!=GRAPH3D)
			staticZ=0.0;
				
		qglColor( QColor(220,220,220) );
		
		for(float c=pref.xmin-fmod(pref.xmin,pref.rasterSizeX)+pref.rasterSizeX; c<pref.xmax; c+=pref.rasterSizeX)
			renderText(c-xTrans,staticY,staticZ,QString::number(c,'g',3),stdFont);
		for(float c=pref.ymin-fmod(pref.ymin,pref.rasterSizeY)+pref.rasterSizeY; c<pref.ymax; c+=pref.rasterSizeY)
			renderText(staticX,c-yTrans,staticZ,QString::number(c,'g',3),stdFont);
		
/*		for(float c=0; c<pref.xmax; c+=pref.rasterSizeX)
			renderText(c-xTrans,staticY,0.0f,QString::number(c,'g',3),stdFont);
		for(float c=0; c>pref.xmin; c-=pref.rasterSizeX)
			renderText(c-xTrans,staticY,0.0f,QString::number(c,'g',3),stdFont);
		
		for(float c=0; c<pref.ymax; c+=pref.rasterSizeY)
			renderText(staticX,c-yTrans,0.0f,QString::number(c,'g',3),stdFont);
		for(float c=0; c>pref.ymin; c-=pref.rasterSizeY)
			renderText(staticX,c-yTrans,0.0f,QString::number(c,'g',3),stdFont);
*/
				
		if(pref.graphType == GRAPH3D)
		{

				staticZ=pref.zmin+zTrans;
			for(float c=pref.zmin-fmod(pref.zmin,pref.rasterSizeZ)+pref.rasterSizeZ; c<pref.zmax; c+=pref.rasterSizeZ)
				renderText(staticX,staticY,c-zTrans,QString::number(c,'g',3),stdFont);
/*			for(float c=0; c<pref.zmax; c+=pref.rasterSizeZ)
				renderText(staticX,staticY,c-zTrans,QString::number(c,'g',3),stdFont);
			for(float c=0; c>pref.zmin; c-=pref.rasterSizeZ)
				renderText(staticX,staticY,c-zTrans,QString::number(c,'g',3),stdFont);	
*/			
			
		}
	}
	
	

	if(drawState!=DRAWNONE)
	{
		if(texture==0xffffffff)
			return;
		
		if(pref.graphType==GRAPH3D)
		{
			double xSize=pref.xmax-pref.xmin,ySize=pref.ymax-pref.ymin;

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glScalef(20.0/xSize,20.0/ySize,1.0f);
			glTranslatef((pref.xmin+pref.xmax)*-0.5f,(pref.ymin+pref.ymax)*-0.5,0.0f);
		//	glDisable(GL_DEPTH_TEST);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum(-10.0,10.0,-10.0,10.0,1.0,100.0);
			glTranslatef(0.0,0.0,-1.0);



			
		}
		
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_QUADS);
		glColor4f(1.0,1.0,1.0,1.0);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(pref.xmin, pref.ymin, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(pref.xmax, pref.ymin,0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(pref.xmax, pref.ymax, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(pref.xmin,pref.ymax, 0.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
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
  int c;

	if(graphProcess)
		return;
	
	current3dSteps=pref.prec3dSteps;
	current2dSteps=pref.prec2dSteps;

  while (!objectInfo.isEmpty())
  {
    for(c=0; c<objectInfo.first()->dataLength; c++)
    {
      delete[] objectInfo.first()->objectData[c].coordinates;
      if(objectInfo.first()->objectData[c].glCreated)
        glDeleteLists(objectInfo.first()->objectData[c].glObject,1);
      else qDebug("data for removal not consistent");
    }
    delete[] objectInfo.first()->objectData;
    delete objectInfo.takeFirst();
  }

	isDynamic=false;
	timer->stop();

}

void GraphOutput::setPref(Preferences newPref)
{
	pref=newPref;
	if(pref.solvePrec!=currentSolvePrec)
	{
		delete drawImage;
		delete drawMap;
		delete[] backMap;
		drawImage=new QImage(TEXTURESIZE,TEXTURESIZE,32);
		drawImage->fill(0x00000000);
		drawImage->setAlphaBuffer(true);
		drawMap=new QPixmap(*drawImage);
		backCursor=0;
		backMap=new QPixmap*[BACKSTEPS];
		for(int c=0; c<BACKSTEPS; c++)
			backMap[c]=NULL;
		
	}
	currentSolvePrec=pref.solvePrec;
	oldXMin=pref.xmin;
	oldXMax=pref.xmax;
	if(!drawScreenshot)
		initializeGL();
}

bool GraphOutput::updateFunctions(double oldXMin,double oldXMax)
{
  QListIterator<ObjectInfo*>i(objectInfo);
  ObjectInfo*obj;
  int c;

	if(graphProcess)
		return false;
	
	bool shiftRight;
	double xStart,xStep;
	int steps,startStep;
	bool ret=true;
	makeCurrent();

	if(pref.xmin>oldXMin)
	{
		shiftRight=true;
		xStart=oldXMax;
		xStep=(pref.xmax-pref.xmin)/PRECISION2D;
		steps=(int)((pref.xmax-oldXMax+xStep/2)/xStep);
		if(steps>PRECISION2D)
		{
			steps=PRECISION2D;
			xStart=pref.xmin;
		}
		startStep=PRECISION2D-steps;
	}
	else 
	{
		shiftRight=false;
		xStart=pref.xmin;
		xStep=(pref.xmax-pref.xmin)/PRECISION2D;
		steps=(int)((oldXMin-pref.xmin+xStep/2)/xStep);
		if(steps>PRECISION2D)
			steps=PRECISION2D;
		startStep=0;
	}
	if(steps <= 0)
		ret=false;



  while(i.hasNext())
	{
    obj=i.next();

		if(!ret);
    else if(obj->type == GRAPHSTD)
		{
      for(c=0; c<obj->dataLength; c++)
      {
        if(obj->logic)
        {
          threadData->vars[0][0].type=NFLOAT;
          threadData->vars[0][0].fval=Complex(obj->objectData[c].dynamicParameter,0.0);
        }
        else vars[0]=obj->objectData[c].dynamicParameter;

        if(shiftRight)
          for(int c1=steps*2; c1<PRECISION2D*2; c1++)
            obj->objectData[c].coordinates[c1-steps*2]=obj->objectData[c].coordinates[c1];
        else for(int c1=(PRECISION2D)*2+1; c1>=steps*2; c1--)
              obj->objectData[c].coordinates[c1]=obj->objectData[c].coordinates[c1-steps*2];
        if(obj->logic)
        {
          Number result;
          Script ca(NULL,obj->function,&pref,vars,threadData);
          for(int c1=0; c1<steps; c1++)
          {
            threadData->vars[23][0].type=NFLOAT;
            threadData->vars[23][0].fval=xStart+c1*xStep;
            obj->objectData[c].coordinates[(startStep+c1)*2]  =threadData->vars[23][0].fval.real();
            result=ca.exec();
            convertToFloat(&result);
            obj->objectData[c].coordinates[(startStep+c1)*2+1]=result.fval.real();
          }
        }
        else {
          Calculate ca(NULL,obj->function,&pref,vars);
          for(int c1=0; c1<steps; c1++)
          {
            vars[23]=xStart+c1*xStep;
            obj->objectData[c].coordinates[(startStep+c1)*2]=vars[23];
            obj->objectData[c].coordinates[(startStep+c1)*2+1]=ca.calc();
          }
        }
      }
		}
    else if(obj->type == GRAPHIEG || obj->type == GRAPHIEL || obj->type == GRAPHIEGE || obj->type == GRAPHIELE)
		{
//			perror("xStart: "+QString::number(xStart)+" xStep: "+QString::number(xStep)+" shiftRight: "+QString::number(shiftRight)+" function: "+QString(objectInfo[c].function)); 

			Calculate *ca1=NULL,*ca2=NULL;
			Script*s1=NULL,*s2=NULL;
			Number result;

      for(c=0; c<obj->dataLength; c++)
      {
        if(obj->logic)
        {
          threadData->vars[0][0].type=NFLOAT;
          threadData->vars[0][0].fval=Complex(obj->objectData[c].dynamicParameter,0.0);
        }
        else vars[0]=obj->objectData[c].dynamicParameter;
        if(obj->logic)
        {
          s1=new Script(NULL,obj->function,&pref,vars,threadData);
          s2=new Script(NULL,obj->function2,&pref,vars,threadData);
        }
        else {
          ca1=new Calculate(NULL,obj->function,&pref,vars);
          ca2=new Calculate(NULL,obj->function2,&pref,vars);
        }

        if(obj->type == GRAPHIEG || obj->type == GRAPHIEL)
        {
        if(shiftRight)
          for(int c1=steps*2; c1<PRECISION2D*2+2; c1++)
            obj->objectData[c].coordinates[c1-steps*2]=obj->objectData[c].coordinates[c1];
        else for(int c1=(PRECISION2D+1)*2-1; c1>=0; c1--)
              obj->objectData[c].coordinates[c1]=obj->objectData[c].coordinates[c1-steps*2];
        }
        else {
          if(shiftRight)
            for(int c1=steps*3; c1<PRECISION2D*3+3; c1++)
              obj->objectData[c].coordinates[c1-steps*3]=obj->objectData[c].coordinates[c1];
          else for(int c1=(PRECISION2D+1)*3-1; c1>=0; c1--)
                obj->objectData[c].coordinates[c1]=obj->objectData[c].coordinates[c1-steps*3];
        }

        double x, y1, y2;
        if(shiftRight)
          steps++;
  //			perror("full length: "+QString::number(steps+startStep));
        for(int c1=0; c1<steps; c1++)
        {
          x=xStart+(double)c1*xStep;
          if(obj->logic)
          {
            threadData->vars[23][0].type=NFLOAT;
            threadData->vars[23][0].fval=x;
            result=s1->exec();
            y1=result.fval.real();
            threadData->vars[23][0].type=NFLOAT;
            threadData->vars[23][0].fval=x;
            result=s2->exec();
            y2=result.fval.real();
          }
          else {
            vars[23]=x;
            y1=ca1->calc();
            y2=ca2->calc();
          }

          if(obj->type==GRAPHIEG)
          {
            obj->objectData[c].coordinates[2*(startStep+c1)]=x;
            if(y1>=y2)
              obj->objectData[c].coordinates[2*(startStep+c1)+1]=y1;
            else obj->objectData[c].coordinates[2*(startStep+c1)+1]=y2;
          }
          else if(obj->type==GRAPHIEL)
          {
            obj->objectData[c].coordinates[2*(startStep+c1)]=x;
            if(y1<=y2)
              obj->objectData[c].coordinates[2*(startStep+c1)+1]=y1;
            else obj->objectData[c].coordinates[2*(startStep+c1)+1]=y2;
          }
          else
          {
            if(y1<=y2)
            {
              obj->objectData[c].coordinates[3*(startStep+c1)]=x;
              obj->objectData[c].coordinates[3*(startStep+c1)+1]=y1;
              obj->objectData[c].coordinates[3*(startStep+c1)+2]=y2;
            }
            else obj->objectData[c].coordinates[3*(startStep+c1)+1]=obj->objectData[c].coordinates[3*(startStep+c1)+2]=0.0;
          }
        }
        if(obj->logic)
        {
          delete s1;
          delete s2;
        }
        else {
          delete ca1;
          delete ca2;
        }
        if(shiftRight)
          steps--;
      }
    }
    else if(obj->type!=GRAPH3D)
    {
      for(c=0; c<obj->dataLength; c++)
      {
        glDeleteLists(obj->objectData[c].glObject,1);
        obj->objectData[c].glObject=generateGLList(obj,c);
      }
    }

	}
	
	return ret;
}

void GraphOutput::processFunction(QString function,QString function2, int type, QColor color, bool logic, bool dynamic)
{

	if(graphProcess)
		return;
	
	if((type==GRAPH3D || type==GRAPHCOMP3D) && pref.graphType!=GRAPH3D)
		return;


  ObjectInfo *info=new ObjectInfo;;
  info->type=type;
  info->color=color;
  info->dynamic=dynamic;
  info->logic=logic;

	if(type==GRAPHPARAMETER)
	{
		int sep=function.find("\\");
		QString f1=function.left(sep);
		QString f2=function.right(function.length()-sep-1);
    info->function=preprocessor(&f1,&pref,false);
    info->function2=preprocessor(&f2,&pref,false);
	}
	else if(type==GRAPHIEGE)
	{
    info->function=preprocessor(&function,&pref,false);
    info->function2=preprocessor(&function2,&pref,false);
	}
	else if(type==GRAPHIELE)
	{
    info->function=preprocessor(&function2,&pref,false);
    info->function2=preprocessor(&function,&pref,false);
	}
	else if(type==GRAPHIEL || type==GRAPHIEG)
	{
    info->function=preprocessor(&function,&pref,false);
		if(function2.length()<=0)
      info->function2=preprocessor(&function,&pref,false);
    else info->function2=preprocessor(&function2,&pref,false);
	}
	else
	{
    info->function=preprocessor(&function,&pref,false);
    info->function2=NULL;
  }

	if(dynamic)
  {
    info->dataLength=pref.dynamicSteps;
    if(pref.dynamicDelay>0)
      timer->start(pref.dynamicDelay*10,false);
    isDynamic=true;
  }
  else info->dataLength=1;

  info->objectData=new ObjectData[info->dataLength];

  for(int c=0; c<info->dataLength; c++)
  {
    info->objectData[c].dynamicParameter=pref.dynamicStart+c*((pref.dynamicEnd-pref.dynamicStart)/(pref.dynamicSteps-1));
    info->objectData[c].processed=info->objectData[c].glCreated=false;
    info->objectData[c].coordinateLength=0;
    info->objectData[c].coordinates=NULL;
  }
  objectInfo.append(info);
}

inline void GraphOutput::drawTriangle(float x[3],float y[3],float z[3],bool colored)
{
	int c;
	if(y[0]>pref.ymin && y[0]<pref.ymax &&		//all vertex inside c s
		   y[1]>pref.ymin && y[1]<pref.ymax &&
		   y[2]>pref.ymin && y[2]<pref.ymax)
	{
		for(c=0; c<3; c++)
		{
			if(colored)
				setGLColor(y[c]);
			glVertex3f(x[c],y[c],z[c]);
		}
	}
	if((y[0]>pref.ymax || y[1]>pref.ymax || y[2]>pref.ymax) &&	//one vertex over maximum, one below minimum
		   (y[0]<pref.ymin || y[1]<pref.ymin || y[2]<pref.ymin))
	{
		return;
	}
  else if(((y[0]>pref.ymin && y[0]<pref.ymax) ||		//at least one vertex inside, at least one outside c s
        (y[1]>pref.ymin && y[1]<pref.ymax) ||
        (y[2]>pref.ymin && y[2]<pref.ymax)) &&
				(y[0]<pref.ymin || y[0]>pref.ymax ||
				y[1]<pref.ymin || y[1]>pref.ymax ||
				y[2]<pref.ymin || y[2]>pref.ymax))
	{
		int vout[2],vin[2],outcount=0;
		for(int c=0; c<3; c++)
		{
			if(y[c]>pref.ymax || y[c]<pref.ymin)
			{
				vout[outcount]=c;
				outcount++;
			}
			else vin[c-outcount]=c;
		}
		
		double tmpx[2],tmpy[2],tmpz[2],fakt,ygr;
		if(y[vout[0]]>pref.ymax)
			ygr=pref.ymax;
		else ygr=pref.ymin;
		
		if(outcount==1)
		{

			
			for(int c=0; c<2; c++)
			{
				fakt=(ygr-y[vin[c]])/(y[vout[0]]-y[vin[c]]);
				
				tmpx[c]=x[vin[c]]+(x[vout[0]]-x[vin[c]])*fakt;
				tmpz[c]=z[vin[c]]+(z[vout[0]]-z[vin[c]])*fakt;
				tmpy[c]=ygr;
			}
			if(colored)
				setGLColor(y[vin[0]]);
			glVertex3f(x[vin[0]],y[vin[0]],z[vin[0]]);
			if(colored)
				setGLColor(y[vin[1]]);
			glVertex3f(x[vin[1]],y[vin[1]],z[vin[1]]);
			if(colored)
				setGLColor(tmpy[0]);
			glVertex3f(tmpx[0],tmpy[0],tmpz[0]);

			if(colored)
				setGLColor(tmpy[0]);
			glVertex3f(tmpx[0],tmpy[0],tmpz[0]);
			if(colored)
				setGLColor(tmpy[1]);
			glVertex3f(tmpx[1],tmpy[1],tmpz[1]);
			if(colored)
				setGLColor(y[vin[1]]);
			glVertex3f(x[vin[1]],y[vin[1]],z[vin[1]]);
		}
		else
		{
			for(int c=0; c<2; c++)
			{
				fakt=(ygr-y[vin[0]])/(y[vout[c]]-y[vin[0]]);
				
				tmpx[c]=x[vin[0]]+(x[vout[c]]-x[vin[0]])*fakt;
				tmpz[c]=z[vin[0]]+(z[vout[c]]-z[vin[0]])*fakt;
				tmpy[c]=ygr;
			}

			if(colored)
				setGLColor(tmpy[0]);
			glVertex3f(tmpx[0],tmpy[0],tmpz[0]);
			if(colored)
				setGLColor(tmpy[1]);
			glVertex3f(tmpx[1],tmpy[1],tmpz[1]);
			if(colored)
				setGLColor(y[vin[0]]);
			glVertex3f(x[vin[0]],y[vin[0]],z[vin[0]]);
		}
	}
}

void GraphOutput::createGLLists()
{
  QListIterator<ObjectInfo*>i(objectInfo);
  ObjectInfo*obj;
  int c;

	if(graphProcess)
		return;
	
	makeCurrent();

  while(i.hasNext())
	{
    obj=i.next();
    for(c=0; c<obj->dataLength; c++)
    {
      if(obj->objectData[c].processed &&!obj->objectData[c].glCreated)
      {
        obj->objectData[c].glCreated=true;
        obj->objectData[c].glObject=generateGLList(obj,c);
      }
    }
	}
}

void GraphOutput::calculateGraphData()
{
  QListIterator<ObjectInfo*>i(objectInfo);
  ObjectInfo*obj;
  int c;

	graphProcess=true;
	int threadCount=0;
  while(i.hasNext())
  {
    obj=i.next();
    for(c=0; c<obj->dataLength; c++)
    {
      if(obj->objectData[c].processed)
      {
        obj->objectData[c].processed=true;
        threads[threadCount]->setObjectData(obj,c);
        threads[threadCount]->start();
        threadCount++;
        if(threadCount>=THREADS)
          break;
      }
    }
  }
	threadTimer->start(10);
	repaint();
}

void GraphOutput::processGraph(ObjectInfo*o,int c,ThreadSync*td,Variable*va)
{
   qDebug("Graph processed: "+QString(o->function)+" dynamic index: "+QString::number(c));

    switch(o->type)
		{
			case GRAPHSTD:
        processStdFunction(o,c,td,va);
				break;
			case GRAPHPOLAR:
        processPolarFunction(o,c,td,va);
				break;
			case GRAPHIEG:
			case GRAPHIEL:
			case GRAPHIEGE:
			case GRAPHIELE:
        processInequalityFunction(o,c,td,va);
				break;
			case GRAPH3D:
        process3dFunction(o,c,td,va);
				break;
			case GRAPHPARAMETER:
        processParameterFunction(o,c,td,va);
				break;
			case GRAPHCOMPLEX:
			case GRAPHCOMP3D:
        processComplexFunction(o,c,td,va);
				break;
		}
//	}
}

GLuint GraphOutput::generateGLList(ObjectInfo*obj,int index)
{

	
	GLuint list;

	list = glGenLists(1);
	glNewList( list, GL_COMPILE );

	double oldx=0.0,oldy=0.0;
	int colored=0;
	float height=pref.ymax-pref.ymin;
	middle=pref.ymin+height/2.0;		//calculate middle height for colors
	lowerMiddle=-height/4.0;
	upperMiddle=height/4.0;

  if(obj->color==QColor(1,1,1))
		colored=1;
  else qglColor( obj->color );

  if(obj->type==GRAPH3D)
	{

		double xStart=pref.xmin,xStep=(pref.xmax-pref.xmin)/PRECISION3D;
		double zStart=pref.zmin,zStep=(pref.zmax-pref.zmin)/PRECISION3D;
		double z=0.0,y=0.0,x=0.0,lastY;

    if(obj->objectData[index].processed)
		{
			glMatrixMode(GL_MODELVIEW);
			if(!pref.show3dGrid)
			{
				double z2,x2;
				float xc[3],yc[3],zc[3];
				glBegin(GL_TRIANGLES);
				for(int c=1; c<PRECISION3D; c++)			//Z
				{
					z=zStart+c*zStep;
					z2=zStart+(c-1)*zStep;
					for(int c1=1; c1<PRECISION3D; c1++)		//X
					{
						x=xStart+c1*xStep;
						x2=xStart+(c1-1)*xStep;
						xc[0]=x2;
						xc[1]=x2;
						xc[2]=x;
						
            yc[0]=obj->objectData[index].coordinates[(c-1)*PRECISION3D+c1-1];
            yc[1]=obj->objectData[index].coordinates[c*PRECISION3D+c1-1];
            yc[2]=obj->objectData[index].coordinates[(c-1)*PRECISION3D+c1];
						
						zc[0]=z2;
						zc[1]=z;
						zc[2]=z2;
						drawTriangle(xc,yc,zc,colored);

						xc[0]=x2;
						xc[1]=x;
						xc[2]=x;
						
            yc[0]=obj->objectData[index].coordinates[c*PRECISION3D+c1-1];
            yc[1]=obj->objectData[index].coordinates[c*PRECISION3D+c1];
            yc[2]=obj->objectData[index].coordinates[(c-1)*PRECISION3D+c1];
						
						zc[0]=z;
						zc[1]=z;
						zc[2]=z2;
						drawTriangle(xc,yc,zc,colored);
					}
					
				}
				glEnd();
			}
			else 
			{
				for(int c=0; c<PRECISION3D; c++)
				{
					z=zStart+c*zStep;
					glBegin(GL_LINES);
          lastY=obj->objectData[index].coordinates[c*PRECISION3D];
					for(int c1=1; c1<PRECISION3D; c1++)
					{
						x=xStart+c1*xStep;
            y=obj->objectData[index].coordinates[c*PRECISION3D+c1];
						
						if((y > pref.ymin&&y<pref.ymax) || (lastY > pref.ymin && lastY < pref.ymax))
						{
							double newXStep=xStep,oldXStep=0.0,newY=y,oldY=lastY;
							if(y<pref.ymin && lastY>pref.ymin)
							{
								newY=pref.ymin;
								newXStep=xStep*(oldY-pref.ymin)/(oldY-y);
							}
							else if(y>pref.ymax && lastY<pref.ymax)
							{
								newY=pref.ymax;
								newXStep=xStep*(pref.ymax-oldY)/(y-oldY);
							}
							else if(y>pref.ymin && lastY<pref.ymin)
							{
								oldY=pref.ymin;
								oldXStep=xStep*(pref.ymin-oldY)/(y-oldY);
							}
							else if(y<pref.ymax && lastY>pref.ymax)
							{
								oldY=pref.ymax;
								oldXStep=xStep*(oldY-pref.ymax)/(oldY-y);
							}
							oldXStep+=xStep*(c1-1)+xStart;
							newXStep+=xStep*(c1-1)+xStart;
							if(colored)
								setGLColor(oldY);
							glVertex3f(oldXStep,oldY,z);
							if(colored)
								setGLColor(newY);
							glVertex3f(newXStep,newY,z);
						}
						lastY=y;
					}
					glEnd();
				}
				for(int c=0; c<PRECISION3D; c++)
				{
					x=xStart+c*xStep;
					glBegin(GL_LINES);
          lastY=obj->objectData[index].coordinates[c];
					for(int c1=1; c1<PRECISION3D; c1++)
					{
						z=zStart+c1*zStep;
            y=obj->objectData[index].coordinates[c1*PRECISION3D+c];
						
						if((y > pref.ymin&&y<pref.ymax) || (lastY > pref.ymin && lastY < pref.ymax))
						{
							double newZStep=zStep,oldZStep=0.0,newY=y,oldY=lastY;
							if(y<pref.ymin && lastY>pref.ymin)
							{
								newY=pref.ymin;
								newZStep=zStep*(oldY-pref.ymin)/(oldY-y);
							}
							else if(y>pref.ymax && lastY<pref.ymax)
							{
								newY=pref.ymax;
								newZStep=zStep*(pref.ymax-oldY)/(y-oldY);
							}
							else if(y>pref.ymin && lastY<pref.ymin)
							{
								oldY=pref.ymin;
								oldZStep=zStep*(pref.ymin-oldY)/(y-oldY);
							}
							else if(y<pref.ymax && lastY>pref.ymax)
							{
								oldY=pref.ymax;
								oldZStep=zStep*(oldY-pref.ymax)/(oldY-y);
							}
							oldZStep+=zStep*(c1-1)+zStart;
							newZStep+=zStep*(c1-1)+zStart;
							if(colored)
								setGLColor(oldY);
							glVertex3f(x,oldY,oldZStep);
							if(colored)
								setGLColor(newY);
							glVertex3f(x,newY,newZStep);
						}
						lastY=y;
					}
					glEnd();
				}
			}
      delete[] obj->objectData[index].coordinates;
      obj->objectData[index].coordinates=NULL;
      obj->objectData[index].coordinateLength=0;
      obj->objectData[index].processed=false;
		}
		glEndList();
	}
  else if(obj->type==GRAPHCOMP3D)
	{
		int colored=0;

		double x,y,z;
		bool end=true;
	
		glMatrixMode(GL_MODELVIEW);

    for(int c=0; c<obj->objectData[index].coordinateLength; c++)
		{
      z=obj->objectData[index].coordinates[c*3+2];
      x=obj->objectData[index].coordinates[c*3];
      y=obj->objectData[index].coordinates[c*3+1];
			
			if(!end)
			{
				if(x>pref.xmax)
				{
          double fakt=(pref.xmax-obj->objectData[index].coordinates[(c-1)*3])/(x-obj->objectData[index].coordinates[(c-1)*3]);
					x=pref.xmax;
          y=obj->objectData[index].coordinates[(c-1)*3+1]+(y-obj->objectData[index].coordinates[(c-1)*3+1])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
					end=true;
				}
				else if(x<pref.xmin)
				{
          double fakt=(pref.xmin-obj->objectData[index].coordinates[(c-1)*3])/(x-obj->objectData[index].coordinates[(c-1)*3]);
					x=pref.xmin;
          y=obj->objectData[index].coordinates[(c-1)*3+1]+(y-obj->objectData[index].coordinates[(c-1)*3+1])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
					end=true;
				}
				if(y>pref.ymax)
				{
          double fakt=(pref.ymax-obj->objectData[index].coordinates[(c-1)*3+1])/(y-obj->objectData[index].coordinates[(c-1)*3+1]);
					y=pref.ymax;
          x=obj->objectData[index].coordinates[(c-1)*3]+(x-obj->objectData[index].coordinates[(c-1)*3])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
					end=true;
				}
				else if(y<pref.ymin)
				{
          double fakt=(pref.ymin-obj->objectData[index].coordinates[(c-1)*3+1])/(y-obj->objectData[index].coordinates[(c-1)*3+1]);
					y=pref.ymin;
          x=obj->objectData[index].coordinates[(c-1)*3]+(x-obj->objectData[index].coordinates[(c-1)*3])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
					end=true;
				}
				if(colored)
					setGLColor(y);

				glVertex3f(x,y,z);
				
				if(end)
					glEnd();
			}
			else if(x>pref.xmin && x<pref.xmax && y>pref.ymin && y<pref.ymax)
			{
				glBegin(GL_LINE_STRIP);
				end=false;
				double tmpX=x,tmpY=y,tmpZ=z;
				if(x>pref.xmax)
				{
          double fakt=(pref.xmax-obj->objectData[index].coordinates[(c-1)*3])/(x-obj->objectData[index].coordinates[(c-1)*3]);
					x=pref.xmax;
          y=obj->objectData[index].coordinates[(c-1)*3+1]+(y-obj->objectData[index].coordinates[(c-1)*3+1])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
				}
				else if(x<pref.xmin)
				{
          double fakt=(pref.xmin-obj->objectData[index].coordinates[(c-1)*3])/(x-obj->objectData[index].coordinates[(c-1)*3]);
					x=pref.xmin;
          y=obj->objectData[index].coordinates[(c-1)*3+1]+(y-obj->objectData[index].coordinates[(c-1)*3+1])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
				}
				if(y>pref.ymax)
				{
          double fakt=(pref.ymax-obj->objectData[index].coordinates[(c-1)*3+1])/(y-obj->objectData[index].coordinates[(c-1)*3+1]);
					y=pref.ymax;
          x=obj->objectData[index].coordinates[(c-1)*3]+(x-obj->objectData[index].coordinates[(c-1)*3])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
				}
				else if(y<pref.ymin)
				{
          double fakt=(pref.ymin-obj->objectData[index].coordinates[(c-1)*3+1])/(y-obj->objectData[index].coordinates[(c-1)*3+1]);
					y=pref.ymin;
          x=obj->objectData[index].coordinates[(c-1)*3]+(x-obj->objectData[index].coordinates[(c-1)*3])*fakt;
          z=obj->objectData[index].coordinates[(c-1)*3+2]+(z-obj->objectData[index].coordinates[(c-1)*3+2])*fakt;
				}
				if(colored)
					setGLColor(y);
				glVertex3f(x,y,z);
				if(colored)
					setGLColor(tmpY);
				glVertex3f(tmpX,tmpY,tmpZ);
			}
		}
		
		if(!end)
			glEnd();
		glEndList();
	}
  else if(obj->type==GRAPHIEG ||obj->type==GRAPHIEL ||
         obj->type==GRAPHIEGE ||obj->type==GRAPHIELE)
	{
		bool end=true;
		double x,y1=0.0,y2=0.0;
    if(obj->type==GRAPHIEG)
			y1=pref.ymax;
    else if(obj->type==GRAPHIEL)
			y2=pref.ymin;
    for(int c=0; c<obj->objectData[index].coordinateLength; c++)
		{
      if(obj->type==GRAPHIEG)
			{
        x=obj->objectData[index].coordinates[c*2];
        y2=obj->objectData[index].coordinates[c*2+1];
				if(y2>pref.ymax)
					y2=pref.ymax;
				else if(y2<pref.ymin)
					y2=pref.ymin;
				if(colored)
					setGLColor(y2);
			}
      else if(obj->type==GRAPHIEL)
			{
        x=obj->objectData[index].coordinates[c*2];
        y1=obj->objectData[index].coordinates[c*2+1];
				if(y1<pref.ymin)
					y1=pref.ymin;
				else if(y1>pref.ymax)
					y1=pref.ymax;
				if(colored)
					setGLColor(y1);
			}
			else {
        x=obj->objectData[index].coordinates[c*3];
        y1=obj->objectData[index].coordinates[c*3+1];
        y2=obj->objectData[index].coordinates[c*3+2];
				if(y1<pref.ymin)
					y1=pref.ymin;
				else if(y1>pref.ymax)
					y1=pref.ymax;
				if(y2>pref.ymax)
					y2=pref.ymax;
				else if(y2<pref.ymin)
					y2=pref.ymin;
				
			}
			if(end)
			{
				if(y1 != y2)   
				{
					glBegin(GL_TRIANGLE_STRIP);
					end=false;
					glVertex3f(x,y1,0.0f);
					glVertex3f(x,y2,0.0f);
				}
			}
			else {
				if(y1==y2)
				{
					glEnd();
					end=true;
				}
				else
				{
					glVertex3f(x,y1,0.0f);
					glVertex3f(x,y2,0.0f);
				}
			}
		}
		if(!end)
			glEnd();
		glEndList();
	}
	else
	{
	//	perror("print index="+QString::number(index)+" length="+QString::number(objectInfo[index].length));
		glBegin(GL_LINE_STRIP);
		bool end=false;
    for(int c=0; c<obj->objectData[index].coordinateLength; c++)
		{
			if(end)
			{
        if(obj->objectData[index].coordinates[c*2+1] >pref.ymin && obj->objectData[index].coordinates[c*2+1] < pref.ymax && obj->objectData[index].coordinates[c*2]>pref.xmin && obj->objectData[index].coordinates[c*2]< pref.xmax)
				{
					glBegin(GL_LINE_STRIP);
					end=false;
					if(colored)
            setGLColor(obj->objectData[index].coordinates[(c)*2+1]);
				//	glVertex3f(oldx,oldy,0.0f);
					
					
          if(c<obj->objectData[index].coordinateLength-2)
					{
            double delta1=obj->objectData[index].coordinates[(c-1)*2+1]-obj->objectData[index].coordinates[c*2+1];
            double delta2=obj->objectData[index].coordinates[c*2+1]-obj->objectData[index].coordinates[(c+1)*2+1];
						if(delta1*delta2>=0.0)
              glVertex3f(obj->objectData[index].coordinates[(c-1)*2],obj->objectData[index].coordinates[(c-1)*2+1],0.0f);
						else 
						{
              glVertex3f(obj->objectData[index].coordinates[(c-1)*2],-1.0*obj->objectData[index].coordinates[(c-1)*2+1]*HUGE_VAL,0.0f);
						}
					}

					if(colored)
            setGLColor(obj->objectData[index].coordinates[c*2+1]);
          glVertex3f(obj->objectData[index].coordinates[c*2],obj->objectData[index].coordinates[c*2+1],0.0f);
				}
				else {
          oldx=obj->objectData[index].coordinates[c*2];
          oldy=obj->objectData[index].coordinates[c*2+1];
				}
			}
			else {

        ObjectData*tmpObj=&obj->objectData[index];

        if(tmpObj->coordinates[c*2+1] > pref.ymin &&
           tmpObj->coordinates[c*2+1] < pref.ymax &&
           tmpObj->coordinates[c*2]   > pref.xmin &&
           tmpObj->coordinates[c*2]< pref.xmax)
				{
					
					if(colored)
            setGLColor(obj->objectData[index].coordinates[c*2+1]);
          glVertex3f(obj->objectData[index].coordinates[c*2],obj->objectData[index].coordinates[c*2+1],0.0f);
				}
				else {
					
					if(colored)
            setGLColor(obj->objectData[index].coordinates[c*2+1]);
					if(c>2)
					{
            double delta1=obj->objectData[index].coordinates[(c-2)*2+1]-obj->objectData[index].coordinates[(c-1)*2+1];
            double delta2=obj->objectData[index].coordinates[(c-1)*2+1]-obj->objectData[index].coordinates[(c)*2+1];
						if(delta1*delta2>=0.0)
              glVertex3f(obj->objectData[index].coordinates[c*2],obj->objectData[index].coordinates[c*2+1],0.0f);
						else 
						{
              glVertex3f(obj->objectData[index].coordinates[c*2],-1.0*obj->objectData[index].coordinates[c*2+1]*HUGE_VAL,0.0f);
						}
					}
					
					
					glEnd();
					end=true;
          oldx=obj->objectData[index].coordinates[c*2];
          oldy=obj->objectData[index].coordinates[c*2+1];
				}
			}
		}
		if(!end)
			glEnd();
		glEndList();
	//	perror("print end");
	}
	return list;
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
	hasSolveObjects=true;
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
	hasSolveObjects=true;
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
	hasSolveObjects=true;
}
void GraphOutput::drawPolarLine(double angle)
{
	if(pref.angle==DEG)
		angle*=PI/180.0;
	else if(pref.angle==GRA)
		angle*=PI/200.0;
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
	hasSolveObjects=true;
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
	hasSolveObjects=true;
}

void GraphOutput::draw3dYLine(double x,double z)
{
	if(x<pref.xmin || x>pref.xmax || z<pref.zmin || z>pref.zmax)
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
	hasSolveObjects=true;
}
void GraphOutput::draw3dZLine(double x,double y)
{
	if(x<pref.xmin || x>pref.xmax || y<pref.ymin || y>pref.ymax)
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
	hasSolveObjects=true;
}

void GraphOutput::drawPoints(long double *coordinates,int num,bool con)
{
	GLuint list;
	list=glGenLists(1);
	double step=PI/10;
	double radiusX=(pref.xmax-pref.xmin)/200,radiusY=(pref.ymax-pref.ymin)/200;
	
	glNewList(list, GL_COMPILE);
	qglColor(QColor(0,0,0));
	for(int c1=0; c1<num; c1++)
	{
		glBegin(GL_LINE_STRIP);
		for(int c=0; c<=20; c++)
			glVertex3f(cos((double)c*step)*radiusX+coordinates[2*c1],sin((double)c*step)*radiusY+coordinates[2*c1+1],0.0f);
		glEnd();
	}
	if(con)
	{
		qglColor(QColor(100,0,0));
		glBegin(GL_LINE_STRIP);
		for(int c=0; c<num; c++)
				glVertex3f(coordinates[2*c],coordinates[2*c+1],0.0f);
		glEnd();
	}
	glEndList();
	additionalObjects.NewItem(list);
	if(!drawScreenshot)
		repaint();
	hasStatisticsObjects=true;
}


void GraphOutput::removeLines()
{
	while(additionalObjects.GetLen() > 0)
	{
		glDeleteLists(additionalObjects[0],1);
		additionalObjects.DeleteItem(0);
	}
	hasSolveObjects=hasStatisticsObjects=false;
	if(!drawScreenshot)
		repaint();
}

void GraphOutput::resetRotation()
{
	xRotation=yRotation=0;
	zMove=0;
}



void GraphOutput::generateTexture()
{
	if(texture==0xffffffff)
		return;
//	struct timeval t1,t2;
//	int seconds,usecs;
//	gettimeofday(&t1,NULL);
//	gettimeofday(&t2,NULL);

	
//	seconds=t2.tv_sec-t1.tv_sec;
//	usecs=t2.tv_usec-t1.tv_usec;
//	if(seconds > 0 && usecs < 0)
//	{
//		seconds--;
//		usecs=1000000+usecs;
//	}
//	perror("convertToImage: "+QString::number(seconds)+" "+QString::number(usecs));
	glEnable(GL_TEXTURE_2D);

//	if(drawState==DRAWFREE)
		(*drawImage)=drawMap->convertToImage();
//	else if(drawState!=DRAWNONE)
//		(*drawImage)=overlayMap->convertToImage();

	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	unsigned char*data=drawImage->bits();
	int c=TEXTURESIZE*TEXTURESIZE;
	
	while(c--)
		if((data[c*4]) ||(data[c*4+1]) || (data[c*4+2]))
			data[c*4+3]=0xff;
	else data[c*4+3]=0x00;

	glTexImage2D(GL_TEXTURE_2D, 0, 4, TEXTURESIZE,
				 TEXTURESIZE, 0, GL_BGRA, GL_UNSIGNED_BYTE,
				 data);

	glDisable(GL_TEXTURE_2D);
	
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
		if(dynamicPos >= dynamicSteps)
			dynamicPos=0;
	}
	
	repaint();
}

void GraphOutput::timerStartSlot(bool start)
{
	if(start && isDynamic)
	{
		timer->start(pref.dynamicDelay*10,false);
	}
	else {
		timer->stop();
	}
}


void GraphOutput::screenshotSlot(int x, int y)
{
	drawScreenshot=true;
	if(x<=0)
		x=geometry().width();
	if(y<=0)
		y=geometry().height();
	
	scr=renderPixmap(x,y,false);
	emit screenshotSignal(&scr);
	drawScreenshot=false;
//	initializeGL();
//	repaint();

}


void GraphOutput::drawSlot(int state,QColor color,int pen)
{

	if(state==DRAWCLEAR)
	{
		if(backMap[BACKSTEPS-1]!=NULL)
			delete backMap[BACKSTEPS-1];
		for(int c=BACKSTEPS-1; c>0; c--)
			backMap[c]=backMap[c-1];
		backMap[0]=drawMap;
		drawMap=new QPixmap(drawMap[0]);
		backCursor=0;
		
		drawMap->fill(QColor(0,0,0));
		generateTexture();
		repaint();
	}
	else if(state==DRAWBACK)
	{
		if(backCursor<BACKSTEPS && backMap[backCursor]!=NULL)
		{
			QPixmap*tmp=drawMap;
			drawMap=backMap[backCursor];
			backMap[backCursor]=tmp;
			backCursor++;
			generateTexture();
			repaint();
		}
	}
	else if(state==DRAWFORWARD)
	{
		if(backCursor>0)
		{
			backCursor--;
			QPixmap*tmp=drawMap;
			drawMap=backMap[backCursor];
			backMap[backCursor]=tmp;
			generateTexture();
			repaint();
		}
	}
	else 
	{
		drawColor=color;
		drawPen=pen;
		if((state==DRAWNONE || drawState==DRAWNONE) && (state != drawState))
		{
			drawState=state;
			repaint();
		}
		else drawState=state;
		if(drawState==DRAWTEXT)
		{
			bool ret;
			drawString = QInputDialog::getText(GRAPHOUTC_STR1,GRAPHOUTC_STR2,
					QLineEdit::Normal,drawString,&ret,this );
			if(!ret)
				drawString="";
		}
	//	perror("DrawSlot: "+QString::number(drawState));
	}
}

void GraphOutput::threadTimerSlot()
{
  QListIterator<ObjectInfo*>i(objectInfo);
  ObjectInfo*obj;
  int c;

	bool allStarted=true,allFinished=true;
  while(i.hasNext())
	{
    obj=i.next();

    for(c=0; c<obj->dataLength; c++)
    {
      if(!obj->objectData[c].processed)
      {
        allStarted=false;
        for(int c1=0; c1<THREADS; c1++)
        {
          if(threads[c1]->wait(0))
          {
            obj->objectData[c].processed=true;
            threads[c1]->setObjectData(obj,c);
            threads[c1]->start();
            break;
          }
        }
      }
    }
	}
//	qDebug("threadTimer2");
	if(allStarted)
	{
		for(int c=0; c<THREADS; c++)
		{
			if(!threads[c]->wait(0))
			{
				allFinished=false;
				break;
			}
		}
		if(allFinished)
		{
			graphProcess=false;
			emit processingFinished();
			threadTimer->stop();
		}
		
	}
//	qDebug("threadTimer end");
}

void GraphicsThread::run()
{
	if(index>=0)
    ((GraphOutput*)parent)->processGraph(obj,index,threadData,vars);
	QCustomEvent *ev=new QCustomEvent(SIGTHREADSYNC);
	QApplication::postEvent(parent,ev);
}



