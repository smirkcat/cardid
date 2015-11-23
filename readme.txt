说明，

修改者 李杰

修改原来无用队列冗余的存储变量，以及无用边缘信息，也修改了自适应二值化的参数设置
原来是用Rect的boundingRect链接，现在使用RotateRect的minAreaRect链接，
因为保存有angel旋转角度，可以用来倾斜校正，最基础的Candidate块没有改变。

旋转几次测试结果是角度是正确的，角度比较小的情况下

工程vs2013 依赖opencv和jni头文件 自己修改配置文件opencv2411和jnijava64,或者手动修改
，请别删除，删除后工程打不开

cmakelist为linux下编译命令 编码都是utf-8，请用对应格式打开

请用
下面命令（推荐）
mkdir release
cd release
cmake ..
make