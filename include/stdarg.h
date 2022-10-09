#ifndef __STDARG_H_DEFINED
#define __STDARG_H_DEFINED 1

typedef unsigned char * va_list;

#define va_start(lst,lastparam) ( (void)((lst) = (va_list)(&(lastparam)+1)) )
#define va_end(lst) ( (void)((lst)=0) )
#define va_arg(lst,type) ( (((type*)((lst)=((lst) + sizeof(type))))[-1]) )


#endif