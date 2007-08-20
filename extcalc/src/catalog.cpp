/*/////////////////////////////////////////Extcalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         catalog.cpp
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.


////////////////////////////////////////////////////////////////////////////////////////////*/
#include "catalog.h"

void Catalog::mathStandardSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("+");
			break;
		case 2:
			emit menuSignal("-");
			break;
		case 3:
			emit menuSignal("*");
			break;
		case 4:
			emit menuSignal("/");
			break;
	}
}

void Catalog::mathTrigonometricSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("sin");
			break;
		case 2:
			emit menuSignal("cos");
			break;
		case 3:
			emit menuSignal("tan");
			break;

	}
}

void Catalog::mathExtendedSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("abs");
			break;
		case 2:
			emit menuSignal("arg");
			break;
		case 3:
			emit menuSignal("conj");
			break;
	}
}

	
void Catalog::matrixSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("[<index>]");
			break;
	}
}

	
void Catalog::scriptStandardSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("if(<exp>) then <exp> else <exp>");
			break;
		case 2:
			emit menuSignal("for(<exp>;<exp>;<exp>)<exp>");
			break;
		case 3:
			emit menuSignal("while(<exp>)<exp>");
			break;
	}
}

void Catalog::scriptTextSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("print(<text>)");
			break;
	}
}

void Catalog::scriptGraphicsSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("drawpoint(<x>,<y>)");
			break;
	}
}

void Catalog::scriptGLSlot(int id)
{
	switch(id)
	{
		case 1:
			emit menuSignal("glbegin(<type>)");
			break;
	}
}







