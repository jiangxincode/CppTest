#include <stdlib.h>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "../source/OJ.h"
#include "CommonDef.h"

using namespace std;

vector<pair<TaskID, TaskStatus>> vec_ATask;
vector<pair<TaskID, TaskStatus>> vec_BTask;
vector<pair<TaskID, TaskStatus>> vec_CTask;

// 功能：初始化任务管理器
// 输入：无
// 输出：无         
// 返回：无
void initialize()
{
    vec_ATask.clear();
    vec_BTask.clear();
    vec_CTask.clear();
}

// 功能：清空任务管理器中的任务队列
// 输入：无
// 输出：无         
// 返回：无
void finitialize()
{
    vec_ATask.clear();
    vec_BTask.clear();
    vec_CTask.clear();
}

// 功能：操作任务，可以增加、运行、删除、强制删除、清除任务。
// 输入：TaskType type: 任务类型
//       TaskID id    : 任务ID，唯一标识任务
//       OperateType opType : 任务操作类型
// 输出：无         
// 返回：操作成功返回true，失败返回false
bool OperateTask (TaskType type, TaskID id, OperateType opType)
{
	if (opType == AddTask)
	{
        if (type == ATask)
        {
            if (vec_ATask.size() >= 100)
            {
                return false;
            }
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (p.first == id)
                {
                    return false;
                }
            }
            pair<TaskID, TaskStatus> p(id, Waiting);
            vec_ATask.push_back(p);
        }
        else if (type == BTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_BTask.begin();it!=vec_BTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (p.first == id)
                {
                    return false;
                }
            }
            pair<TaskID, TaskStatus> p(id, Waiting);
            vec_BTask.push_back(p);
        }
        else if (type == CTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_CTask.begin();it!=vec_CTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (p.first == id)
                {
                    return false;
                }
            }
            pair<TaskID, TaskStatus> p(id, Waiting);
            vec_CTask.push_back(p);
        }
        else
        {
            return false;
        }
	}
    else if (opType == RunTask)
    {
        if (type == ATask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    if ((*it).second == Waiting)
                    {
                        (*it).second = Finished;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return false;
        }
        else if (type == BTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_BTask.begin();it!=vec_BTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    if ((*it).second == Waiting)
                    {
                        (*it).second = Finished;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return false;
        }
        else if (type == CTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_CTask.begin();it!=vec_CTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    if ((*it).second == Waiting)
                    {
                        (*it).second = Finished;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }
    else if (opType == DelTask)
    {
        if (type == ATask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    if ((*it).second == Finished)
                    {
                        vec_ATask.erase(it);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return false;
        }
        else if (type == BTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_BTask.begin();it!=vec_BTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    if ((*it).second == Finished)
                    {
                        vec_BTask.erase(it);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return false;
        }
        else if (type == CTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_CTask.begin();it!=vec_CTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    if ((*it).second == Finished)
                    {
                        vec_CTask.erase(it);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }
    else if (opType == DelForceTask)
    {
        if (type == ATask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    vec_ATask.erase(it);
                    return true;
                }
            }
            return false;
        }
        else if (type == BTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_BTask.begin();it!=vec_BTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    vec_ATask.erase(it);
                    return true;
                }
            }
            return false;
        }
        else if (type == CTask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_CTask.begin();it!=vec_CTask.end();++it)
            {
                pair<TaskID, TaskStatus> p = *it;
                if (id == (*it).first)
                {
                    vec_ATask.erase(it);
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }
    else if (opType == ClearTask)
    {
        if (type == ATask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
            {
                if ((*it).second != Finished)
                {
                    return false;
                }
            }
            vec_ATask.clear();
            return true;
        }
        else if (type == ATask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
            {
                if ((*it).second != Finished)
                {
                    return false;
                }
            }
            vec_ATask.clear();
            return true;
        }
        else if (type == ATask)
        {
            for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
            {
                if ((*it).second != Finished)
                {
                    return false;
                }
            }
            vec_ATask.clear();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// 功能：获取Task当前状态
// 输入：TaskID id：查找的任务ID号
// 输出：TaskStatus &status：当前任务的状态
// 返回：无
void GetTaskStatus(TaskID id, TaskStatus &status)
{
    for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_ATask.begin();it!=vec_ATask.end();++it)
    {
        if ((*it).first == id)
        {
            status = (*it).second;
            return;
        }
    }
    for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_BTask.begin();it!=vec_BTask.end();++it)
    {
        if ((*it).first == id)
        {
            status = (*it).second;
            return;
        }
    }
    for (vector<pair<TaskID, TaskStatus>>::iterator it=vec_CTask.begin();it!=vec_CTask.end();++it)
    {
        if ((*it).first == id)
        {
            status = (*it).second;
            return;
        }
    }
    status = NotExist;
    
}




