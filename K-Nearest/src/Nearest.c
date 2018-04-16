/**
   ******************************************************************************************************************************************************
   * @file                Nearest.c
   * @author          Morris
   * @version         V1.0
   * @date              2018��4��16��20:49:24 ��VS2017��DeBugģʽ���ձ������С�
   * @brief             ͳ��ѧϰ�����е� k �����㷨
   ******************************************************************************************************************************************************
   * @attention   ��1�����ڴ��ڵݹ���ã������������޴�ʱ������Kֵ�ϴ�ʱ�������������ջ��.exe�ļ���ջ����
   *                                �������׵���ջ������󣨿ɿ��ǲ���ѭ����ʽʵ�֣���
   *                      ��2��K=1ʱΪ��������������迼��ջ���⡣
   *                      ��3��������30���������������У���������ɵĲ�ͬ�������������30����������С�
   *                      ��4����������Ϊ10000ʱ��K=5000����������K=10000ʱ����ջ��������ĳ���ջ������������
   *                      ��5����������5��K=500������ջ��������ĺ�������
   *                      ��6������K-D��ÿ���ڵ�������һ�Σ��д��Ż���
   *                      ��7������K����ʱ��·���ظ����д��Ż���
   *
   ******************************************************************************************************************************************************
   */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "../inc/Nearest.h"
/**
 *@brief	�жϽڵ�洢�����Ƿ��Ѵ洢�ڽ���������
 *@param	i32 *vecPtr k�����������б��е������洢����
 *@param	i32 num ��ǰ�ڵ�洢�������б��е�����
 *@param	i32 numOfElement ��ǰ�����ĵ�n������
 *@retval	int
*/
static i32 __isInList( 
	i32 *vecPtr,
	i32 num, 
	i32 numOfElement )
{
	  i32 i;

	  for( i = 0; i < numOfElement; i++ ){
			if( num == vecPtr[ i ] ){
				  return 1;
			}/* end if */
	  }/* end for */
	   
	  return 0;
}/* end function __isInList */

/**
 * @brief		ŷ�Ͼ��뺯��
 * @param		d64 *inPtr �洢��������������ָ��
 * @param		d64 **vePtr �洢�������ݵĶ�ά����ָ��
 * @param		i32 colum �������ݶ�ά�����е�������
 * @param		i32 numOfElment ��������ά��
 * @retval		double���ͣ�ŷʽ����ֵ
 */
static d64 EuclideanDistance( 
	d64 *inPtr, 
	d64 **vePtr, 
	i32 colum, 
	i32 numOfElment )
{
	  i32 i;
	  d64 temp = 0.0;

	  for( i = 0; i < numOfElment; i++ ){
			temp += pow( ( inPtr[ i ] - vePtr[ i ][colum ] ), 2 );
	  }/* end for */

	  return sqrt( temp );
}/* end function EuclideanDistance */

/**
 * @brief		�����پ��뺯��
 * @param		d64 *inPtr �洢��������������ָ��
 * @param		d64 **vePtr �洢�������ݵĶ�ά����ָ��
 * @param		i32 colum �������ݶ�ά�����е�������
 * @param		i32 numOfElment ��������ά��
 * @retval		double���ͣ������پ���ֵ
 */
static d64 ManhattanDistance( 
	d64 *inPtr, 
	d64 **vePtr,
	i32 colum, 
	i32 numOfElment )
{
	  i32 i;
	  d64 temp = 0.0;

	  for( i = 0; i < numOfElment; i++ ){
			temp += fabs( ( inPtr[ i ] - vePtr[ i ][ colum ] ) );
	  }/* end for */

	  return temp;

}/* end function ManhattanDistance */

/**
 * @brief		������뺯��
 * @param		d64 *inPtr �洢��������������ָ��
 * @param		d64 **vePtr ѵ�������е�����
 * @param		i32 colum �������ݶ�ά�����е�������
 * @param		i32 numOfElment ��������ά��
 * @retval		double���� ���q=�������ֵ
 */
