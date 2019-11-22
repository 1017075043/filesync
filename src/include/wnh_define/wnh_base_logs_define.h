//日志输出定义

#ifndef __wnh_base_logs_define__
#define __wnh_base_logs_define__

//日志模式
#define WNH_LOGS_MODE_N        0        //不产生日志
#define WNH_LOGS_MODE_S        1        //在前端显示日志输出
#define WNH_LOGS_MODE_XS       2        //不带文件名,方法 ,行数的信息,在前端显示日志输出
#define WNH_LOGS_MODE_W        3        //不在前端显示日志输出,直接将日志写入日志文件
#define WNH_LOGS_MODE_XW       4        //不带文件名,方法 ,行数的信息,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_LOGS_MODE_SW       5        //在前端显示日志输出,并将日志写入日志文件
#define WNH_LOGS_MODE_XSW      6        //不带文件名,方法 ,行数的信息,在前端显示日志输出,并将日志写入日志文件

//日志等级设置
#define WNH_DEBUG_S            0        //LOGLEVEL=WNH_DEBUG_S         以调试级别输出日志,在前端显示日志输出
#define WNH_INFO_S             1        //LOGLEVEL=WNH_INFO_S          以信息级别输出日志,在前端显示日志输出
#define WNH_WARN_S             2        //LOGLEVEL=WNH_WARN_S          以警告级别输出日志,在前端显示日志输出
#define WNH_ERROR_S            3        //LOGLEVEL=WNH_ERROR_S         以错误级别输出日志,在前端显示日志输出
#define WNH_DEBUG_XS           4        //LOGLEVEL=WNH_DEBUG_XS        以调试级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出
#define WNH_INFO_XS            5        //LOGLEVEL=WNH_INFO_XS         以信息级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出
#define WNH_WARN_XS            6        //LOGLEVEL=WNH_WARN_XS         以警告级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出
#define WNH_ERROR_XS           7        //LOGLEVEL=WNH_ERROR_XS        以错误级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出

#define WNH_DEBUG_W            8        //LOGLEVEL=WNH_DEBUG_W         以调试级别输出日志,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_INFO_W             9        //LOGLEVEL=WNH_INFO_W          以信息级别输出日志,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_WARN_W            10        //LOGLEVEL=WNH_WARN_W          以警告级别输出日志,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_ERROR_W           11        //LOGLEVEL=WNH_ERROR_W         以错误级别输出日志,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_DEBUG_XW          12        //LOGLEVEL=WNH_DEBUG_XW        以调试级别输出日志,不带文件名,方法 ,行数的信息,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_INFO_XW           13        //LOGLEVEL=WNH_INFO_XW         以信息级别输出日志,不带文件名,方法 ,行数的信息,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_WARN_XW           14        //LOGLEVEL=WNH_WARN_XW         以警告级别输出日志,不带文件名,方法 ,行数的信息,不在前端显示日志输出,直接将日志写入日志文件
#define WNH_ERROR_XW          15        //LOGLEVEL=WNH_ERROR_XW        以错误级别输出日志,不带文件名,方法 ,行数的信息,不在前端显示日志输出,直接将日志写入日志文件

#define WNH_DEBUG_SW          16        //LOGLEVEL=WNH_DEBUG_SW        以调试级别输出日志,在前端显示日志输出,并将日志写入日志文件
#define WNH_INFO_SW           17        //LOGLEVEL=WNH_INFO_SW         以信息级别输出日志,在前端显示日志输出,并将日志写入日志文件
#define WNH_WARN_SW           18        //LOGLEVEL=WNH_WARN_SW         以警告级别输出日志,在前端显示日志输出,并将日志写入日志文件
#define WNH_ERROR_SW          19        //LOGLEVEL=WNH_ERROR_SW        以错误级别输出日志,在前端显示日志输出,并将日志写入日志文件
#define WNH_DEBUG_XSW         20        //LOGLEVEL=WNH_DEBUG_XSW       以调试级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出,并将日志写入日志文件
#define WNH_INFO_XSW          21        //LOGLEVEL=WNH_INFO_XSW        以信息级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出,并将日志写入日志文件
#define WNH_WARN_XSW          22        //LOGLEVEL=WNH_WARN_XSW        以警告级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出,并将日志写入日志文件
#define WNH_ERROR_XSW         23        //LOGLEVEL=WNH_ERROR_XSW       以错误级别输出日志,不带文件名,方法 ,行数的信息,在前端显示日志输出,并将日志写入日志文件


