#ifndef _LINUX_STRING_H_
#define _LINUX_STRING_H_

char * strcpy(char * dest,const char *src);
char * strncpy(char * dest,const char *src,unsigned int count);
int strcmp(const char * cs,const char * ct);
unsigned int strlen(const char * s);
void * memset(void * s,int c,unsigned int count);
void * memcpy(void *dest, const void *src, unsigned int count);
void * memmove(void * dest,const void *src,unsigned int count);
int memcmp(const void * cs,const void * ct,unsigned int count);

#endif /* _LINUX_STRING_H_ */
