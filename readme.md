#Encoding problem

#Some Notes
1. 从windows中的记事本保存的文件都有BOM(Bytes Order Mark).  

2. windows记事本可以保存的格式：
	1. Ansi格式为，系统默认的编码，即在不同系统中不一样。在我电脑编码(code page)是windows-936,　即GBK.
	2. Unicode 即为　UTF-16BE(little-endian)  
	3. Unicode big endian 即为　UTF-16BE(big-endian)  
	4. UTF-8 就是 UTF-8

3. 中文编码
	gb2312 扩展并兼容 ASCII
	GBK 扩展并兼容 gb2312.  (原因：汉字太多了)
	GB18030 扩展并兼容GBK. （原因：少数民族)
	称这三个编码为DBCS(Double Byte Character Set)

4. Unicode 编码
	Unicode 是编码规范
	UTF(Unicode transformation format)　是如何保存和传输unicode的方案(实现).

#BOM(Bytes Order Mark) Table
|EncodingFormat|BOM|
|:---|:---:|
|UTF-8|0xef 0xbb 0xbf|
|UTF-16LE|0xff 0xfe|
|UTF-16BE|0xfe 0xff|
|ANSI| None|

windows根据此表，若发现BOM则按对应方式处理，若无则按ANSI(默认编码)处理。

## 查看BOM
运行以下命令，查看各个文件的前几个字节
```
xxd -g 1 ansi.txt
xxd -g 1 utf8.txt
xxd -g 1 unicode.txt
xxd -g 1 unicodeb.txt
```

#怎么转换一个文件的编码
1. In Linux
	1. 查看所有编码格式
		`iconv -l`
	2. 转换编码
		`iconv -f 'gbk' -t 'utf-8' ansi.txt -o 'ansi-conv.txt'`
		此处gbk等价于windows-936
2. In windows
	用记事本打开，另存为时，选择不同的编码方式。

# 确定文本的编码
对于Unicode文本最标准的途径是检测文本最开头的几个字节。如:  

|BOM|Charset/encoding |
|:---|---:|
|EF BB BF|UTF-8|
|FE FF|UTF-16/UCS-2, little endian(UTF-16LE)|
|FF FE|UTF-16/UCS-2, big endian(UTF-16BE)|
|FF FE 00 00|UTF-32/UCS-4, little endian.|
|00 00 FE FF|UTF-32/UCS-4, big-endia|



# windows 的代码页表
	874 （ANSI/OEM - 泰文）
	932 （ANSI/OEM - 日文 Shift-JIS）
	936 （ANSI/OEM - 简体中文 GBK）
	949 （ANSI/OEM - 韩文）
	950 （ANSI/OEM - 繁体中文 Big5）
	1250 （ANSI - 中欧）
	1251 （ANSI - 西里尔文）
	1252 （ANSI - 拉丁文 I）
	1253 （ANSI - 希腊文）
	1254 （ANSI - 土耳其文）
	1255 （ANSI - 希伯来文）
	1256 （ANSI - 阿拉伯文）
	1257 （ANSI - 波罗的海文）
	1258 （ANSI/OEM - 越南）



# References
[ASCII，Unicode和UTF-8](http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html)

