#ifndef _LINUX_STRING_H_
#define _LINUX_STRING_H_

#include <linux/types.h>	/* for size_t */
#include <linux/stddef.h>	/* for NULL */

#ifdef __cplusplus
extern "C" {
#endif

extern char * strpbrk(const char *,const char *);
extern char * strsep(char **,const char *);
extern __kernel_size_t strspn(const char *,const char *);


#define strchr(s, c) ({ \
	(typeof(&(s)[0]))(_strchr((s), c)); \
	})

#define strrchr(s, c) ({ \
	(typeof(&(s)[0]))(_strrchr((s), c)); \
	})

#define strstr(s1, s2) ({ \
	(typeof(&(s1)[0]))(_strstr((s1), (s2))); \
	})

#ifndef __HAVE_ARCH_STRCHRNUL
extern char * strchrnul(const char *,int);
#endif

/*
 * Include machine specific inline routines
 */
#include <asm/string.h>

#ifndef __HAVE_ARCH_STRCPY
extern char * strcpy(char *,const char *);
#endif
#ifndef __HAVE_ARCH_STRNCPY
extern char * strncpy(char *,const char *, __kernel_size_t);
#endif
#ifndef __HAVE_ARCH_STRLCPY
size_t strlcpy(char *, const char *, size_t);
#endif
#ifndef __HAVE_ARCH_STRCAT
extern char * strcat(char *, const char *);
#endif
#ifndef __HAVE_ARCH_STRNCAT
extern char * strncat(char *, const char *, __kernel_size_t);
#endif
#ifndef __HAVE_ARCH_STRCMP
extern int strcmp(const char *,const char *);
#endif
#ifndef __HAVE_ARCH_STRNCMP
extern int strncmp(const char *,const char *,__kernel_size_t);
#endif
#ifndef __HAVE_ARCH_STRNICMP
extern int strnicmp(const char *, const char *, __kernel_size_t);
#endif
#ifndef __HAVE_ARCH_STRCASECMP
extern int strcasecmp(const char *s1, const char *s2);
#endif
#ifndef __HAVE_ARCH_STRNCASECMP
extern int strncasecmp(const char *s1, const char *s2, size_t n);
#endif
#ifndef __HAVE_ARCH_STRCHR
extern char * _strchr(const char *,int);
#endif
#ifndef __HAVE_ARCH_STRRCHR
extern char * _strrchr(const char *,int);
#endif
#ifndef __HAVE_ARCH_STRSTR
extern char * _strstr(const char *,const char *);
#endif
#ifndef __HAVE_ARCH_STRLEN
extern __kernel_size_t strlen(const char *);
#endif
#ifndef __HAVE_ARCH_STRNLEN
extern __kernel_size_t strnlen(const char *,__kernel_size_t);
#endif
#ifndef __HAVE_ARCH_STRDUP
extern char * strdup(const char *);
#endif
#ifndef __HAVE_ARCH_STRNDUP
extern char *strndup(const char *, size_t);
#endif
#ifndef __HAVE_ARCH_STRSWAB
extern char * strswab(const char *);
#endif

#ifndef __HAVE_ARCH_MEMSET
extern void * memset(void *,int,__kernel_size_t);
#endif
#ifndef __HAVE_ARCH_MEMCPY
extern void * memcpy(void *,const void *,__kernel_size_t);
#endif
#ifndef __HAVE_ARCH_MEMMOVE
extern void * memmove(void *,const void *,__kernel_size_t);
#endif
#ifndef __HAVE_ARCH_MEMSCAN
extern void * memscan(void *,int,__kernel_size_t);
#endif
#ifndef __HAVE_ARCH_MEMCMP
extern int memcmp(const void *,const void *,__kernel_size_t);
#endif
#ifndef __HAVE_ARCH_MEMCHR
extern void * memchr(const void *,int,__kernel_size_t);
#endif
extern char * skip_spaces(const char *);

extern char *strim(char *);

void *memchr_inv(const void *start, int c, size_t bytes);

/**
 * kbasename - return the last part of a pathname.
 *
 * @path: path to extract the filename from.
 */
static inline const char *kbasename(const char *path)
{
	const char *tail = strrchr(path, '/');
	return tail ? tail + 1 : path;
}


#ifdef __cplusplus
}
#endif

void *memdup(const void *, size_t);

static inline void *kmemdup(const void *src, size_t len, gfp_t gfp)
{
	return memdup(src, len);
}

extern int kstrtobool(const char *s, bool *res);

int match_string(const char * const *array, size_t n, const char *string);

/**
 * strstarts - does @str start with @prefix?
 * @str: string to examine
 * @prefix: prefix to look for.
 */
static inline bool strstarts(const char *str, const char *prefix)
{
	return strncmp(str, prefix, strlen(prefix)) == 0;
}

#endif /* _LINUX_STRING_H_ */
