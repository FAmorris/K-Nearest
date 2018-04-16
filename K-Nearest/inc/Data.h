#ifndef __DATA_H
#define __DATA_H

#ifdef __cplusplus
extern "C" {
#endif
#include "UserType.h"

typedef struct{
	d64 **samPtrs;	 /* ѵ�������洢��ά����ָ��	*/
	d64 **tSamPtrs;/* ���������洢��ά����ָ��	 */
	i32 *aimPtr; /* ѵ������Ŀ������洢����ָ��*/
	i32 *tAimPtr;	/* ��������Ŀ������洢����ָ��*/

	i32 numOfSample;/* ѵ���������� */
	i32 numOfTSample; /* ������������ */
	i32 numOfInput;	/* ��������ά��*/
	i32 numOfClasses;
	i32 samParmLabel;/* ���������ñ�־ */
	i32 creatLabel;
	i32 TrainDataEntered;
	i32 TestDataEntered;
}DT_TypeDef, *DT_TypeDefPtr;/* �������ݴ洢�ṹ������ͽṹ��ָ�� */

void DT_DatasCreat(DT_TypeDefPtr dPtr);/* �������ݴ洢���麯�� */
void DT_InputTrainSamples( DT_TypeDefPtr dPtr );/* ����ѵ���������ݺ��� */
void DT_InputTestSamples( DT_TypeDefPtr dPtr );/* ��������������ݺ��� */
void DT_DatasInit( DT_TypeDefPtr  dPtr );/* �洢�����ʼ������*/
void DT_DatasDeInit( DT_TypeDefPtr dPtr );/* �ͷ�������ռ�ڴ溯��*/
void DT_PrintTrainSamples( DT_TypeDefPtr dPtr );/* ��ʾѵ����������*/
void DT_PrintTestSamples( DT_TypeDefPtr dPtr );/* ��ʾ������������ */
void DT_SetSampleParameters( DT_TypeDefPtr dPtr );/* ������������	����*/
void printDatasParams( DT_TypeDefPtr dPtr );/* ��ʾ�����洢�ṹ�������� */
void DT_sorftSampleSequence( DT_TypeDefPtr dPtr, i32 *sPtr, i32 num1, i32 num2 );

#ifdef __cplusplus
}
#endif

#endif /* __DATA_H */

/********************************************************** END OF HEARD FILE ***************************************************************/