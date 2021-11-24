# WebGPU on WASM by Emscripten

Based on Cocos Creator v3.4.0, emsdk 2.0.26.

WebGPU explainer:  https://gpuweb.github.io/gpuweb/explainer/

## 关于WebGPU

#### 什么是WebGPU ？

区别于WebGL:
>
WebGPU is a proposed Web API to enable webpages to use the system’s GPU (Graphics Processing Unit) to perform computations and draw complex images that can be presented inside the page. This goal is similar to the WebGL family of APIs, but WebGPU enables access to more advanced features of GPUs. Whereas WebGL is mostly for drawing images but can be repurposed (with great effort) to do other kinds of computations, WebGPU has first-class support for performing general computations on the GPU.

 #### 为什么选择WebGPU

（大势所趋

#### 为什么不直接用typescript实现

反过来说为什么用c++编译成wasm，因为这样c++部分可以共用framegragh部分的代码。而且因为编辑器基于electron，所以Windows上面WebGPU理论上可以利用[dawn](https://dawn.googlesource.com/dawn)(chrome上WebGPU的实现)直接原生跑DX12，Linux原生跑Vulkan, Mac原生跑Metal.



## 原生实现

#### 修改、编译

##### 所需环境

emsdk 2.0.26，因为emscripten编译用的make，windows下需要首先安装额外的make环境：

[make](http://gnuwin32.sourceforge.net/packages/make.htm) [coreutils](http://gnuwin32.sourceforge.net/packages/coreutils.htm) [libiconv](http://gnuwin32.sourceforge.net/packages/libiconv.htm) [libintl](http://gnuwin32.sourceforge.net/packages/libintl.htm)

emscripten安装环境详见[Emscripten官网](https://emscripten.org/docs/getting_started/downloads.html)，注意`install/activate latest`要改成对应版本`install/activate 2.0.26`.

安装完成后cmd 输入 `emcc -v`, 如下输出表示成功：

![image-20211123175408589](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20211123175408589.png)

##### 修改

所有c++实现都在engine-native\cocos\renderer\gfx-wgpu里边，对应ts胶水层都在engine\cocos\core\gfx\webgpu里边。修改原生c++代码需要手动编译（如下小节）并将生成的js和wasm文件拷贝到engine\cocos\core\gfx\webgpu\lib文件夹下替换原有文件，修改ts部分预览的时候编辑器重新编译即可，编辑器本身生效需要重启编辑器。

##### 编译

c++部分的改动需要手动编译，在engine-native\cocos\renderer\gfx-wgpu文件夹下依次运行

`emcmake cmake .`

`emmake make`

即可，在当前文件夹下会重新生成js和wasm文件。

#### 实现

##### c++部分

c++部分WebGPU部分的实现其实和其他后端并无二致，对应接口的头文件就是emscripten提供的webgpu.h。 基本流程和Metal很像，只有一些细微的差别。由Device创建command encoder, command encoder在一个pass中可以作为长期持有的对象，然后command encoder 可以创建render encoder 和 compute encoder分别执行对应功能，最后command encoder执行finish可以产生一个command buffer, 这个就是拿来提交进queue里的command buffer. 