static d64 MaxDistance( 
	d64 *inPtr, 
	d64 **vePtr, 
	i32 colum, 
	i32 numOfElment )
{
	  i32 i;
	  d64 temp;
	  d64 max = 0.0;

	  for( i = 0; i < numOfElment; i++ ){
			temp = fabs( ( inPtr[ i ] - vePtr[ i ][ colum ] ) );
			
			if( temp > max ){
				  max = temp;
			}/* end if */

	  }/* end for */

	  return max;
}/* end function MaxDistance */

/**
 * @brief		���µ�ǰ����ں���
 * @param		KNN_NdTypeDefPtr tnPtr �ڵ�ṹ��ָ��
 * @param		KNN_PrmTypdeDefPtr prmPtr �㷨�����ṹ��ָ��
 * @param		DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ��
 * @retval		��
*/
static void KNN_NearestDistance( 
	KNN_NdTypeDefPtr tnPtr, 
	KNN_PrmTypdeDefPtr prmPtr, 
	const DT_TypeDefPtr dPtr )
{
	  d64 temp;/* ������ʱ���� */

	  if ( !__isInList( prmPtr->knnIndexPtr, tnPtr->index,  prmPtr->kTimes ) ){ /*�жϵ�ǰ�ڵ��Ƿ��ѱ���Ϊ���� */

		  temp = EuclideanDistance( 
			  prmPtr->inPtr, /* �������� */
			  dPtr->samPtrs, /* �������ݴ洢��ά���� */
			  tnPtr->index, /* ��ǰ�ڵ�洢������ֵ */
			  dPtr->numOfInput );/* ��������ά��*/

		  if ( prmPtr->dist >= temp ){/* �ж�������ڵ�����Ƿ�С�ڵ�ǰ��С����*/

			  prmPtr->dist = temp;/*���¾���*/
			  prmPtr->knnIndexPtr[ prmPtr->kTimes ] = tnPtr->index;/*�洢�ڵ�����*/

		  }/* end if */
	  }/* end if */
}/* end function KNN_NearestDistance */

/**
  * @brief		����k-d������
  * @param	KNN_NdTypeDefPtr *tnPtrs k-d�����ṹ��ָ��
  * @param	KNN_NdPrmTypeDefPtr npPtr ���ɽ����������ṹ��ָ��
  * @param	DT_TypeDefPtr dPtr �������ݴ洢�ṹ��ָ��
  * @retval		��
  */
