#ifndef __OJ_H__
#define __OJ_H__
#include "CommonDef.h"

void initialize();
bool OperateTask (TaskType type, TaskID id, OperateType opType);
void GetTaskStatus(TaskID id, TaskStatus &status);
void finitialize();
#endif
