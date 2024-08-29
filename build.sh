#!/bin/bash  
  
# 设定目录路径  
BUILD_DIR="build"  
  
# 检查目录是否存在  
if [ -d "$BUILD_DIR" ]; then  
    # 如果目录存在，则清空其内容  
    echo "Directory $BUILD_DIR exists. Removing its contents..."  
    rm -rf "$BUILD_DIR"/*  
    # 注意：上面的命令不会删除目录本身，只会删除目录下的所有内容  
    # 如果你想要确保目录是空的（包括目录本身为空的情况），你可能不需要这一步  
    # 但如果你想要重新创建目录（比如为了重置权限等），可以保留上面的命令  
    # 并继续执行下面的mkdir命令  
else  
    # 如果目录不存在，则创建它  
    echo "Directory $BUILD_DIR does not exist. Creating it..."  
    mkdir -p "$BUILD_DIR"  
fi  
  
echo "Directory $BUILD_DIR is now ready."
cd $BUILD_DIR
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/aarch64.cmake
make package
