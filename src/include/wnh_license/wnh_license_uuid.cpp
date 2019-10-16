#include "wnh_license.h"

string wnh_license::get_uuid() //获取uuid
{
    int i,n;
    uuid_t uu[4];
    char buf[1024];
    struct timeval tv;
    //1、
    uuid_generate(uu[0]);
    //2、
    uuid_generate_random(uu[1]);
    //3、
    uuid_generate_time(uu[2]);
    //4、
    n = uuid_generate_time_safe(uu[3]);
    printf("n = %d\n",n);
    for(i=0;i<4;++i){
        uuid_unparse(uu[i],buf);
        printf("uu[%d]\t\t%s\n",i,buf);
    }

    uuid_time(uu[2],&tv);
    printf("tv s:%lx  u:%lx\n",tv.tv_sec,tv.tv_usec);

    return "";
}
