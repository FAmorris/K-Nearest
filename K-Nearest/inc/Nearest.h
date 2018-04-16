#ifndef __NEAREST_H
#define __NEAREST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Data.h"
#include "UserType.h"

#define		KNN_STACK_SIZE									100 /* 栈大小 */

typedef struct tNode{
	  i32 dimention; /* 节点数据排序维度 */
	  i32 index; /* 切分点数据索引 */
	  struct tNode *leftChildPtr; /* 左子节点 */
	  struct tNode *rightChildPtr; /* 右子节点 */
}KNN_NdTypeDef, /* 节点结构体*/
*KNN_NdTypeDefPtr; /* 节点结构体指针 */

typedef struct{
	  i32 deep; /* 当前节点所在深度 */
	  i32 samSurplus; /* 生成树时节点对应样本数据个数 */
	  i32 *sPtr; /* 生成树时对应样本索引数组 */
}KNN_NdPrmTypeDef, /* 生成结点所需参数结构体 */
*KNN_NdPrmTypeDefPtr; /* 生成结点所需参数结构体指针 */

typedef struct{
	  i32 tail; /* 栈底 */
	  i32 top;/* 栈顶 */
	  KNN_NdTypeDefPtr kStkPtrs[ KNN_STACK_SIZE ]; /* 栈， 用于存储叶节点搜索路径 */
}KNN_StkTypeDef, /* 栈结构体 */
*KNN_StkTypeDefPtr;/* 栈结构体指针 */

typedef struct {
	i32 kTimes; /* 当前搜索次数 */
	i32 *knnIndexPtr; /* k个最近邻索引数组 */
	d64 *inPtr; /* 输入数据 */
	d64 dist; /* 当前最近距离 */
	KNN_StkTypeDef KNN_Stack; /* 栈 */
}KNN_PrmTypeDef, /* 算法参数结构体变量 */
*KNN_PrmTypdeDefPtr; /* 算法参数结构体指针 */

typedef struct{
	  i32 k; /* k个近邻 */
	  i32 treeLabel;
	  KNN_PrmTypeDef parameters; /* 算法参数 */
	  KNN_NdTypeDefPtr rootPtr; /* k-d 树根节点 */
}KNN_TypeDef, /* 算法结构体 */
*KNN_TypeDefPtr; /* 算法结构体指针 */

void KNN_NearestInit( KNN_TypeDefPtr nPtr );
void KNN_NearestCreat( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr );
void KNN_SearchKNearest( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr );
void KNN_TestModelPerformence( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr );
void KNN_LinnerScan( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr );
void KNN_SetKNNParameters( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr );
void KNN_InputData( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr);
void KNN_PrintConmand( i32 *chose );
void KNN_printData( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr );
i32 KNN_ClassifyInputData( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr );

#ifdef __cplusplus
}
#endif

#endif /* __NEAREST_H */

/********************************************************** END OF HEARD FILE ***************************************************************/