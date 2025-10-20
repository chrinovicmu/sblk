#ifndef UTILS_H 
#define UTILS_H


#define PR_ERR_LOG(fmt, ...) \
    pr_err("[%s:%d:%s()] " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)


#endif // !UTILS_H 

