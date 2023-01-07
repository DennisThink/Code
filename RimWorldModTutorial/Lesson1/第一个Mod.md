# Rimoworld的mod教程第一篇

这是Rimworld的Mod教程第一篇，主要介绍About目录相关的内容。


1.创建一个目录(ModLesson1)            
2.创建一个ModLesson1的子目录About目录       
3.在About目录下创建一个png图片Preview.png(图片大小636*318).图片大小随意，默认为2:1比例。           
![img](./ModLesson1/About/Preview.png)

4.在About目录下创建一个About.xml文件,文件的内容如下。               
```xml
<?xml version="1.0" encoding="utf-8"?>
<ModMetaData>
  <name>ModLesson1</name>
  <packageId>ModLesson1</packageId>
  <author>DennisThink</author>
  <url>https://www.dennisthink.com/</url>
  <supportedVersions>
    <li>1.0</li>
    <li>1.1</li>
    <li>1.2</li>
    <li>1.3</li>
  </supportedVersions>
  <modDependencies>
    <li>
      <packageId>brrainz.harmony</packageId>
      <displayName>Harmony</displayName>
      <steamWorkshopUrl>steam://url/CommunityFilePage/2009463077</steamWorkshopUrl>
      <downloadUrl>https://github.com/pardeike/HarmonyRimWorld/releases/latest</downloadUrl>
    </li>
  </modDependencies>
  <loadAfter>
    <li>brrainz.harmony</li>
  </loadAfter>
  <description></description>
</ModMetaData>

```
5.将ModLesson1目录拷贝到Rimworld的Mod目录。                     
6.重新打开Rimword就可以看到我们制作的第一个Mod了。
![image](./Mod%E7%95%8C%E9%9D%A2.png)

参考:https://blog.csdn.net/qq_58145131/article/details/123726403
TODO:
1. About.xml的相关字段的解释和补充。
2. 错误提示信息的消除。