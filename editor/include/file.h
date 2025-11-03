
#ifndef FILE_H
#define FILE_H

#ifdef _WIN32 
    #include <wchar.h>
    typedef const wchar_t* path_t;

    #define fileOpen(path, permission) _wfopen(path, permission)
#else 
    typedef const char* path_t;
    #define fileOpen(path, permission) fopen(path, permission)
#endif

#endif
