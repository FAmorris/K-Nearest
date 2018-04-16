#ifndef __NEAREST_H
#define __NEAREST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Data.h"
#include "UserType.h"

#define		KNN_STACK_SIZE									100 /* ջ��С */

typedef struct tNode{
	  i32 dimention; /* �ڵ���������ά�� */
	  i32 index; /* �зֵ��������� */
	  struct tNode *leftChildPtr; /* ���ӽڵ� */
	  struct tNode *rightChildPtr; /* ���ӽڵ� */
}KNN_NdTypeDef, /* �ڵ�ṹ��*/
*KNN_NdTypeDefPtr; /* �ڵ�ṹ��ָ�� */

typedef struct{
	  i32 deep; /* ��ǰ�ڵ�������� */
	  i32 samSurplus; /* ������ʱ�ڵ��Ӧ�������ݸ��� */
	  i32 *sPtr; /* ������ʱ��Ӧ������������ */
}KNN_NdPrmTypeDef, /* ���ɽ����������ṹ�� */
*KNN_NdPrmTypeDefPtr; /* ���ɽ����������ṹ��ָ�� */

typedef struct{
	  i32 tail; /* ջ�� */
	  i32 top;/* ջ�� */
	  KNN_NdTypeDefPtr kStkPtrs[ KNN_STACK_SIZE ]; /* ջ�� ���ڴ洢Ҷ�ڵ�����·�� */
}KNN_StkTypeDef, /* ջ�ṹ�� */
*KNN_StkTypeDefPtr;/* ջ�ṹ��ָ�� */

typedef struct {
	i32 kTimes; /* ��ǰ�������� */
	i32 *knnIndexPtr; /* k��������������� */
	d64 *inPtr; /* �������� */
	d64 dist; /* ��ǰ������� */
	KNN_StkTypeDef KNN_Stack; /* ջ */
}KNN_PrmTypeDef, /* �㷨�����ṹ����� */
*KNN_PrmTypdeDefPtr; /* �㷨�����ṹ��ָ�� */

typedef struct{
	  i32 k; /* k������ */
	  i32 treeLabel;
	  KNN_PrmTypeDef parameters; /* �㷨���� */
	  KNN_NdTypeDefPtr rootPtr; /* k-d �����ڵ� */
}KNN_TypeDef, /* �㷨�ṹ�� */
*KNN_TypeDefPtr; /* �㷨�ṹ��ָ�� */

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