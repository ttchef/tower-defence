
#ifndef FILE_H
#define FILE_H

#ifdef _WIN32 
    #include <wchar.h>
    #include <stringapiset.h>
    #include <stdlib.h>
    
    static inline FILE* fileOpen(const char* path, const char* mode) {
        int32_t wlen = MultiByteToWideChar(CP_UTF8, 0, path, -1, NULL, 0);
        wchar_t* wpath = (wchar_t*)malloc(wlen * sizeof(wchar_t));
        MultiByteToWideChar(CP_UTF8, 0, path, -1, wpath, wlen);

        int32_t mlen = MultiByteToWideChar(CP_UTF8, 0, mode, -1, NULL, 0);
        wchar_t* wmode = (wchar_t*)malloc(mlen * sizeof(wchar_t));
        MultiByteToWideChar(CP_UTF8, 0, mode, -1, wmode, mlen);
        

        FILE* file = _wfopen(wpath, wmode);
        free(wpath);
        free(wmode);
        return file;
    }
#else 
    static inline FILE* fileOpen(const char* path, const char* mode) {
        return fopen(path, mode);    
    }
#endif

#endif
