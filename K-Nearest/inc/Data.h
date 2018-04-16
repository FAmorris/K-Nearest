#ifndef __DATA_H
#define __DATA_H

#ifdef __cplusplus
extern "C" {
#endif
#include "UserType.h"

typedef struct{
	d64 **samPtrs;	 /* 训练样本存储二维数组指针	*/
	d64 **tSamPtrs;/* 测试样本存储二维数组指针	 */
	i32 *aimPtr; /* 训练样本目标输出存储数组指针*/
	i32 *tAimPtr;	/* 测试样本目标输出存储数组指针*/

	i32 numOfSample;/* 训练样本总数 */
	i32 numOfTSample; /* 测试样本总数 */
	i32 numOfInput;	/* 输入向量维数*/
	i32 numOfClasses;
	i32 samParmLabel;/* 参数已设置标志 */
	i32 creatLabel;
	i32 TrainDataEntered;
	i32 TestDataEntered;
}DT_TypeDef, *DT_TypeDefPtr;/* 样本数据存储结构体变量和结构体指针 */

void DT_DatasCreat(DT_TypeDefPtr dPtr);/* 创建数据存储数组函数 */
void DT_InputTrainSamples( DT_TypeDefPtr dPtr );/* 输入训练样本数据函数 */
void DT_InputTestSamples( DT_TypeDefPtr dPtr );/* 输入测试样本数据函数 */
void DT_DatasInit( DT_TypeDefPtr  dPtr );/* 存储数组初始化函数*/
void DT_DatasDeInit( DT_TypeDefPtr dPtr );/* 释放数组所占内存函数*/
void DT_PrintTrainSamples( DT_TypeDefPtr dPtr );/* 显示训练样本函数*/
void DT_PrintTestSamples( DT_TypeDefPtr dPtr );/* 显示测试样本函数 */
void DT_SetSampleParameters( DT_TypeDefPtr dPtr );/* 设置样本参数	函数*/
void printDatasParams( DT_TypeDefPtr dPtr );/* 显示样本存储结构参数函数 */
void DT_sorftSampleSequence( DT_TypeDefPtr dPtr, i32 *sPtr, i32 num1, i32 num2 );

#ifdef __cplusplus
}
#endif

#endif /* __DATA_H */

/********************************************************** END OF HEARD FILE ***************************************************************/