//20191104
//加入编译日志模式宏,精简代码量
//去除不在前端显示日志输出,直接将日志写入日志文件模式,精简代码量
//去除在前端显示日志输出,并将日志写入日志文件模式,精简代码量
//以调试级别输出日志
#if defined(DEBUG_MODE_LOGS)
	#if defined(SOMPLE_LOGS)
		#define WNHDEBUG(...) \
		{ \
			switch(LOGLEVELSWITCH[0]) \
			{ \
				case WNH_LOGS_MODE_S: \
					LOGS_MUTEX_LOCK.lock(); \
					cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
					break; \
				case WNH_LOGS_MODE_XS: \
					LOGS_MUTEX_LOCK.lock(); \
					cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
					break; \
			} \
		}
	#else
		#define WNHDEBUG(...) \
		{ \
			switch(LOGLEVELSWITCH[0]) \
			{ \
				case WNH_LOGS_MODE_S: \
					LOGS_MUTEX_LOCK.lock(); \
					cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
					break; \
				case WNH_LOGS_MODE_XS: \
					LOGS_MUTEX_LOCK.lock(); \
					cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
					break; \
				case WNH_LOGS_MODE_W: \
					LOGS_MUTEX_LOCK.lock(); \
					WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
					break; \
				case WNH_LOGS_MODE_XW: \
					LOGS_MUTEX_LOCK.lock(); \
					WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
					break; \
				case WNH_LOGS_MODE_SW: \
					LOGS_MUTEX_LOCK.lock(); \
					cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
					break; \
				case WNH_LOGS_MODE_XSW: \
					LOGS_MUTEX_LOCK.lock(); \
					cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
					LOGS_MUTEX_LOCK.unlock(); \
				break; \
			} \
		}
	#endif
#else
	#define WNHDEBUG(...) //WNHDEBUG(...)
#endif
//以信息级别输出日志
#if defined(SOMPLE_LOGS)
    #define WNHINFO(...) \
    { \
        switch(LOGLEVELSWITCH[1]) \
        { \
            case WNH_LOGS_MODE_S: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XS: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
        } \
    }
#else
    #define WNHINFO(...) \
    { \
        switch(LOGLEVELSWITCH[1]) \
        { \
            case WNH_LOGS_MODE_S: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XS: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_W: \
                LOGS_MUTEX_LOCK.lock(); \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XW: \
                LOGS_MUTEX_LOCK.lock(); \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_SW: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XSW: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
        } \
    }
#endif
//以警告级别输出日志
#if defined(SOMPLE_LOGS)
    #define WNHWARN(...) \
    { \
        switch(LOGLEVELSWITCH[2]) \
        { \
            case WNH_LOGS_MODE_S: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XS: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
        } \
    }
#else
    #define WNHWARN(...) \
    { \
        switch(LOGLEVELSWITCH[2]) \
        { \
            case WNH_LOGS_MODE_S: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XS: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_W: \
                LOGS_MUTEX_LOCK.lock(); \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XW: \
                LOGS_MUTEX_LOCK.lock(); \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_SW: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XSW: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            } \
    }
#endif
//以错误级别输出日志
#if defined(SOMPLE_LOGS)
#define WNHERROR(...) \
{ \
    switch(LOGLEVELSWITCH[3]) \
    { \
        case WNH_LOGS_MODE_S: \
            LOGS_MUTEX_LOCK.lock(); \
            cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
            LOGS_MUTEX_LOCK.unlock(); \
            break; \
        case WNH_LOGS_MODE_XS: \
            LOGS_MUTEX_LOCK.lock(); \
            cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
            LOGS_MUTEX_LOCK.unlock(); \
            break; \
    } \
}
#else
    #define WNHERROR(...) \
    { \
        switch(LOGLEVELSWITCH[3]) \
        { \
            case WNH_LOGS_MODE_S: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XS: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_W: \
                LOGS_MUTEX_LOCK.lock(); \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XW: \
                LOGS_MUTEX_LOCK.lock(); \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_SW: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
            case WNH_LOGS_MODE_XSW: \
                LOGS_MUTEX_LOCK.lock(); \
                cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \
                LOGS_MUTEX_LOCK.unlock(); \
                break; \
        } \
    }
#endif

#endif

//20191004
//加入shell输出颜色,使用彩色的显示日志,取消将日志写入日志文件操作
//以调试级别输出日志
/*  #define WNHDEBUG(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[0]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \            */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                            */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \            */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_GREEN << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                            */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*          break; \                                                                                                                                                                                        */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*  //以信息级别输出日志                                                                                                                                                                                    */
/*  #define WNHINFO(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[1]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \             */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                             */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \             */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_WHITE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                             */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*  //以警告级别输出日志                                                                                                                                                                                    */
/*  #define WNHWARN(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[2]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \            */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                            */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \            */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_YELLOW << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                            */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                       */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          } \                                                                                                                                                                                             */
/*  }                                                                                                                                                                                                       */
/*  //以错误级别输出日志                                                                                                                                                                                    */
/*  #define WNHERROR(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[3]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \              */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                              */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \              */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << WNH_COLOR_RED << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                              */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << WNH_COLOR_WHITE << endl; \                                                                                      */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */

