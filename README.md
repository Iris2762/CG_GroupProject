# 3BodyViwer

基于[Playground](https://gitee.com/mrcer/playground)的三体系统的模拟可视化和第一人称视角交互程序

Playground本身和3BodyViewer的增量开发均属于计算机图形学大作业的一部分

## 分工

## 项目环境

依赖`glfw3`、`glad`、`glm`、`std_image`，均已包含在`import`文件夹中。其中`glfw3`需要编译为动态库，`lib`中已经放置了我用`gcc`编译好的动态库，如果你使用的是其他工具链，请参考[LearnOpenGL](https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/)自行构建。编译出的可执行文件需要和`glfw3`动态库放置于同一目录。

程序可以在Windows上使用gcc工具链编译使用，已知使用msvc工具链时需要调整`shader.cpp`以及其他引用`shader`时可能会出现路径问题，在Linux上使用需要修改CMake文件链接X11（如果你使用的窗口管理器是X11）以及GL

## 项目结构

```
3BodyViewer
|
|-import
|   |-include       外部库引用
|   |-source        外部库源码
|
|-include           项目引用
|-source            项目源码
|-shader            着色器源码
|-lib               预编译动态库
```