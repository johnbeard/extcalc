/*/////////////////////////////////////////Concalc////////////////////////////////////////////
/////////////////////////////////Scientific Graphic Calculator////////////////////////////////

File:         concalc.h
Author:       Rainer Strobel
Email:        rainer1223@users.sourceforge.net
Homepage:     http://extcalc-linux.sourceforge.net

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

Main header file of Concalc.

////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef CONSOLECALC_H
#define CONSOLECALC_H

void searchScripts(char*,Preferences*,Variable*,ThreadSync*);
void loadSubScripts(ThreadSync*,Preferences*,Variable*,Script*);
void initDebugging(char*,ThreadSync*);
//int commentRemover(char *code);
//int preferencesPreprocessor(char *code,Preferences*pref);





#endif
