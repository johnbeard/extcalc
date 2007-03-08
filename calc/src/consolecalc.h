#ifndef CONSOLECALC_H
#define CONSOLECALC_H

void searchScripts(char*,Preferences*,Variable*,ThreadSync*);
void loadSubScripts(ThreadSync*,Preferences*,Variable*,Script*);
void initDebugging(char*,ThreadSync*);
int commentRemover(char *code);
int preferencesPreprocessor(char *code,Preferences*pref);





#endif
