# 指定目标系统
set(CMAKE_SYSTEM_NAME Linux)
# 指定目标平台
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# 指定交叉编译工具链的根路径
set(CROSS_CHAIN_PATH ${PROJECT_SOURCE_DIR}/compile/bin/aarch64-none-linux-gnu)

set(CMAKE_C_COMPILER ${CROSS_CHAIN_PATH}-gcc)
set(CMAKE_CXX_COMPILER ${CROSS_CHAIN_PATH}-g++)