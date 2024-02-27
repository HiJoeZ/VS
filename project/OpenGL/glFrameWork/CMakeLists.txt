#递归将本文件夹下的所有cpp放到FW中
file(GLOB_RECURSE FW ./ *.cpp)

#将WRAPPER中所有cpp编译为frameWork这个lib库
add_library(fw ${FW})