static void KNN_KdTreeCreat( 
	KNN_NdTypeDefPtr *tnPtrs, 
	KNN_NdPrmTypeDefPtr npPtr,
	const DT_TypeDefPtr dPtr 
)
{
	  i32 i; /* ѭ����ʱ���� */
	  i32 midium;/* ��λ����ʱ����	 */
	  i32 surplurs;/* �ӽڵ�����������ʱ���� */
	  KNN_NdPrmTypeDef nodeParam;/* �����ӽڵ���������ṹ�����	*/

	  *tnPtrs = ( KNN_NdTypeDefPtr )malloc( sizeof ( KNN_NdTypeDef ) ); /* ��̬����һ���ڵ��ڴ� */

	  if( *tnPtrs != NULL ){ /* �жϽڵ��ڴ��Ƿ����ɹ� */

			( *tnPtrs )->dimention = npPtr->deep % dPtr->numOfInput; /* ���ݽڵ���ȼ����зֵ�ѡ��ά��  */

			if( npPtr->samSurplus > 1 ){ /* �жϸýڵ��Ӧ�����ռ��������� */
				  DT_sorftSampleSequence(
					  dPtr,
					  npPtr->sPtr, 
					  ( *tnPtrs )->dimention, 
					  npPtr->samSurplus ); /* ���ݵ�ǰ�зֵ�ά�ȶԸýڵ�����Ӧ������������ */                                                                                                              
			}/* end if */

			midium = npPtr->samSurplus / 2; /* ������λ�� */
			( *tnPtrs )->index = npPtr->sPtr[ midium ];	/* �洢��λ����Ӧ��������	 */
			surplurs = midium;

			if( surplurs == 0 ){	 /* �ж�����ʣ������Ƿ�Ϊ0 */
				  ( *tnPtrs )->leftChildPtr = NULL; /* ��ǰ�ڵ���ΪҶ�ڵ㣬�����������ӽڵ� */
			}/* end if */
			else{
				  nodeParam.deep = npPtr->deep + 1;  /* ��һ����� */
				  nodeParam.samSurplus = surplurs;	 /* ���ӽڵ��Ӧ�����ռ��������� */
				  nodeParam.sPtr = ( i32 * )malloc( sizeof( i32 ) * nodeParam.samSurplus );/* ���ӽڵ��Ӧ�������������洢���� */

				  for( i = 0; i < nodeParam.samSurplus; i++ ){
						nodeParam.sPtr[ i ] = npPtr->sPtr[ i ];/* �ýڵ����ӽڵ��Ӧ����������������*/
				  }/* end for */

				  KNN_KdTreeCreat( ( &( *tnPtrs )->leftChildPtr ), &nodeParam, dPtr );	/* �ݹ�����������ӽڵ� */
				  free( nodeParam.sPtr );/* �ͷ����ӽڵ���������ָ��*/

			}/* end else */

			if( npPtr->samSurplus > 1 ){	/* �жϸýڵ��Ӧ�����ӿռ��������� */
				  surplurs = npPtr->samSurplus - surplurs - 1;

				  if( surplurs == 0 ){
						( *tnPtrs )->rightChildPtr = NULL;/* ��ǰ�ڵ���ΪҶ�ڵ㣬�����������ӽڵ�*/
				  }/* end if */
				  else{
						nodeParam.samSurplus = surplurs;/*���ӽڵ��Ӧ�����ռ���������*/
						nodeParam.sPtr = ( i32 * )malloc( sizeof( i32 ) * nodeParam.samSurplus );/* ���ӽڵ��Ӧ�������������洢���� */

						for( i = 0; i < nodeParam.samSurplus; i++ ){
							  nodeParam.sPtr[ i ] = npPtr->sPtr[ midium + 1 + i ];
						}/* end for */

						KNN_KdTreeCreat( &( ( *tnPtrs )->rightChildPtr ), &nodeParam, dPtr );/* �ݹ��������ӽڵ�*/
						free( nodeParam.sPtr );/* �ͷ����ӽڵ���������ָ��*/
				  }/* end else */
			}/* end if */
			else{
				  ( *tnPtrs )->rightChildPtr = NULL;
			}/* end else */
	  }/* end if */
	  else{
			printf( "\n����kdTreeCreat() �ڴ治�㣡\n" );
			exit( -1 );
	  }/* end else */
}/* end function kdTreeCreat */

/**
 * @brief		����k�����㷨����
 * @param		KNN_TypeDefPtr nPtr k�����㷨�ṹ��ָ��
 * @param		DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ��
 * @retval		��
 */
