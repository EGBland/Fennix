#ifndef __LOG_H_DEFINED
#define __LOG_H_DEFINED 1

#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN (1<<1)
#define LOG_LEVEL_ERR (1<<2)
#define LOG_LEVEL_DEBUG (1<<3)

void log(unsigned char level, char *msg);

#endif