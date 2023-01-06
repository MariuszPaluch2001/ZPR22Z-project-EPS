//
// Created by mariusz on 26.12.22.
//
#ifndef ZPR_GUIUTILS_H
#define ZPR_GUIUTILS_H

#include <iostream>
#include <sys/stat.h>

long getFileSize(const std::string &filename)
{
    struct stat stat_buf{};
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size / 1000 : -1;
}

int convertEPSFileToPNG(const std::string &path){
    std::string gs_command_run = "gs -dEPSCrop -sDEVICE=png16m -r200 -dDownScaleFactor=8 -o tmp/.output_image.png ";
    gs_command_run += path;
    std::cout << gs_command_run << std::endl;
    return system(gs_command_run.c_str());
}

#endif // ZPR_GUIUTILS_H
