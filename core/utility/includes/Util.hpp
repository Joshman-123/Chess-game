#pragma
#define DELETE_COPY_MOVE_OPERATORS(Class) \
    Class(const Class&) = delete; \
    Class& operator=(const Class&) = delete; \
    Class(Class&&) = delete; \
    Class& operator=(Class&&) = delete;

