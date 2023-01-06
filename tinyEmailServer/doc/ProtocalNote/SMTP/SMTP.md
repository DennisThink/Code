1、SMTP协议简介

SMTP称为简单邮件传输协议（Simple Mail Transfer Protocal），目标是向用户提供高效、可靠的邮件传输。它的一个重要特点是它能够在传送中接力传送邮件，即邮件可以通过不同网络上的主机接力式传送。通常它工作在两种情况下：一是邮件从客户机传输到服务器；二是从某一个服务器传输到另一个服务器。SMTP是一个请求/响应协议，它监听25号端口，用于接收用户的Mail请求，并与远端Mail服务器建立SMTP连接。

2、SMTP协议工作机制

SMTP通常有两种工作模式。发送SMTP和接收SMTP。具体工作方式为：发送SMTP在接收到用户的邮件请求后，判断此邮件是否为本地邮件，若是直接投送到用户的邮箱，否则向DNS查询远端邮件服务器的MX记录，并建立与远端接收SMTP之间的一个双向传送通道，此后SMTP命令由发送SMTP发出，由接收SMTP接收，而应答则反方向传送。一旦传送通道建立，SMTP发送者发送MAIL命令指明邮件发送者。如果SMTP接收者可以接收邮件则返回OK应答。SMTP发送者再发出RCPT命令确认邮件是否接收到。如果SMTP接收者接收，则返回OK应答；如果不能接收到，则发出拒绝接收应答（但不中止整个邮件操作），双方将如此反复多次。当接收者收到全部邮件后会接收到特别的序列，入伏哦接收者成功处理了邮件，则返回OK应答。

3、SMTP的连接和发送过程

（a）建立TCP连接

（b）客户端发送HELO命令以标识发件人自己的身份，然后客户端发送MAIL命令；

         服务器端正希望以OK作为响应，表明准备接收

（c）客户端发送RCPT命令，以标识该电子邮件的计划接收人，可以有多个RCPT行；

         服务器端则表示是否愿意为收件人接收邮件

（d）协商结束，发送邮件，用命令DATA发送

（e）以.表示结束输入内容一起发送出去

（f）结束此次发送，用QUIT命令退出

示例如下：


C: telent SMTP.163.com 25  //以telenet方式连接163邮件服务器
S: 220 163.com Anti-spam GT for Coremail System //220为响应数字，其后的为欢迎信息
C: HELO SMTP.163.com //除了HELO所具有的功能外，EHLO主要用来查询服务器支持的扩充功能 
S: 250-mail
S: 250-AUTH LOGIN PLAIN
S: 250-AUTH=LOGIN PLAIN
S: 250 8BITMIME //最后一个响应数字应答码之后跟的是一个空格，而不是'-' 
C: AUTH LOGIN   //请求认证
S: 334 dxNlcm5hbWU6  //服务器的响应——经过base64编码了的“Username”=
C: Y29zdGFAYW1heGl0Lm5ldA==  //发送经过BASE64编码了的用户名
S: 334 UGFzc3dvcmQ6  //经过BASE64编码了的"Password:"=
C: MTk4MjIxNA==  //客户端发送的经过BASE64编码了的密码
S: 235 auth successfully  //认证成功 
C: MAIL FROM: bripengandre@163.com  //发送者邮箱
S: 250 … .  //“…”代表省略了一些可读信息
C: RCPT TO: bripengandre@smail.hust.edu.cn　//接收者邮箱
S: 250 … .    // “…”代表省略了一些可读信息
C: DATA //请求发送数据
S: 354 Enter mail, end with "." on a line by itself
C: Enjoy Protocol Studing
C: .
S: 250 Message sent
C: QUIT //退出连接 
S: 221 Bye
其他命令：

VRFY——用于验证给定用户邮箱是否存在，以及接收关于该用户的详细信息；

EXPN——用于扩充邮件列表

4、邮件的路由过程

SMTP服务器是基于“域名服务DNS中计划收件人的域名来路由电子邮件”。SMTP服务器基于DNS中的MX记录来路由电子邮件，MX记录注册了域名和相关的SMTP中的主机，属于该域的电子邮件都应向该主机发送。