//20190614
//加入互斥信号量来处理使用多线程的时候，日志打印出现混乱的现象
//以调试级别输出日志
/*  #define WNHDEBUG(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[0]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                  */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                  */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*          break; \                                                                                                                                                                                        */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*  //以信息级别输出日志                                                                                                                                                                                    */
/*  #define WNHINFO(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[1]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                   */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*  //以警告级别输出日志                                                                                                                                                                                    */
/*  #define WNHWARN(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[2]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                   */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          } \                                                                                                                                                                                             */
/*  }                                                                                                                                                                                                       */
/*  //以错误级别输出日志                                                                                                                                                                                    */
/*  #define WNHERROR(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[3]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                  */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                                  */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              LOGS_MUTEX_LOCK.lock(); \                                                                                                                                                                   */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              LOGS_MUTEX_LOCK.unlock(); \                                                                                                                                                                 */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*                                                                                                                                                                                                          */
/*  //20190622                                                                                                                                                                                              */
/*  //以调试级别输出日志                                                                                                                                                                                    */
/*  #define WNHDEBUG(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[0]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                             */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                    */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                             */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                    */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*  //以信息级别输出日志                                                                                                                                                                                    */
/*  #define WNHINFO(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[1]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                              */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                     */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                              */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                     */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              cout << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*  //以警告级别输出日志                                                                                                                                                                                    */
/*  #define WNHWARN(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[2]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                              */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                     */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                              */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                     */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              cout << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                   */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                          */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*  //以错误级别输出日志                                                                                                                                                                                    */
/*  #define WNHERROR(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      switch(LOGLEVELSWITCH[3]) \                                                                                                                                                                         */
/*      { \                                                                                                                                                                                                 */
/*          case WNH_LOGS_MODE_S: \                                                                                                                                                                         */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                             */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XS: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_W: \                                                                                                                                                                         */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                    */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XW: \                                                                                                                                                                        */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_SW: \                                                                                                                                                                        */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << getpid() << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                             */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << getpid() << "]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl; \                    */
/*              break; \                                                                                                                                                                                    */
/*          case WNH_LOGS_MODE_XSW: \                                                                                                                                                                       */
/*              cout << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                                  */
/*              WNH_LOGS_FILE << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl; \                                                                                                         */
/*              break; \                                                                                                                                                                                    */
/*      } \                                                                                                                                                                                                 */
/*  }                                                                                                                                                                                                       */
/*                                                                                                                                                                                                          */
/*                                                                                                                                                                                                          */
/*  //extern bool LOGLEVELSWITCH[8];                                                                                                                                                                        */
/*  //以调试级别输出日志                                                                                                                                                                                    */
/*  #define WNHDEBUG(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVELSWITCH[debug]){cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                               */
/*      else if(LOGLEVELSWITCH[debug_x]){cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                        */
/*  }                                                                                                                                                                                                       */
/*  //以信息级别输出日志                                                                                                                                                                                    */
/*  #define WNHINFO(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVELSWITCH[info]){cout << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                                 */
/*      else if(LOGLEVELSWITCH[info_x]){cout << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                          */
/*  }                                                                                                                                                                                                       */
/*  //以警告级别输出日志                                                                                                                                                                                    */
/*  #define WNHWARN(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVELSWITCH[warn]){cout << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                                 */
/*      else if(LOGLEVELSWITCH[warn_x]){cout << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                          */
/*  }                                                                                                                                                                                                       */
/*  //以错误级别输出日志                                                                                                                                                                                    */
/*  #define WNHERROR(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVELSWITCH[error]){cout << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                               */
/*      else if(LOGLEVELSWITCH[error_x]){cout << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                        */
/*  }                                                                                                                                                                                                       */
/*                                                                                                                                                                                                          */
/*  //调试日志的输出--20190421                                                                                                                                                                              */
/*  //以调试级别输出日志                                                                                                                                                                                    */
/*  #define WNHDEBUG(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVEL > 3 && LOGLEVEL <= 4){cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                       */
/*      else if(LOGLEVEL <= 0){cout << "[" << LOCALTIME << "]-[DEBUG]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                                  */
/*  }                                                                                                                                                                                                       */
/*  //以信息级别输出日志                                                                                                                                                                                    */
/*  #define WNHDEBUG(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVEL > 3 && LOGLEVEL <= 5){cout << "[" << LOCALTIME << "]-[INFO]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                        */
/*      else if(LOGLEVEL <= 1){cout << "[" << LOCALTIME << "]-[INFO]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                                   */
/*  }                                                                                                                                                                                                       */
/*  //以警告级别输出日志                                                                                                                                                                                    */
/*  #define WNHWARN(...) \                                                                                                                                                                                  */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVEL > 3 && LOGLEVEL <= 6){cout << "[" << LOCALTIME << "]-[WARN]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                        */
/*      else if(LOGLEVEL <= 2){cout << "[" << LOCALTIME << "]-[WARN]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                                   */
/*  }                                                                                                                                                                                                       */
/*  //以错误级别输出日志                                                                                                                                                                                    */
/*  #define WNHERROR(...) \                                                                                                                                                                                 */
/*  { \                                                                                                                                                                                                     */
/*      if(LOGLEVEL > 3 && LOGLEVEL <= 7){cout << "[" << LOCALTIME << "]-[ERROR]-[" << __VA_ARGS__ << "]" << endl;} \                                                                                       */
/*      else if(LOGLEVEL <= 3){cout << "[" << LOCALTIME << "]-[ERROR]-[" << __FILE__ << "]-[" << __func__ << "]-[" << __LINE__ << "]--[" << __VA_ARGS__ << "]" << endl;} \                                  */
/*  }                                                                                                                                                                                                       */