void KNN_NearestCreat( 
	KNN_TypeDefPtr nPtr , 
	const DT_TypeDefPtr dPtr )
{
	  i32 i;
	  KNN_NdPrmTypeDef nodeParam;

	  if( dPtr->TrainDataEntered == 1 && nPtr->rootPtr == NULL ){

			nPtr->rootPtr = ( KNN_NdTypeDefPtr )malloc( sizeof( KNN_NdTypeDef  ) );/* ���ڵ� */

			if( nPtr->rootPtr != NULL ){ /*�жϸ��ڵ��ڴ�����Ƿ�ɹ�*/

				  nodeParam.deep = 0;/* ���ڵ���� */
				  nodeParam.samSurplus = dPtr->numOfSample;/* ���ڵ��Ӧ�������� */
				  nodeParam.sPtr = ( i32 * )malloc( sizeof( i32 ) * nodeParam.samSurplus );/* ���ڵ��Ӧ���������������� */

				  for( i = 0; i < nodeParam.samSurplus; i++ ){
						nodeParam.sPtr[ i ] = i;
				  }/* end for */

				  printf( "\n���������㷨ģ��...\n" );

				  KNN_KdTreeCreat( &(nPtr->rootPtr), &nodeParam, dPtr );/*���� kd ��*/
				  free( nodeParam.sPtr );/* �ͷ���ʱ�����ڴ� */

				  nPtr->treeLabel = 1;
				  printf( "\n�ɹ������㷨ģ�ͣ�\n" );

			}/* end if */
			else{
				  printf("\n����NearestCreat() �ڴ治��!\n");
				  exit( -1 );/*�˳�Ӧ�ó���*/
			}/* end else */
	  }/* end if */
	  else{
			if( dPtr->TrainDataEntered != 1 ) printf( "\n�޿������ݣ�����������!\n" );
			nPtr->rootPtr = NULL;
	  }/* end else */
}/* end function NearestCreat */

/**
 * @brief		�ݹ�����Ҷ�ڵ㺯��
 * @param		KNN_NdTypeDefPtr tnPtr k-d�����ṹ��ָ��
 * @param		KNN_PrmTypdeDefPtr prmPtr �㷨�����ṹ��ָ��
 * @param		DT_TypeDefPtr dPtr �������ݴ洢�ṹ��ָ��
 * @retval		��
 */
static void KNN_SearchLeafNode( 
	KNN_NdTypeDefPtr tnPtr, 
	KNN_PrmTypdeDefPtr prmPtr, 
	const DT_TypeDefPtr dPtr )
{
	  prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = tnPtr;/* ����ǰ�ڵ�ѹջ����¼����Ҷ�ڵ�·�� */

	  if( tnPtr->leftChildPtr == NULL && tnPtr->rightChildPtr == NULL ) return;/* �����ǰ�ڵ�ΪҶ�ڵ㣬���˳��ݹ� */

	  if( prmPtr->inPtr[ tnPtr->dimention ] < dPtr->samPtrs[ tnPtr->dimention ][ tnPtr->index ] ){ /* �ж������뵱ǰ�ڵ�洢�������ݵ�ǰά��С*/
			if( tnPtr->leftChildPtr != NULL ){/* ����ǰ�ڵ�����ӽڵ㲻Ϊ�գ��ƶ�����ڵ�*/

				  prmPtr->KNN_Stack.top++;/* ջָ������ */
				  KNN_SearchLeafNode( tnPtr->leftChildPtr, prmPtr, dPtr );/* ����Ҷ�ڵ� */

			}/* end if */
			else return;/* ��ǰ�ڵ���αҶ�ڵ㣬�˳��ݹ� */
	  }/* end if */
	  else if( tnPtr->rightChildPtr != NULL ){/* ����ǰ�ڵ�����ӽڵ㲻Ϊ�գ��ƶ����ҽڵ�*/

			prmPtr->KNN_Stack.top++;/* ջָ������ */
			KNN_SearchLeafNode( tnPtr->rightChildPtr, prmPtr, dPtr );/* ����Ҷ�ڵ� */

	  }/* end else if */
	  else return;/* ��ǰ�ڵ���αҶ�ڵ㣬�˳��ݹ� */
}/* end function KNN_SearchLeafNode */

