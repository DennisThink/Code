# 第二章 登录登出功能相关设计


## 1. 账号体系设计

登录和登出功能作为IM的基础,在第一部分进行介绍。

用户的账号体系设计，主要是为了在系统中标识每一个用户。用户的账号由以下几个方面构成。

| 名词     | 含义                                 | 来源                 |
| -------- | ------------------------------------ | -------------------- |
| 账号ID   | 用于唯一标识用户的8位数字            | 用户注册时系统生成   |
| 用户名   | 用户进行登录时，唯一标识用户的字符串 | 用户注册时由用户填写 |
| 用户密码 | 用户进行登录时，进行身份确认的字符串 | 用户注册时由用户填写 |
| 用户昵称 | 显示在主界面的，用户的昵称           | 用户注册时由用户填写 |


## 2. 主要操作的介绍

1. 账号创建和删除
2. 账号登录和登出
3. 用户验证和重置密码
4. 多设备登录和扫码登录

## 3. 章节介绍

在本章中，主要介绍了各个功能点的流程，以及需要的相关参数，并以Client_Core的为例，说明HTTP的请求和回复应该如何编写。