[UTF-8, a transformation format of ISO 10646](https://www.ietf.org/rfc/rfc3629.txt)

# Quotation
	> 作者：时国怀
	> 链接：https://www.zhihu.com/question/20650946/answer/15751688
	> 来源：知乎
	> 著作权归作者所有，转载请联系作者获得授权。
	> 
	> 先来解释一下这三种编码的历史吧：
	> 
	> ANSI：最早的时候计算机ASCII码只能表示256个符号（含控制符号），这个字符集表示英文字母足够，其中，我们键盘上可见的符号的编码范围是从32到126（大小写英文字母、数字、英文符号等）。但表示汉字、日语、韩语就不太够用了，汉字常用字有3000多个。
	> 
	> 但是中国人也要用电脑打字，于是，中国人就研究出来了最早的中文字符集GB2312（GBK就是后来的扩展），GB2312的做法是，把ASC码取值范围的128～255这个区间挪用了一下，用两个ASC码表示一个汉字，这样可用的编码范围用十六进制表示就是0x8080到0xFFFF，这大概能表示一万多个符号，足够了。[注:实际没用那么多，GBK的范围是8140-FEFE]
	> 
	> 那个时候，计算机技术还不发达，各个国家搞自己的，比如台湾，也另搞了一套，叫BIG5（俗称：大五码），跟大陆的也不太一样，但方法是类似的，都是用0x80到0xFF这个区间。
	> 然后日语（有编码JIS）、韩语等等也各搞一套。
	> 
	> 这些国家的编码区间都是重叠的，但同一个汉字（比如有一些汉字同时存在于简体、繁体、日语汉字中）有不同的编码，很混乱是不是？但也凑合用了。编码不同导致了很多麻烦，比如一个网页，如果你不知道它是什么编码的，那么你可能很难确定它显示的是什么，一个字符可能是大陆简体/台湾繁体/日本汉字，但又完全是不同的几个字。
	> 
	> 所以如果用一些很老的软件，可能会听说有中文版/日文版之类的，对应的版本只能在对应的系统上运行。
	> 
	> 后来，这个对操作系统的开发实在是太困难了，因为这意味着不同语言的版本，都要重新编码。于是发明了Unicode。
	> 
	> Unicode这个东西，就是要把地球上所有的语言的符号，都用统一的字符集来表示，一个编码真正做到了唯一。
	> 
	> Unicode里有几种方式：
	> 
	> UTF-16BE/LE：UTF-16就是Windows模式的编码模式(Windows里说的Unicode一般都是指这种编码），用2个字节表示任意字符，注意：英文字符也占2个字节（变态不？），这种编码可以表示65536个字符，至于LE和BE，就是一个数值在内存/磁盘上的保存方式，比如一个编码0x8182，在磁盘上应该是0x81 0x82呢？还是0x82 0x81呢？就是高位是最先保存还是最后保存的问题，前者为BE，后者为LE。
			> 
			> 		UTF-8：UTF-8则是网页比较流行的一种格式：用一个字节表示英文字符，用3个字节表示汉字，准确的说，UTF-8是用二进制编码的前缀，如果某个UTF-8的编码的第一个字节的最高二进制位是0，则这个编码占1字节，如果是110，则占2字节，如果是1110，则占3字节……
			> 
			> 		好了，说了这么，再来研究Windows的记事本。
			> 
			> 		Windows早期（至少是95年以前的事情了）是ANSI字符集的，也就是说一个中文文本，在Windows简体中文版显示的是中文，到Windows日文版显示的就不知道是什么东西了。
			> 
			> 		后来，Windows支持了Unicode，但当时大部分软件都是用ANSI编码的，unicode还不流行，怎么办？Windows想了个办法，就是允许一个默认语言编码，就是当遇到一个字符串，不是unicode的时候，就用默认语言编码解释。（在区域和语言选项里可以改默认语言）
			> 
			> 		这个默认语言，在不同Windows语言版本里是不同的，在简体中文版里，是GBK，在繁体中文版里，是BIG5，在日文版里是JIS
			> 
			> 		而记事本的ANSI编码，就是这种默认编码，所以，一个中文文本，用ANSI编码保存，在中文版里编码是GBK模式保存的时候，到繁体中文版里，用BIG5读取，就全乱套了。
			> 
			> 		记事本也不甘心这样，所以它要支持Unicode，但是有一个问题，一段二进制编码，如何确定它是GBK还是BIG5还是UTF-16/UTF-8？记事本的做法是在TXT文件的最前面保存一个标签，如果记事本打开一个TXT，发现这个标签，就说明是unicode。标签叫BOM，如果是0xFF 0xFE，是UTF16LE，如果是0xFE 0xFF则UTF16BE，如果是0xEF 0xBB 0xBF，则是UTF-8。如果没有这三个东西，那么就是ANSI，使用操作系统的默认语言编码来解释。
			> 
			> 		Unicode的好处就是，不论你的TXT放到什么语言版本的Windows上，都能正常显示。而ANSI编码则不能。（UTF-8的好处是在网络环境下，比较节约流量，毕竟网络里英文的数据还是最多的）
			> 
			> 		举例：
			> 
			> 		同样一段中文文本（可以插入一些英文），保存成ANSI/Unicode/UTF-8，三个文件。
	> 
	> 修改windows的默认语言为日语之类的（WIN7的改法是：控制面板-时钟、语言和区域-更改显示语言-区域和语言-管理-非unicode程序语言-更改区域设置/WNIXP改法是：控制面板-区域和语言选项-非unicode程序语言）。
	> 
	> 修改完要求重启，重启以后，再打开这三个文件，ANSI的编码全乱了，其余两个都正常显示，这就是UNICODE的作用。
	> 
	> 另外，为什么记事本、开始菜单什么的还是正确的中文呢？明明我已经改了默认语言了？因为它们的程序编码也是unicode的。
	> 
	> 要把txt发给国外的朋友或者用在非中文的操作系统/软件里，那么你的编码最好选择unicode
	> 
	> -完- 
