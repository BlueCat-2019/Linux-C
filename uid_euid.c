#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
/* 一个进程有两个用户ID, UID和EUID. EUID存在的目的是方便资源的访问
 * 它使得运行程序的用户拥有该程序的有效有户权限。*/

int main(int argc, char* argv[])
{
    /* 获取用户UID */
    uid_t uid = getuid();
    /* 获取用户EUID */
    uid_t euid = geteuid();
    printf("User ID: %d, effective User ID: %d\n",
                uid, euid);
    return 0;
}


/* 将以root用户起动的进程切换为一个普通用户身份运行 */
static bool switch_to_user(uid_t user_id, gid_t group_id)
{
    /* 先确保目标用户不是root */
    if(user_id == 0 && group_id == 0)
        return false;
    /* 确保当前用户是合法的用户: root 或者 目标用户 */
    gid_t gid = getgid();
    uid_t uid = getuid();
    if(((gid != 0) || uid != 0) && (gid != group_id) || (uid != user_id)))
        return false;

    /* 如果不是root, 则已经是普通用户了 */
    if(uid != 0)
        return false;
    /* 切换到目标用户 */
    if((setgid(group_id) < 0) || (setuid(user_id) < 0))
        return false;
    
    return true;
}