/* CIAI : Développement Multi-lots
 * @author H4203
 */

#ifndef EXEMPLE_H
#define EXEMPLE_H

/**
 * My structure is a custom structure which no particular goal. In fact, this
 * is uselles code.
 */
typedef struct
{
	/**
	 * Foo contains a value described by this comment.
	 */
	int foo;
	/**
	 * Understood I comment EACH member of the struct.
	 */
	int bar;
	/**
	 * Oh a pointer !
	 */
	char* baz;
} my_struct_t;

/**
 * My global var contains a globaly useless value.
 */
int MyGlobalVar;

/**
 * Get it ? This describe what does the function.
 * 
 * @param foo the foo value needed by the function
 * @return a pointer of characters \o/
 */
char* doSomething(int foo);

#endif

/* terminer par une ligne vide */