/**
 * @brief		��������ڵݹ麯��
 * @param		KNN_NdTypeDefPtr tnPtr k-d�����ṹ��ָ��
 * @param		KNN_PrmTypdeDefPtr prmPtr �㷨�����ṹ��ָ��
 * @param		DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ��
 * @retval		��
*/
static void KNN_SearchNearest( 
	KNN_NdTypeDefPtr tnPtr, 
	KNN_PrmTypdeDefPtr prmPtr, 
	const DT_TypeDefPtr dPtr )
{
	  if( prmPtr->KNN_Stack.top >= 0 ){ /* �жϵ�ǰ�ڵ��Ƿ��Ǹ��ڵ�ĸ��ڵ� */

			KNN_NearestDistance( tnPtr, prmPtr, dPtr );/* ���㵱ǰ�ڵ����������� */

			if( fabs( prmPtr->inPtr[ tnPtr->dimention ] - 
				dPtr->samPtrs[ tnPtr->dimention ][ tnPtr->index ] ) 
				< prmPtr->dist  ){/* �ж�������͵�ǰ�����֮��ľ���Ϊ�뾶�ĳ������뵱ǰ�ڵ����һ�ӽڵ��Ƿ��ཻ */

				  if( prmPtr->inPtr[ tnPtr->dimention ] < 
					  dPtr->samPtrs[ tnPtr->dimention ][ tnPtr->index ] ){/* ���������ӽڵ��ƶ�����ǰ�ڵ� */

						if( tnPtr->rightChildPtr != NULL ){/* ����ǰ�ڵ㲻��αҶ�ڵ� */
							  KNN_SearchLeafNode( tnPtr->rightChildPtr, prmPtr, dPtr );/* �Ե�ǰ�ڵ�����ӽڵ�Ϊ���ڵ�����Ҷ�ڵ� */
						}/* end if */
						else{/*����ǰ�ڵ�ΪαҶ�ڵ�*/
							prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = NULL;
							prmPtr->KNN_Stack.top--;/* �˻ص�ǰ�ӽڵ�ĸ��ڵ� */
						}/* end else */
				  }/* end if */
				  else{/* ���������ӽڵ��ƶ�����ǰ�ڵ� */
						if( tnPtr->leftChildPtr != NULL ){/* ��ǰ�ڵ㲻��αҶ�ڵ�*/
							KNN_SearchLeafNode( tnPtr->leftChildPtr, prmPtr, dPtr );/* �Ե�ǰ�ڵ�����ӽڵ�Ϊ���ڵ�����Ҷ�ڵ� */
						 }/* end if */
						else{/* ����ǰ�ڵ���ΪҶ�ڵ� */
								prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = NULL;
								prmPtr->KNN_Stack.top--;/* �˻ص�ǰ�ӽڵ�ĸ��ڵ� */
						}/* end else */
				  }/* end else */
			}/* end if */
			else{/* �����ཻ */
				prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = NULL;
				prmPtr->KNN_Stack.top--;/* ֱ���˻ص�ǰ�ڵ�ĸ��ڵ� */
			}/* end else */

			KNN_SearchNearest( 
				prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ],/*��������Ҷ�ڵ���ջ��ΪҶ�ڵ㣬����ջ��Ϊ��ǰ�ڵ�ĸ��ڵ� */
				prmPtr, dPtr );

	  }/* end if */
	  else return;/* �˳���������� */
}/* end function KNN_SearchNearest */

/**
 * @brief		����K���ں���
 * @param		KNN_TypeDefPtr nPtr �㷨�ṹ��ָ��
 * @param		DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ��
 * @retval		��
*/
void KNN_SearchKNearest( 
	KNN_TypeDefPtr nPtr, 
	const DT_TypeDefPtr dPtr )
{
	if ( nPtr->treeLabel == 1 && nPtr->k != 0 && nPtr->parameters.inPtr != NULL ){
		while ( nPtr->parameters.kTimes < nPtr->k ){/* k������ */

			nPtr->parameters.dist = +INFINITY;

			KNN_SearchLeafNode( nPtr->rootPtr, &nPtr->parameters, dPtr );/* ����Ҷ�ڵ� */
			KNN_SearchNearest(
				nPtr->parameters.KNN_Stack.kStkPtrs[ nPtr->parameters.KNN_Stack.top ], /* Ҷ�ڵ� */
				&nPtr->parameters, dPtr );/* ��������� */

			nPtr->parameters.kTimes++;
			nPtr->parameters.KNN_Stack.top = 0;/* ջָ��ָ��ջ�� */
		}/* end while */

		nPtr->parameters.kTimes = 0;
	}
	else{ 
		if( nPtr->treeLabel != 1 ) printf( "\n����k-d �������ڣ�\n" );
		else if( nPtr->k != 1) printf( "\n����������kֵ!\n" );
		else printf( "\n���������ݵ㣡\n" );
	}/* end else */
}/* end function KNN_SearchKNearest */

