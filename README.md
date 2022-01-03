# SourceHanSans-Pixel

基于思源黑体的开源CJK字符集像素字体。

提供C语言的示例程序，可在嵌入式硬件使用。

目前提供了16x15像素、12x11像素两种CJK字符集字库，全字库体积为1.4MB。

![demo](demo/16.png)
![demo](demo/12.png)

# 示例程序

[UTF8文本绘制](https://github.com/44670/SourceHanSans-Pixel/tree/main/examples/C)

提示：修改hal.h中的平台相关代码后可移植到不同的软硬件平台上。

# 文件列表

**SourceHanSansSC-VF.otf**

  原始版本的Source Hans Sans字体文件。

**font16x15.4FN**

  16x15像素、CJK字符集的二进制字库文件，使用方法参考示例程序。

**font12x11.4FN**

  12x11像素、CJK字符集的二进制字库文件，使用方法参考示例程序。
  
**WorkBench.ipynb**

  实现像素字体转换、编码、预览的Notebook文件，可以在Jupyter Notebook中运行。



# 许可协议

"Source Han Sans" 字体及其衍生产物，遵循SIL OPEN FONT LICENSE Version 1.1协议。

本项目包含的程序代码（WorkBench.ipynb、示例程序代码等等），以MIT协议发布。
