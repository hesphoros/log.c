/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

typedef enum LogLevel_e {
	LOG_LEVEL_TRACE,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_FATAL
} LogLevel;

typedef struct {
	va_list ap;
	const char* fmt;
	const char* file;
	struct tm* time;

	void* udata;
	int line;
	LogLevel level;
} log_Event;

typedef void (*log_LogFn)(log_Event* ev);
typedef void (*log_LockFn)(bool lock, void* udata);

#define log_trace(...) log_log(LOG_LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(LOG_LEVEL_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(LOG_LEVEL_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_LOCK()   if (L.lock) L.lock(true, L.udata)
#define LOG_UNLOCK() if (L.lock) L.lock(false, L.udata)

const char* log_level_string(LogLevel level);
void log_set_lock(log_LockFn fn, void* udata);
void log_set_level(LogLevel level);
void log_set_quiet(bool enable);
int log_add_callback(log_LogFn fn, void* udata, LogLevel level);
int log_add_fp(FILE* fp, LogLevel level);

void log_log(LogLevel level, const char* file, int line, const char* fmt, ...);

#endif
