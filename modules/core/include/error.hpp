//
// Created by xin on 11/8/15.
//

#ifndef LIGHTIMAGE_ERROR_HPP
#define LIGHTIMAGE_ERROR_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>

#define ERR(info) error(__FILE__, __LINE__, info)

namespace li
{
    inline void error(const char* file, long line, const char* info)
    {
        std::cerr<<file<<"\t"<<line<<":"<<info <<std::endl;
    }
}


#endif //LIGHTIMAGE_ERROR_HPP