若SMTP服务器mail.abc.com收到一封信要发送到shuser@sh.abc.com：

a: SendMail请求DNS给出主机sh.abc.com的CNAME记录，如有，假若CNAME到shmail.abc.com，则再次请求shmail.abc.com的CNAME记录，直到没有为止；

b: 假定被CNAME到shmail.abc.com，然后SendMail请求@abc.com域的DNS给出shmail.abc.com的MX记录，

    shmail MX 5 shmail.abc.com

    10 shmail2.abc.com

c: SendMail做好请求DNS给出shmail.abc.com的A记录，即IP地址，若返回值为1.2.3.4

d: SwndMail与1.2.3.4连接，传送这封信给shuser@sh.abc.com的信到1.2.3.4这台服务器的SMTP后台程序。

5、SMTP常用的命令

SMTP命令不区分大小写，但参数区分大小写。常用命令如下：

HELO <domain> <CRLF>——向服务器标识用户身份发送者能欺骗、说谎，但一般情况下服务器都能检测到

RCPT TO: <forward-path> <CRLF>——<forward-path>用来标志邮件接收者的地址，常用在MAIL FROM后，可以有多个RCPT TO

DATA <CRLF>——将之后的数据作为数据发送，以<CRLF>.<CRLF>标志数据的结尾

REST <CRLF>——重置会话，当前传输被取消

NOOP <CRLF>——要求服务器返回OK应答，一般用作测试

QUIT <CRLF>——结束会话

VRFY <string> <CRLF>——验证指定的邮箱是否存在，由于安全方面的原因，服务器大多禁止此命令

EXPN <string> <CRLF>——验证给定的邮箱列表是否存在，由于安全方面的原因，服务器大多禁止此命令

HELP <CRLF>——查询服务器支持什么命令

6、SMTP常用的响应

501——参数格式错误

502——命令不可实现

503——错误的命令序列

504——命令参数不可实现

211——系统状态或系统帮助响应

214——帮助信息

220<domain>——服务器就绪

221<domain>——服务关闭

421<domain>——服务器未就绪，关闭传输信道

250——要求的邮件操作完成

251——用户非本地，将转发向<forward-path>

450——要求的邮件操作未完成，邮箱不可用

550——要求的邮件操作未完成，邮箱不可用

451——放弃要求的操作，处理过程中出错

551——用户非本地，请尝试<forward-path>

452——系统存储不足，要求的操作未执行

552——过量的存储分配，要求的操作未执行

553——邮箱名不可用，要求的操作未执行

354——开始邮件输入，以“.”结束

554——操作失败

7、使用SMTP的必要性

一般的PC资源不够，处理能力不够，不可能全天候地连接在因特网上来收发邮件。所以使用SMTP服务器，可以让多个用户共用服务器，有效地降低了成本。

8、SMTP和邮件格式的关系

可以用一个比较形象的例子来说明：甲与乙书信来往，甲通过邮局向乙发送信件，邮局见转交邮件可看成使用了SMTP协议，至于书信的格式则会因为地区习惯等的不同而不同，这个书信格式可看成是邮件格式的标准。

9、浏览器发送邮件使用的协议

浏览器发送邮件的过程：

例如：bripengandre@126.com可通过登陆www.126.com来收发邮件

bripengandre@126.com在www.126.com提供的邮件页面上填写的相应信息（如发信人邮箱、收信人邮箱等），通过http协议被提交给126服务器；126服务器根据这些信息组装一封符合邮件规范的邮件（就像用户代理一样）；然后smtp.126.com通过SMTP协议将这封邮件发送到接收端邮件服务器。

由此可知，浏览器发送邮件只是用户代理的功能直接放到邮件服务器上去做了，至于邮件服务器见发送邮件仍然采用的是SMTP协议。
--------------------- 
作者：Caroline0071 
来源：CSDN 
原文：https://blog.csdn.net/kerry0071/article/details/28604267 
版权声明：本文为博主原创文章，转载请附上博文链接！