/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a C compiler to compile this file. If you    */
/*       are using GNU C++, be sure to use compile this   */
/*       file using a GNU compiler with the               */
/*       -fdollars-in-identifiers flag.                   */


extern void (*_ctors[])();
void (*_ctors[])() =
    {
    0
    };

extern void (*_dtors[])();
void (*_dtors[])() =
    {
    0
    };