/**
  * @brief		��ʼ���㷨�ṹ���������
  * @param	KNN_TypeDefPtr nPtr �㷨�ṹ��ָ��
  * @param	DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ��
  * @retval		��
  */
void KNN_NearestInit( KNN_TypeDefPtr nPtr )
{
	i32 i;

	for ( i = 0; i < KNN_STACK_SIZE; i++ ){
		nPtr->parameters.KNN_Stack.kStkPtrs[ i ] = NULL; /* ��ʼ��ջ */
	}/* end for */

	/*��ʼ������*/
	nPtr->parameters.dist = 0.0;
	nPtr->treeLabel = 0;
	nPtr->parameters.KNN_Stack.tail = 0;
	nPtr->parameters.KNN_Stack.top = 0;
	nPtr->parameters.kTimes = 0;
	nPtr->parameters.inPtr = NULL;
	nPtr->parameters.knnIndexPtr = NULL;
	nPtr->rootPtr = NULL;

}/* end function NearestInit */

/**
 * @brief		���������ݽ��з��ຯ��
 * @param		KNN_TypeDefPtr nPtr �㷨�ṹ��ָ��
 * @param		DT_TypeDefPtr dPtr ���ݴ洢�ṹ��ָ��
 * @retval		int�����������������
 */
i32 KNN_ClassifyInputData( 
	KNN_TypeDefPtr nPtr, 
	const DT_TypeDefPtr dPtr )
{

	i32 i, KNN_class, count = 0, max = 0;

	if ( nPtr->treeLabel == 1  && nPtr->k != 0 && dPtr->numOfClasses != 0 && nPtr->parameters.inPtr != NULL ){
		i32 *freqPtr = ( i32 * )malloc( sizeof( i32 ) * ( dPtr->numOfClasses + 1 ) );/* ���ڼ���k��������ĳһ�����Ƶ�� */
		i32 *maxFreqPtr = ( i32 * )malloc( sizeof( i32 ) * dPtr->numOfClasses );/* �洢���Ƶ������� */

			/* ��ʼ�� */
		for ( i = 0; i < dPtr->numOfClasses + 1; i++ ){
			freqPtr[ i ] = 0;

			if ( i < dPtr->numOfClasses ){
				maxFreqPtr[ i ] = 0;
			}/* end if */
		}/* end for */

		KNN_SearchKNearest( nPtr, dPtr );/* ����k������ */

		for ( i = 0; i < nPtr->k; i++ ){
			freqPtr[ dPtr->aimPtr[ nPtr->parameters.knnIndexPtr[ i ] ] ]++;/* ͳ��k��������ÿ������Ƶ�� */
		}/* end for */

		for ( i = 1; i < dPtr->numOfClasses + 1; i++ ){

			if ( freqPtr[ i ] > max ){/* Ѱ��Ƶ��������� */
				max = freqPtr[ i ];
				count = 1;
				maxFreqPtr[ 0 ] = i;
			}/* end if */
			else if ( freqPtr[ i ] == max && freqPtr[ i ] != 0 ){/* ���Ƶ����ͬ����� */
				count++;
				maxFreqPtr[ count - 1 ] = i;
			}/* end else if */
		}/*end for */

		KNN_class = maxFreqPtr[ rand( ) % count ];/* �� count �����Ƶ����ͬ�������������� */

		free( freqPtr );
		free( maxFreqPtr );/* �ͷ��ڴ� */

		return KNN_class;/* ������������ */
	}/* end if */
	else{
		if( !nPtr->treeLabel ) printf( "\n����k-d��δ���ɣ�\n" );
		else if( !nPtr->k )printf( "\n������kֵ��\n" );
		else if( nPtr->parameters.inPtr == NULL ) printf( "\n���������ݣ�\n" );
		else printf( "\n���������������\n" );
		return 0;
	}/* end else */
}/* end function KNN_ClassifiedInput */

