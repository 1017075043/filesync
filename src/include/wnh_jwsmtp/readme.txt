std::string html("<html>"
                 "<body>"
                 "<h1>aaa this is wunanhui test mail, think you!<h1>"
                 "</body>"
                 "</html>");

jwsmtp::mailer m(""/*接收者*/, "wunanhui_1@163.com"/*发送者*/, "aaaaa this is wunanhui test mail, think you!"/*主题*/ ,
                 ""/*内容*/, "smtp.163.com"/*邮件服务器地址*/,
                 jwsmtp::mailer::SMTP_PORT, false);

//添加多个接收者
m.addrecipient("2076729339@qq.com");
m.addrecipient("wunanhui_1@126.com");
m.addrecipient("wunanhui_1@163.com");

//添加HTML的发送内容，它会替换构造函数中的“这里填写邮件内容”
m.setmessageHTML(html);
// 添加多个附件
m.attach("config.log");
m.attach("autoscan.log");

//经过测试，163/126支持的auth认证是PLAIN模式
m.authtype(jwsmtp::mailer::PLAIN);

//这里输入认证用户名，注意哦，需要是***@163.com的用户名
m.username("wunanhui_1@163.com");
//这里输入密码
m.password("QWEasd123");
m.send(); // 这里发送邮件，需要注意的是，这里是同步模式哦！
std ::cout << m.response() << std::endl;//这里如果展示的是250，代表发送邮件成功











// Note that the only valid version of the GPL as far as jwSMTP
// is concerned is v2 of the license (ie v2, not v2.2 or v3.x or whatever),
// unless explicitly otherwise stated.
//
// This file is part of the jwSMTP library.
//
//  jwSMTP library is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; version 2 of the License.
//
//  jwSMTP library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with jwSMTP library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// jwSMTP library
//   http://johnwiggins.net
//   smtplib@johnwiggins.net
//
#include <iostream>
// Please note the jwsmtp library has to be installed
// for this next header to work.
#include "jwsmtp/jwsmtp.h"

// obviously we must escape the quotes i.e. \"
std::string html("<html>"
"<body>"
"This is the html part of the message<br><br>"
"<b>bold</b><br>"
"<i>italic</i><br>"
"<font size=\"7\">Large Text</font><br><br>"
"Or a link: <a href=\"http://johnwiggins.net\">johnwiggins.net</a><br><br>"
"And an image: <br><img alt=\"an image in email\" src=\"http://johnwiggins.net/jwsmtp/example.png\"><br>"
"</body>"
"</html>");

int main(int argc, char* argv[])
{
   // replace the users 'to' and 'from' here before compiling this demo
   jwsmtp::mailer m("root", "root", "subject line",
                    "This is the plain text part of the message", "localhost",
                    jwsmtp::mailer::SMTP_PORT, false);

   // send a html file (remember you still can send an html file as an attachment
   // but calling this function will allow mime compatible clients to actually
   // display the html if the client is set to show html messages.
   //    m.setmessageHTMLfile("/home/myname/thefile.html");

   // Build our html from a string. You can also send html as a vector.
   // i.e.
   //    std::vector<char> htmlvec;
   //    ....add html to the vector.
   //    m.setmessageHTML(htmlvec);
   m.setmessageHTML(html);

   //m.username("someone@somewhere.net");
   //m.password("secret");
   m.send(); // send the mail
   std ::cout << m.response() << "\n";
   return 0;
}





// Note that the only valid version of the GPL as far as jwSMTP
// is concerned is v2 of the license (ie v2, not v2.2 or v3.x or whatever),
// unless explicitly otherwise stated.
//
// This file is part of the jwSMTP library.
//
//  jwSMTP library is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; version 2 of the License.
//
//  jwSMTP library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with jwSMTP library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// jwSMTP library
//   http://johnwiggins.net
//   smtplib@johnwiggins.net
//
// http://www.boost.org
//#include <boost\thread\thread.hpp>

#include <iostream>
#include "jwsmtp/jwsmtp.h"

using std::cout;
using std::cin;
using std::string;

void Usage() {
   cout << "jwSMTP library demo program\n"
           "demo2 <email toaddress> <email fromaddress> <smtpserver>\n"
           "   e.g.\n"
           "      demo2 recipient@there.com me@server.com mail.server.com\n";
}

int main(int argc, char* argv[])
{
   if(argc != 4) {
      Usage();
      return 0;
   }

   cout << "jwSMTP library demo program\n\n";
   string to(argv[1]);
   string from(argv[2]);
   string smtpserver(argv[3]);

   if(to.length() < 2 || from.length() < 2 || smtpserver.length() < 2) {
      Usage();
      return 0;
   }

   char str[2048];
   cout << "Please enter the subject of the mail\n";
   cin.getline(str, 500);
   string subject(str);
   strcpy(str, "");

   cout << "Please enter the message body end with \".\" on a line by itself\n";
   string mailmessage;
   while(true) {
      cin.getline(str, 2048);
      if(!strcmp(str, "."))
         break;

      mailmessage += str;
      mailmessage += "\r\n";
      strcpy(str, "");
   }

   cout << "\nPlease wait sending mail\n";
   // This is how to tell the mailer class that we are using a direct smtp server
   // preventing the code from doing an MX lookup on 'smtpserver' i.e. passing
   // false as the last parameter.
   jwsmtp::mailer mail(to.c_str(), from.c_str(), subject.c_str(), mailmessage.c_str(),
                       smtpserver.c_str(), jwsmtp::mailer::SMTP_PORT, false);

   // using a local file as opposed to a full path.
   mail.attach("attach.png");

   // add another recipient (carbon copy)
   //mail.addrecipient("someoneelse@somewhere.net", mailer::Cc);

   // set a new smtp server! This is the same as setting a nameserver.
   // this depends on the constructor call. i.e. in the constructor
   // If MXLookup is true this is a nameserver
   // If MXLookup is false this is an smtp server
   //mail.setserver("mail.somewherefun.com");
   // same again except using an IP address instead.
   //mail.setserver("192.168.0.1");

   // boost::thread thrd(mail);
   // thrd.join(); // optional
   // or:-

   // Use authentication
   //mail.username("testuser");
   //mail.password("secret");
   // LOGIN authentication by default
   // if you want plain as opposed to login authentication
   //mail.authtype(jwsmtp::mailer::PLAIN);

   // mail.send();
   mail.operator()();
   cout << mail.response() << "\n";

   //mail.reset(); // now we can mail someone else.
   //mail.setmessage("flibbletooting");
   //mail.setsubject("another message same object");
   //mail.attach("/home/user1/image.gif");
   // or a win example
   //mail.attach("C:\\image.gif");
   //mail.addrecipient("someoneelseagain@foobar.net");

   //mail.operator ()();
   //cout << mail.response() << "\n";
   return 0;
}
