2020年01月08日
升级版本为filesync-v1.1.2
更新内容
1.优化失败任务列表信息查看功能
2.处理wnh_tables类循环显示子行的时候数据重复的问题

2020年01月06日
升级版本为filesync-v1.1.1
更新内容
1.完成失败任务列表信息查看功能,实现了可以分页查询的功能
2.wnh_base添加get_keyboard_input_string方法,获取键盘任意键的输入,以字符串的形式返回
3.使用wnh_tables类添加get_display_line_num方法,获取显示的行数

2019年12月30日
升级版本为filesync-v1.1.0
更新内容
1.优化监控目录和忽略同步目录的添加顺序,在添加监控目录的时候,直接判断是否属于忽略同步目录,是的话就直接忽略掉,避免出现先添加在删除的情况下文件描述符使用完的情况

2019年12月30日
升级版本为filesync-v1.0.9
更新内容
1.添加wnh_config_ini_ex类,优化配置文件的读取方式,将读取结果直接存放于vector<vector <string> >中
2.wnh_base添加get_uuid方法.生成32位的uuid
3.优化wnu_tables类,丰富字体显示格式

2019年12月13日
升级版本为filesync-v1.0.8
更新内容
1.优化程序,处理有时候有突然卡住的问题
2.使用wnh_tables类进行控制端表格显示

2019年11月20日
升级版本为filesync-v1.0.7
更新内容
1.添加使用命令行参数传参启动方式
例如:
filesync server --conf=filesync.conf --pid=filesync_server.pid --limit="limit root" --log=WNH_INFO_XS
filesync client --ip=127.0.0.1 --port=10086 --pid=filesync_server.pid --limit="limit root" --log=WNH_INFO_XS
filesync control 1 --ip=127.0.0.1 --port=10086 --log=WNH_INFO_XS

2019年11月18日
升级版本为filesync-v1.0.6
更新内容
1.添加使用license模式,支持使用 filesync license filesync.license 命令查看许可文件信息
2.添加control模式下查看服务器许可功能, filesync control 10
3.优化客户端离线邮件告警内容

2019年11月06日
升级版本为filesync-v1.0.5
更新内容
1.添加通用许可功能
2.优化数据传输过程

2019年11月06日
升级版本为filesync-v1.0.4
更新内容
1.处理可能由于uuid导致获取产品序列号有变动的导致许可经常用不了的问题
2.处理现实产品序列号异常的bug

2019年11月03日
升级版本为filesync-v1.0.3
更新内容
1.添加客户端可以连接多个服务端的模式,可以更好的支持文件实时备份,(若想要连接多个可以端,在配置文件中添加如下内容)
[client_configure]
server_ip_port=192.168.60.130:10086
启动方式为filesync client filesync.conf
2.程序还向下兼容,支持在命令行直接传参连接单个服务端的模式
3.修改control模式下的使用说明和环境变量使用说明

2019年11月01日
升级版本为filesync-v1.0.2
更新内容
1.优化control的使用模式,去除默认root用户启动限制和pid限制。
2.处理个别临时目录创建后由于权限问题，导致的临时文件无法写入。

2019年10月31日
升级版本为filesync-v1.0.1
更新内容
处理由于wnh_config_ini类析时出现段错误的问题。

2019年10月15日
发布filesync-v1.0.0版本
开发完成,版本发布。
