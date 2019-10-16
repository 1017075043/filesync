#include "wnh_license.h"

bool wnh_license::get_cpu_id_by_asm(string & cpu_id) //从asm中获取cpu信息
{
    WNHINFO("2");
    cpu_id.clear();

    unsigned int s1 = 0;
    unsigned int s2 = 0;
    asm volatile
            (
                "movl $0x01, %%eax; \n\t"
                "xorl %%edx, %%edx; \n\t"
                "cpuid; \n\t"
                "movl %%edx, %0; \n\t"
                "movl %%eax, %1; \n\t"
                : "=m"(s1), "=m"(s2)
                );
    WNHINFO("3");
    if (0 == s1 && 0 == s2)
    {
        return(false);
    }
    WNHINFO("4");
    char cpu[32] = { 0 };
    snprintf(cpu, sizeof(cpu), "%08X%08X", htonl(s2), htonl(s1));
    string(cpu).swap(cpu_id);
    WNHINFO("5");
    return(true);
}

void wnh_license::parse_cpu_id(const char * file_name, const char * match_words, string & cpu_id) //解析cpu信息
{
    cpu_id.c_str();

    std::ifstream ifs(file_name, std::ios::binary);
    if (!ifs.is_open())
    {
        return;
    }

    char line[4096] = { 0 };
    while (!ifs.eof())
    {
        ifs.getline(line, sizeof(line));
        if (!ifs.good())
        {
            break;
        }

        const char * cpu = strstr(line, match_words);
        if (NULL == cpu)
        {
            continue;
        }
        cpu += strlen(match_words);

        while ('\0' != cpu[0])
        {
            if (' ' != cpu[0])
            {
                cpu_id.push_back(cpu[0]);
            }
            ++cpu;
        }

        if (!cpu_id.empty())
        {
            break;
        }
    }

    ifs.close();
}

bool wnh_license::get_cpu_id_by_system(string & cpu_id) //从系统中获取cpu信息
{
    cpu_id.c_str();
    WNHINFO("6");
    const char * dmidecode_result = ".dmidecode_result.txt";
    char command[512] = { 0 };
    snprintf(command, sizeof(command), "dmidecode -t 4 | grep ID > %s", dmidecode_result);
    WNHINFO("7");
    if (0 == system(command))
    {
        parse_cpu_id(dmidecode_result, "ID:", cpu_id);
    }
    WNHINFO("8");
    unlink(dmidecode_result);
    WNHINFO("9");
    return(!cpu_id.empty());
}

bool wnh_license::get_cpu_id(string & cpu_id) //获取cpu信息
{
    if (get_cpu_id_by_asm(cpu_id))
    {
        return(true);
    }
    if (0 == getuid())
    {
        if (get_cpu_id_by_system(cpu_id))
        {
            return(true);
        }
    }
    return(false);
}

string wnh_license::get_cpu_id() //获取cpu信息
{
    string cpu_id;
    WNHINFO("1");
    if (get_cpu_id_by_asm(cpu_id))
    {
        WNHINFO("cpu_id=" << cpu_id);
        return cpu_id;
    }
    if (0 == getuid())
    {
        if (get_cpu_id_by_system(cpu_id))
        {
            WNHINFO("cpu_id=" << cpu_id);
            return cpu_id;
        }
    }
    WNHINFO("10");
    WNHINFO("cpu_id=" << cpu_id);
    return cpu_id;
}
