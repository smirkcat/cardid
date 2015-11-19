说明，

修改者 李杰

修改原来无用队列冗余的存储变量，以及无用边缘信息
原来是用Rect的boundingRect链接，现在使用RotateRect的minAreaRect链接，
因为保存有angel旋转角度，可以用来倾斜校正，最基础的Candidate块没有改变。

旋转几次测试结果是角度是正确的，角度比较小的情况下

工程时vs2013 依赖opencv 自己修改配置文件opencv2411,或者手动添加opencv依赖，请别删除

修改cmakelist