/**
 * @brief		����ģ�ͷ������ܺ�����������kֵ����
 * @param		KNN_TypeDefPtr nPtr �㷨�����ṹ��ָ��
 * @param		DT_TypeDefPtr dPtr �������ݴ洢�ṹ��ָ��
 * @retval		��
 */
void KNN_TestModelPerformence( 
	KNN_TypeDefPtr nPtr, 
	const DT_TypeDefPtr dPtr )
{
	i32 i, j, correct = 0, error = 0;
	d64 correctRate, errorRate;
	if ( nPtr->treeLabel == 1  && dPtr->TestDataEntered == 1&& dPtr->numOfClasses != 0 ){
		printf( "\n�㷨����...\n" );

		if( nPtr->parameters.inPtr == NULL ){
			nPtr->parameters.inPtr = ( d64 * )malloc( sizeof( d64 ) * dPtr->numOfInput );
		}/* end if */

		for ( i = 0; i < dPtr->numOfTSample; i++ ){
			for ( j = 0; j < dPtr->numOfInput; j++ ){
				nPtr->parameters.inPtr[ j ] = dPtr->tSamPtrs[ j ][ i ];/* �����������*/
			}/* end inner for */

			if ( dPtr->tAimPtr[ i ]  ==  KNN_ClassifyInputData( nPtr, dPtr ) ){
				correct++;/* ������ȷ������ */
			}/* end if */
		}/* end outer for */

		correctRate = ( ( d64 )correct / dPtr->numOfTSample ) * 100.0;/* ��������������ȷ��*/
		errorRate = 100 - correctRate;/* ������ */

		printf( "\n������������ȷ�ʣ� %.2lf%%\n"
			"\n���������������ʣ� %.2lf%%\n", correctRate, errorRate );
	}
	else{
		if ( !nPtr->treeLabel ) printf( "\n����k-d��δ���ɣ�\n" );
		else if ( !dPtr->TestDataEntered ) printf( "\n�����޿��ò���������\n" );
		else printf( "\n�����������������!\n" );
	}/* end else */
}/* end function KNN_TestModelPerformence */

/**
 * @brief		����ɨ�躯��
 * @param		KNN_TypeDefPtr nPtr �㷨�ṹ��ָ��
 * @param		���ݴ洢�ṹ��ָ��
 * @retval		��
*/

void KNN_LinnerScan( 
	KNN_TypeDefPtr nPtr, 
	const DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	d64 temp;
	i32 temp2;
	if ( dPtr->TrainDataEntered == 1 ){
		d64 *linerPtr = ( d64 * )malloc( sizeof( d64 ) * dPtr->numOfSample );
		i32 *linerIndPtr = ( i32 * )malloc( sizeof( i32 ) * dPtr->numOfSample );

		for ( i = 0; i < dPtr->numOfSample; i++ ){
			linerPtr[ i ] = EuclideanDistance(
				nPtr->parameters.inPtr,
				dPtr->samPtrs, i,
				dPtr->numOfInput ); /* ����������ÿ�������ľ��� */

			linerIndPtr[ i ] = i; /* �洢���� */
		}/* end for */

		/* �Ծ���������� */
		for ( i = 1; i < dPtr->numOfSample; i++ ){
			for ( j = 0; j < dPtr->numOfSample - 1; j++ ){
				if ( linerPtr[ j ] > linerPtr[ j + 1 ] ){
					temp = linerPtr[ j ];
					temp2 = linerIndPtr[ j ];

					linerPtr[ j ] = linerPtr[ j + 1 ];
					linerIndPtr[ j ] = linerIndPtr[ j +1 ];

					linerPtr[ j + 1 ] = temp;
					linerIndPtr[ j + 1 ] = temp2;
				}/* end if */
			}/* end inner for */
		}/* end outer for */

		printf( "\n����ɨ��k�������������������\n" );

		for ( i = 0; i < nPtr->k; i++ ){
			printf( "(%d) %d\n", i + 1, linerIndPtr[ i ] );
		}/*end for */

		free( linerPtr );
		free( linerIndPtr );/* �ͷ��ڴ�*/
	}/* end if */
	else{
		printf( "\n�����޿���ѵ��������\n" );
	}/* end else */
}/* end function KNN_LinnerScan */

