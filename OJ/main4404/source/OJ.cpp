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

// ���ܣ���ʼ�����������
// ���룺��
// �������         
// ���أ���
void initialize()
{
    vec_ATask.clear();
    vec_BTask.clear();
    vec_CTask.clear();
}

// ���ܣ��������������е��������
// ���룺��
// �������         
// ���أ���
void finitialize()
{
    vec_ATask.clear();
    vec_BTask.clear();
    vec_CTask.clear();
}

// ���ܣ��������񣬿������ӡ����С�ɾ����ǿ��ɾ�����������
// ���룺TaskType type: ��������
//       TaskID id    : ����ID��Ψһ��ʶ����
//       OperateType opType : �����������
// �������         
// ���أ������ɹ�����true��ʧ�ܷ���false
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

// ���ܣ���ȡTask��ǰ״̬
// ���룺TaskID id�����ҵ�����ID��
// �����TaskStatus &status����ǰ�����״̬
// ���أ���
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




