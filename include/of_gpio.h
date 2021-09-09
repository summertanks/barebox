/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * OF helpers for the GPIO API
 *
 * based on Linux OF_GPIO API
 */

#ifndef __OF_GPIO_H
#define __OF_GPIO_H

/*
 * This is Linux-specific flags. By default controllers' and Linux' mapping
 * match, but GPIO controllers are free to translate their own flags to
 * Linux-specific in their .xlate callback. Though, 1:1 mapping is recommended.
 */
enum of_gpio_flags {
	OF_GPIO_ACTIVE_LOW = 0x1,
};

#ifdef CONFIG_OF_GPIO
extern int of_get_named_gpio_flags(struct device_node *np,
		const char *list_name, int index, enum of_gpio_flags *flags);

#else /* CONFIG_OF_GPIO */

static inline int of_get_named_gpio_flags(struct device_node *np,
		const char *list_name, int index, enum of_gpio_flags *flags)
{
	return -ENOSYS;
}

#endif /* CONFIG_OF_GPIO */

/**
 * of_gpio_named_count() - Count GPIOs for a device
 * @np:		device node to count GPIOs for
 * @propname:	property name containing gpio specifier(s)
 *
 * The function returns the count of GPIOs specified for a node.
 * Note that the empty GPIO specifiers count too. Returns either
 *   Number of gpios defined in property,
 *   -EINVAL for an incorrectly formed gpios property, or
 *   -ENOENT for a missing gpios property
 *
 * Example:
 * gpios = <0
 *          &gpio1 1 2
 *          0
 *          &gpio2 3 4>;
 *
 * The above example defines four GPIOs, two of which are not specified.
 * This function will return '4'
 */
static inline int of_gpio_named_count(struct device_node *np, const char* propname)
{
	return of_count_phandle_with_args(np, propname, "#gpio-cells");
}

/**
 * of_gpio_count() - Count GPIOs for a device
 * @np:		device node to count GPIOs for
 *
 * Same as of_gpio_named_count, but hard coded to use the 'gpios' property
 */
static inline int of_gpio_count(struct device_node *np)
{
	return of_gpio_named_count(np, "gpios");
}

static inline int of_get_gpio_flags(struct device_node *np, int index,
		      enum of_gpio_flags *flags)
{
	return of_get_named_gpio_flags(np, "gpios", index, flags);
}

static inline int of_get_named_gpio(struct device_node *np,
				const char *list_name, int index)
{
	return of_get_named_gpio_flags(np, list_name, index, NULL);
}

/**
 * of_get_gpio() - Get a GPIO number to use with GPIO API
 * @np:		device node to get GPIO from
 * @index:	index of the GPIO
 *
 * Returns GPIO number to use with Linux generic GPIO API, or one of the errno
 * value on the error condition.
 */
static inline int of_get_gpio(struct device_node *np, int index)
{
	return of_get_gpio_flags(np, index, NULL);
}

#endif
