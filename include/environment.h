/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <linux/list.h>
#include <errno.h>

/**
 * Managment of a environment variable
 */
struct variable_d {
	struct list_head list;
	char *name;
	char *data;
};

struct env_context {
	struct env_context *parent;
	struct list_head local;
	struct list_head global;
};

struct env_context *get_current_context(void);
char *var_val(struct variable_d *);
char *var_name(struct variable_d *);

#ifdef CONFIG_ENVIRONMENT_VARIABLES
const char *getenv(const char *);
int setenv(const char *, const char *);
void export_env_ull(const char *name, unsigned long long val);
int getenv_ull(const char *name, unsigned long long *val);
int getenv_ul(const char *name, unsigned long *val);
int getenv_uint(const char *name, unsigned int *val);
int getenv_bool(const char *var, int *val);
const char *getenv_nonempty(const char *var);
#else
static inline char *getenv(const char *var)
{
	return NULL;
}

static inline int setenv(const char *var, const char *val)
{
	return 0;
}

static inline void export_env_ull(const char *name, unsigned long long val) {}

static inline int getenv_ull(const char *name, unsigned long long *val)
{
	return -EINVAL;
}

static inline int getenv_ul(const char *name, unsigned long *val)
{
	return -EINVAL;
}

static inline int getenv_uint(const char *name, unsigned int *val)
{
	return -EINVAL;
}

static inline int export(const char *var)
{
	return -EINVAL;
}

static inline int getenv_bool(const char *var, int *val)
{
	return -EINVAL;
}

static inline const char *getenv_nonempty(const char *var)
{
	return NULL;
}
#endif

int env_pop_context(void);
int env_push_context(void);

int export(const char *);

static inline int unsetenv(const char *var)
{
	return setenv(var, NULL);
}

#endif	/* _ENVIRONMENT_H_ */

/**
 * @file
 * @brief Environment handling
 *
 * Important: This file will also be used on the host to create
 * the default environment when building the barebox binary.
 */
