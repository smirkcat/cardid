### 修改说明
1.修改原来无用队列冗余的存储变量，以及无用边缘信息，也修改了自适应二值化的参数设置;
2.原来是用Rect的boundingRect链接，现在使用RotateRect的minAreaRect链接，因为保存有angel旋转角度，可以用来倾斜校正，最基础的Candidate块没有改变。
3.旋转几次测试结果是角度是正确的，在角度左右不超过45度的情况下

### window平台vs编译
工程vs2013 依赖opencv库以及jni头文件，打开前添加环境变量OPENCV_DIR其值为opencv2.4.11的build目录，以及JAVA_HOME

### linux平台cmake编译
请用下面命令
```markdown
mkdir linux
cd linux
cmake ../
make
```

### 代码结构
```markdown
/include 头文件放置目录
/src 源文件放置目录
/test 测试用例源文件
CMakeLists.txt cmake运行文件
```
