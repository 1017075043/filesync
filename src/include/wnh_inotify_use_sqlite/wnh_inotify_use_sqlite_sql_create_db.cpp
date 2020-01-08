#include "wnh_inotify_use_sqlite.h"

bool wnh_inotify_use_sqlite::watch_list_create_db()//创建一个数据进行数据存储
{
    WNHINFO("使用数据库" << DB_NAME << "来进行数据存储");
    return sqlite_op.create_db(DB_NAME);//创建一个数据库
}
