#include "logging.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

void log_list(const char *msg, va_list ap) 
{
	while (true) {
		const char *arg = va_arg(ap, const char *);
		if (arg==NULL) {
			break;
		}

		printf("%s",arg);
	}

	printf("\n");
}

void log_error(const char *msg, ...)
{
	va_list ap;

	printf ("ERROR: ");
	va_start(ap, msg);
	log_list(msg, ap);
}

void log_warning(const char *msg, ...)
{
	va_list ap;

	printf ("WARNING: ");
	va_start(ap, msg);
	log_list(msg, ap);
}

void log_info(const char *msg, ...)
{
	va_list ap;

	printf ("INFO: ");
	va_start(ap, msg);
	log_list(msg, ap);
}

