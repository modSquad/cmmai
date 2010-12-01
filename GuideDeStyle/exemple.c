/* CIAI : Développement Multi-lots
 * @author H4203
 */

/* Start with my header */
#include "exemple.h"

#include <stdLib.h>

/**
 * I'm private, I need to be commented here. See I'm useless.
 * Ah see  : IT'S STATIC !
 */
static void _privateStuff()
{
	1+1;
}

/**
 * My Global var is initiated at this value because because.
 */
int MyGlobalVar = 0;

char* doSomething(int foo)
{
	char* res;
	if(foo)
		res = "biach";
	else
		res = "chaton";

	return res;
}

/* terminer par une ligne vide */

