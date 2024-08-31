/**
 * 求二叉树的深度和宽度
 * 给定一个二叉树，获取该二叉树的宽度和深度。
 *
 * 例如输入
 *    a
 *   / \
 *  b   c
 * / \   / \
 * d e  f  g
 *
 * 返回3.
 * 详细描述：
 * 接口说明
 * 原型：
 * int GetBiNodeInfo(BiNode &head, unsigned int *pulWidth, unsigned int *pulHeight)
 * 输入参数：
 * head   需要获取深度的二叉树头结点
 * 输出参数（指针指向的内存区域保证有效）：
 * pulWidth   宽度
 * pulHeight  高度
 * 返回值：
 * 0          成功
 * 1          失败或其他异常
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct tagBiNode
{
    char             data;
    struct tagBiNode *left;
    struct tagBiNode *right;
} BiNode;

/*
Description
给定一个二叉树，获取该二叉树的宽度深度。
Prototype
int GetBiNodeInfo(BiNode &head, unsigned int *pulWidth, unsigned int *pulHeight)
Input Param
head   需要获取深度的二叉树头结点
Output Param
pulWidth   宽度
pulHeight  高度
Return Value
0          成功
1          失败或其他异常
*/
struct BiNodeInfo {
    int width;
    int height;
};
BiNodeInfo getBiNodeInfo(BiNode* head) {
    /* 在这里实现功能 */
    BiNodeInfo biNodeInfo;
    if (head == NULL) {
        biNodeInfo.width = 0;
        biNodeInfo.height = 0;
    } else {
        int left_height, right_height;
        if ((head->left == NULL) && (head->right == NULL)) {
            biNodeInfo.width = 1;
        } else {
            biNodeInfo.width = getBiNodeInfo(head->left).width
                               + getBiNodeInfo(head->right).width;
        }

        left_height = getBiNodeInfo(head->left).height;
        right_height = getBiNodeInfo(head->right).height;
        biNodeInfo.height = (left_height > right_height) ? (1 + left_height)
                                                         : (1 + right_height);
    }

    return biNodeInfo;
}

int GetBiNodeInfo(BiNode &head, unsigned int *pulWidth, unsigned int *pulHeight)
{
    /*在这里实现功能*/
    if (&head == NULL)
    {
        *pulWidth = 0;
        *pulHeight = 0;
        return -1;
    }
    *pulWidth = getBiNodeInfo(&head).width;
    *pulHeight = getBiNodeInfo(&head).height;
    return 0;
}

int main()
{
    char result[128] = {0};
    BiNode dataa = {'a', NULL, NULL};
    BiNode datab = {'b', NULL, NULL};
    BiNode datac = {'c', NULL, NULL};
    BiNode datad = {'d', NULL, NULL};
    BiNode datae = {'e', NULL, NULL};
    BiNode dataf = {'f', NULL, NULL};
    BiNode datag = {'g', NULL, NULL};
    BiNode datah = {'h', NULL, NULL};
    BiNode datai = {'i', NULL, NULL};
    BiNode dataj = {'j', NULL, NULL};
    BiNode datak = {'k', NULL, NULL};
    BiNode datal = {'l', NULL, NULL};
    BiNode datam = {'m', NULL, NULL};
    BiNode datan = {'n', NULL, NULL};
    BiNode datao = {'o', NULL, NULL};
    BiNode datap = {'p', NULL, NULL};

    dataa.left = &datab;
    dataa.right = &datac;
    datab.left = &datad;
    datab.right = &datae;
    datac.left = &dataf;
    datac.right = &datag;
    datad.left = &datah;
    datad.right = &datai;
    datae.left = &dataj;
    datae.right = &datak;
    dataf.left = &datal;
    dataf.right = &datam;
    datag.left = &datan;
    datag.right = &datao;
    datah.left = &datap;

    unsigned int ulWidth = 0;
    unsigned int ulHeight = 0;
    std::cout << (GetBiNodeInfo(dataa, &ulWidth, &ulHeight) == 0) << std::endl;
    std::cout << (ulWidth == 8) << std::endl;
    std::cout << (ulHeight == 5) << std::endl;
}

