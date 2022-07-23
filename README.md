# 希家红娘 A-face-matching-app
#### 青岛理工大学

~~English version will be written soon~~

~~Once I get some spare time , I'll translate this project into English~~

#### 面向对象课程设计-一个根据人脸照片匹配度寻找对象的小软件
![image](https://user-images.githubusercontent.com/92865821/180488880-858a306f-8ebc-4310-b961-b7c2fdf33c2c.png)

### MFC OpenCV VC++


需要配置VS2019+OpenCV库，这个可以使用搜索引擎

上了一年大学这是我做的第一个完整的包括前后端的小程序

~~水平真的好菜全是bug~~

这个项目本来是四个人做的，但是感谢我摆烂的另外三个队友，让我一个人学到这么多东西。

## 以下是使用手册

（1）	打开程序，单击【选择自己的照片】按钮，系统会自动弹出文件管理器的对话框，再次鼠标单击选择待匹配对象的JPG格式图片。


（2）	选择完成后，单击【选择你要找的对象们】按钮，系统会自动弹出文件管理器的对话框，再次鼠标单击选择一个文件夹，这个文件夹应当包含可匹配的对象的多张JPG图片。


（3）	单击【计算】按钮，系统将自动在后台完成对相似度的计算并自动记录一个相似度较大（大于0.21）的图片路径，此时会提示二人照片的匹配度，如果用户认为这个匹配度满意，单击对话框的确定按钮。


（4）	单击【显示匹配】按钮，系统会将对象图片显示在程序右上角。


（5）	单击【退出程序】退出。


## 算法用的是直方图匹配  ~~但是我看不懂~~

![image](https://user-images.githubusercontent.com/92865821/180609047-86d79aae-288e-4b9a-86ad-45d87929a723.png)


## 参考资料

1、	Building Computer Vision Projects with OpenCV 4 and C++ (David Millán Escrivá)


2、	LEARN OPENCV C++ in 4 HOURS       	        https://www.youtube.com/watch?v=2FYm3GOonhk&t=2525s


3、	How to load jpg with MFC https://stackoverflow.com/questions/2490661/how-to-load-png-jpeg-images-using-mfc


4、	Face dataset：


https://www.kaggle.com/datasets/ashishjangra27/gender-recognition-200k-images-celeba 


5、	Other references: www.github.com


6、	Install Opencv & tutorials https://docs.opencv.org/4.x/d9/df8/tutorial_root.html 


## 一些其他的碎碎念

这个项目是去北京找小伙伴路上写的 被迫带着十几斤的笔记本赶火车 对待大学的小组作业 学到的对付人的知识绝对比编程本身重要 