void KNN_SetKNNParameters( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr )
{
	i32 temp;
	if ( dPtr->samParmLabel  == 1){
		do{
			printf( "\n����Kֵ( С�ڻ����ѵ����������%d, �˳�: -1 )��", dPtr->numOfSample );
			scanf_s( "%d", &temp );

			printf( "\n" );

			if ( temp == -1 ) break;

			if ( temp < 0 ) printf( "\n�������: ���������0����ֵ��\n" );

			if ( temp >  dPtr->numOfSample )printf( "\n�������: ������С��%d����ֵ��\n", dPtr->numOfSample );
		} while ( temp < 0 || temp > dPtr->numOfSample );

		nPtr->k = temp;

		if ( nPtr->parameters.knnIndexPtr != NULL ){
			free( nPtr->parameters.knnIndexPtr );
		}/* end if */

		nPtr->parameters.knnIndexPtr = ( i32 * )malloc( sizeof( i32 ) * nPtr->k );/* ��̬�����ڴ�洢k����������*/

		for ( temp = 0; temp < nPtr->k; temp++ ){
			nPtr->parameters.knnIndexPtr[ temp ] = -1;
		}/* end for */
	}/* end if */
	else printf( "\n���ô���: ���������ݽṹ��Ϣ��\n" );

}/* end function KNN_SetKNNParameters */

void KNN_InputData( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr)
{
	i32 i;
	if ( dPtr->samParmLabel == 1 ){
		if ( nPtr->parameters.inPtr == NULL ){
			nPtr->parameters.inPtr = ( d64 * )malloc( sizeof( d64 ) * dPtr->numOfInput );
		}/*end if */

		printf( "\n�������ݣ�\n" );

		for( i = 0; i < dPtr->numOfInput; i++ ){
			scanf_s( "%lf", &nPtr->parameters.inPtr[ i ] );
		}/* end for */
	}/* end if */
	else printf( "\n������������Ϣ��\n" );
}/* end function KNN_InputData */

void KNN_printData( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr )
{
	i32 i;
	if( nPtr->parameters.inPtr == NULL ){
		printf( "\n��\n" );
	}/* end if */
	else{
		printf( "\n�������ݣ�\n" );
		for( i = 0; i < dPtr->numOfInput; i++ ){
			printf( "%.3lf\n", nPtr->parameters.inPtr[ i ] );
		}/* end for */
	}/* end else */
}/* end function KNN_printData */

void KNN_PrintConmand( i32 *chose )
{
	printf( "\n1.  �������ݴ洢����.\n"
			"2.  ��ʾ���ݴ洢����.\n"
			"3.  �������ݴ洢�ṹ.\n"
			"4.  ��ʼ�����ݽṹ��.\n"
			"5.  ����kֵ.\n"
			"6.  ����ѵ������.\n"
			"7.  �����������.\n"
			"8.  ��ʾѵ������.\n"
			"9.  ��ʾ��������.\n"
			"10. ����k-d��.\n"
			"11. k-d������k����.\n"
			"12. ����ɨ������k����.\n"
			"13. ����ģ������.\n"
			"14. ����ʶ������.\n"
			"15. ��ʾ��������.\n"
			"16. KNN����.\n"
			"0.  �˳�.\n"
			"ѡ����ţ�");
	scanf_s( "%d", chose );
}/* end function KNN_PrintConmand */

/********************************************************************************************* END OF FILE *********************************************************************************************/