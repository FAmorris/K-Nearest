/**
   ******************************************************************************************************************************************************
   * @file               Data.c
   * @author         Morris
   * @version        V1.0
   * @date             2018��4��16��20:49:24 ��VS2017��DeBugģʽ���ձ������С�
   * @brief            k �����㷨,���ݴ洢�ṹ
   ******************************************************************************************************************************************************
   * @attention
   *
   *
   ******************************************************************************************************************************************************
   */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "../inc/Data.h"

/**
 * @brief		�����洢�ṹ���������
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
*/
void DT_SetSampleParameters( DT_TypeDefPtr dPtr )
{
	i32 num1 = 0;

	do{
		printf( "\n����ѵ����������( �˳�: -1 )��" );
		scanf_s("%d", &num1 ); /* ��������ѵ������������ */

		if( num1 == -1 ){
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n����������������0������\n" );
		}/* end if */
	}while( num1 < 0 );/* ѭ������ֱ���û�ѡ���˳���������ȷ*/
	dPtr->numOfSample = num1;/*	����ѵ����������*/

	do{
		printf("\n���������������( �˳�: -1 )��");
		scanf_s("%d", &num1);	/*���������������*/

		if( num1 == -1 ){
			return;
		}/* end if */

		if( num1 < 0 ){
			printf("\n����������������0������\n");
		}/* end if */
	}while( num1 < 0 );
	dPtr->numOfTSample = num1;/*���ò�����������*/

	do{
		printf("\n��������ά��( �˳�: -1 )�� ");
		scanf_s("%d", &num1);/*��������������ά��*/

		if( num1 == -1 ){
			return;	
		}/* end if */	

		if( num1 < 0 ){
			printf("\n����������������0������\n");
		}/* end if */
	}while( num1 < 0 );
	dPtr->numOfInput = num1;	/*������������ά��*/

	do{
		printf("\n�������������( �˳�: -1 )�� ");
		scanf_s("%d", &num1);/*��������������ά��*/

		if( num1 == -1 ){
			return;	
		}/* end if */	

		if( num1 < 0 ){
			printf("\n����������������0������\n");
		}/* end if */
	}while( num1 < 0 );
	
	dPtr->numOfClasses = num1;

	dPtr->samParmLabel = 1;/* ���ݲ������ñ�־	*/
}/*end function setSampleParameters */

/**
 * @brief		�������ݴ洢�ṹ��
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
 */
void DT_DatasCreat( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 numS		= dPtr->numOfSample;/* ��ȡѵ����������*/
	i32 numI		= dPtr->numOfInput;/* ��ȡ��������ά��	*/
	i32 numT		= dPtr->numOfTSample;	/* ��ȡ������������	*/
																					
	if( dPtr->samParmLabel == 1 ){/* �ж��Ƿ���������������*/
		dPtr->samPtrs = ( d64 ** )malloc	( sizeof( d64 * ) * ( numI ) );/* ��̬����洢ѵ���������ݵ�ָ������ */

		if( dPtr->samPtrs != NULL ){	 /* �ж�ָ�������ڴ��Ƿ����ɹ�*/	
			for( i = 0; i < numI; i++ ){
				dPtr->samPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numS );/* ָ�����鶯̬����һά���飬���ɶ�ά����*/

				if( dPtr->samPtrs[ i ] == NULL ){/* �ж�ѵ��������ά���鶯̬�����Ƿ�Ϊ�� */
					printf("�ڴ����DT_DatasCreat�����ڴ����ʧ�ܣ�\n");
					exit( -1 );/* ����Ӧ�ó��� */
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("�ڴ����DT_DatasCreat�����ڴ����ʧ�ܣ�\n");
			exit( -1 );/* ����Ӧ�ó��� */
		}/* end else */

		dPtr->aimPtr = ( i32 * )malloc( sizeof( i32 ) * numS );/* ��̬����洢ѵ������Ŀ�����������*/

		if( dPtr->aimPtr == NULL ){/* �ж�ѵ������Ŀ��������鶯̬�����Ƿ�Ϊ��*/
			printf("�ڴ����DT_DatasCreat�����ڴ����ʧ�ܣ�\n");
			exit( -1 );/* ����Ӧ�ó���*/
		}/* end if */

		dPtr->tSamPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numI );	/* ��̬����洢�����������ݵ�ָ������	*/
		if( dPtr->tSamPtrs != NULL ){/* �ж�ָ�������ڴ��Ƿ����ɹ�*/
			for( i = 0; i < numI; i++ ){
				dPtr->tSamPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numT );/* ָ�����鶯̬����һά���飬���ɶ�ά����*/

				if( dPtr->tSamPtrs[ i ] == NULL ){/* �жϲ���������ά���鶯̬�����Ƿ�Ϊ��	*/
					printf("�ڴ����DT_DatasCreat�����ڴ����ʧ�ܣ�\n");
					exit( -1 );/* ����Ӧ�ó���*/
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("�ڴ����DT_DatasCreat�����ڴ����ʧ�ܣ�\n");
			exit( -1 );/* ����Ӧ�ó���*/
		}/* end else */

		dPtr->tAimPtr = ( i32 * )malloc( sizeof( i32 ) * numT );/* ��̬����һ���洢��������Ŀ����������� */

		if( dPtr->tAimPtr == NULL ){/* �жϲ�������Ŀ��������鶯̬�����Ƿ�Ϊ��*/
			printf("�ڴ����DT_DatasCreat�����ڴ����ʧ�ܣ�\n");
			exit( -1 );/* ����Ӧ�ó���*/
		}/* end if */
	}/* end if */
	else{
		printf("\n���ô������ݴ洢�ṹ����δ���ã�\n");
		return;
	}/* end else */

	dPtr->creatLabel = 1;	/* �����洢�ṹ������־��1*/

}/* end function  DatasCreat */

/**
 * @brief		���ѵ����������
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
 */
void DT_InputTrainSamples( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	i32 numI = dPtr->numOfInput;	/* ��ȡ��������ά��	*/
	i32 numS = dPtr->numOfSample; /* ��ȡѵ���������� */
	
	if( dPtr->creatLabel == 1 ){ /* �ж������洢�ṹ�Ƿ񴴽� */
		printf( "\n����ѵ������, ����������%d, ����ά����%d\n", numS, numI );
		for( i = 0; i < numS; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->samPtrs[ j ][ i ] );
			}/* end for */
		}/* end for */

		printf( "\n����ѵ���������( 1-%d )������������%d\n", dPtr->numOfClasses, numS );
		for( i = 0; i < numS; i++ ){
			scanf_s("%d", &dPtr->aimPtr[ i ]);
		}/* end for */

		dPtr->TrainDataEntered = 1;

	}/* end if */
	else{
		printf( "\n���ô����뽨�����ݽṹ��\n" );
	}/* end else */
}/*end function InputTrainSamples */

/**
 * @brief		���������������
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
 */
void DT_InputTestSamples( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	i32 numI = dPtr->numOfInput;	/* ��ȡ��������ά�� */
	i32 numT = dPtr->numOfTSample;	/* ��ȡ������������	*/

	if( dPtr->creatLabel == 1 ){/* �ж������洢�ṹ�Ƿ񴴽�	 */
		printf("\n��������������������� %d, ����ά����%d\n", numT, numI);
		for( i = 0; i < numT; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->tSamPtrs[ j ][ i ]);
			}/* end for */
		}/* end for */

		printf("\n��������������( 1 - %d )������������%d:\n", dPtr->numOfClasses, numT );
		for( i = 0; i < numT; i++ ){
			scanf_s("%d", &dPtr->tAimPtr[ i ]);
		}/* end for */

		dPtr->TestDataEntered = 1;

	}/* end if */
	else{
		printf("\n���ô����뽨�����ݽṹ��\n");
	}/* end else */

}/*end function InputTestSamples */

/**
 * @brief		������
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @param		i32 num1 ����ά��
 * @param		i32 num2 ����ά��
 * @retval		��
 */
void DT_sorftSampleSequence( 
	DT_TypeDefPtr dPtr,
	i32 *sPtr, 
	i32 num1,
	i32 num2 )
{
	  i32 i;
	  i32 j;
	  i32 temp;

	  for( i = 1; i < num2; i++ ){
			for( j = 0; j < num2 - 1; j++ ){
				  if( dPtr->samPtrs[ num1 ][ sPtr[ j ] ] > dPtr->samPtrs[ num1 ][ sPtr[ j + 1 ] ] ){
						temp = sPtr[ j ];

						sPtr[ j ] = sPtr[ j + 1 ];
							  
						sPtr[ j + 1 ] = temp; 
				  }/* end if */
			}/* end for */
	  }/* end for */

}/* end function sorftSampleSequence */

/**
 * @brief		���ݴ洢�ṹ��ʼ������
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
 */
void DT_DatasInit( DT_TypeDefPtr  dPtr )
{
	i32 i;
	i32 j;
	i32 numI   = dPtr->numOfInput;/* ��ȡ��������ά��	*/
	i32 numS  = dPtr->numOfSample;/* ��ȡѵ����������*/
	i32 numT = dPtr->numOfTSample;	/* ��ȡ������������	*/

	if ( dPtr->creatLabel == 1 ){
		for ( i = 0; i < numS; i++ ){
			for ( j = 0; j < numI; j++ ){
				dPtr->samPtrs[ j ][ i ] =  0.0;	/*��ʼ��ѵ�������洢��ά����*/
			}/* end for */

			dPtr->aimPtr[ i ] = 0;/* ��ʼ��ѵ������Ŀ������洢����*/

		}/* end for */

		for ( i = 0; i < numT; i++ ){
			for ( j = 0; j < numI; j++ ){
				dPtr->tSamPtrs[ j ][ i ] = 0.0; /* ��ʼ����������Ŀ������洢��λ����*/
			}/*  end for */

			dPtr->tAimPtr[ i ] =0;	/* ��ʼ����������Ŀ������洢��λ����	 */

		}/* end for */
	}/* end if */
	else printf( "\n���������ݴ洢�ṹ.\n" );
}/* end function DataInit */

/**
 * @brief		���ݴ洢�ṹ�ڴ��ͷź���
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
 */
void DT_DatasDeInit( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 numI		= dPtr->numOfInput; /* ��ȡ��������ά�� */
	i32 numS		= dPtr->numOfSample; /* ��ȡѵ���������� */
	i32 numT		= dPtr->numOfTSample; /* ��ȡ������������	 */

	for( i = 0; i < numI; i++ ){
		free( dPtr->samPtrs[ i ]);	/* �ͷŴ洢ѵ���������ݶ�ά����	�ڴ� */
		free( dPtr->tSamPtrs[ i ]);/* �ͷŴ洢�����������ݶ�ά�����ڴ� */
	}/* end for */

	free( dPtr->samPtrs ); /* �ͷ�ѵ���������ݵ�ָ������ */
	free( dPtr->tSamPtrs ); /*	�ͷŲ����������ݵ�ָ������ */
	free( dPtr->aimPtr );	/* �ͷ�ѵ������Ŀ�������ָ������ */
	free( dPtr->tAimPtr ); /*	�ͷŲ�������Ŀ�������ָ������ */

	dPtr->creatLabel	= 0; /* ��ʼ��������־ */
	dPtr->samParmLabel	= 0;/* ��ʼ��������־ */
	dPtr->numOfInput = 0; /* ��ʼ������ά�� */
	dPtr->numOfSample	= 0; /* ��ʼ��ѵ���������� */
	dPtr->numOfTSample = 0; /* ��ʼ�������������� */

}/* end function DatasDeInit */

/**
 * @brief		ѵ��������ʾ��Ϣ����
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
 */
void DT_PrintTrainSamples( DT_TypeDefPtr dPtr )
{
	i32 i, j, k;
	i32 temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;	
	i32 numI = dPtr->numOfInput;
	i32 numS = dPtr->numOfSample;

	if ( dPtr->TrainDataEntered == 1 ){
		temp1 = numS / 10;
		temp2 = numS % 10;

		if ( temp1 != 0 ){
			for ( k = 0; k < temp1; k++ ){
				printf( "\nѵ���������� %d - %d:\n", temp3 + 1, temp4 + 10 );

				for ( i = 0; i < numI; i++ ){
					for ( j = temp3; j < temp4 + 10; j++ ){
						printf( "%-10.3lf ", dPtr->samPtrs[ i ][ j ] );
					}/* end for */
					printf( "\n" );
				}/* end for */

				printf( "\nĿ�������\n" );

				for ( j = temp3; j < temp4 + 10; j++ ){
					printf( "%-10d ", dPtr->aimPtr[ j ] );
				}/* end for */
				printf( "\n" );

				temp3 = temp4 + 10;
				temp4 += 10;
			}/* end for */
		}/* end if */

		if ( temp2 != 0 ){
			temp3 = temp4;
			temp4 += temp2;

			printf( "\nѵ���������� %d - %d:\n", temp3 + 1, temp4 );

			for ( i = 0; i < numI; i++ ){
				for ( j = temp3; j < temp4; j++ ){
					printf( "%-10.3lf ", dPtr->samPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */

			printf( "\nĿ�������\n" );

			for ( j = temp3; j < temp4; j++ ){
				printf( "%-10d ", dPtr->aimPtr[ j ] );
			}/* end for */
			printf( "\n" );
		}/* end if */
	}
	else printf( "\n���ݲ����ڣ�\n" );
}/* end function printSamples */

/**
 * @brief		����������ʾ��Ϣ����
 * @param		DT_TypeDefPtr dPtr �����洢�ṹ��
 * @retval		��
 */
void DT_PrintTestSamples( DT_TypeDefPtr dPtr )
{
	i32 i, j, k;
	i32 temp1 = 0, temp2 = 0, temp3 = 0,temp4 = 0;
	i32 numI = dPtr->numOfInput;
	i32 numT = dPtr->numOfTSample;
if( dPtr->TestDataEntered == 1 ){
	temp1 = numT / 10;
	temp2 = numT % 10;

	if ( temp1 != 0 ){
		for ( k = 0; k < temp1; k++ ){
			printf( "\n������������ %d - %d:\n", temp3 + 1, temp4 + 10 );

			for ( i = 0; i < numI; i++ ){
				for ( j = temp3; j < temp4 + 10; j++ ){
					printf( "%-10.3lf ", dPtr->tSamPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */

			printf( "\nĿ�������\n" );

			for ( j = temp3; j < temp4 + 10; j++ ){
				printf( "%-10d ", dPtr->tAimPtr[ j ] );
			}/* end for */
			printf( "\n" );

			temp3 = temp4 + 10;
			temp4 += 10;
		}/* end for */
	}/* end if */

	if ( temp2 != 0 ){
		temp3 = temp4;
		temp4 += temp2;

		printf( "\n������������ %d - %d:\n", temp3 + 1, temp4 );

		for ( i = 0; i < numI; i++ ){
			for ( j = temp3; j < temp4; j++ ){
				printf( "%-5.3lf ", dPtr->tSamPtrs[ i ][ j ] );
			}/* end for */
			printf( "\n" );
		}/* end for */

		printf( "\nĿ�������\n" );

		for ( j = temp3; j < temp4; j++ ){
			printf( "%-10d ", dPtr->tAimPtr[ j ] );
		}/* end for */
		printf( "\n" );

	}/* end if */
}
else printf( "\n���ݲ����ڣ�\n" );
}/* end function printTestSamples */

void printDatasParams( DT_TypeDefPtr dPtr )
{
	if ( dPtr->samParmLabel == 1 ){
		printf( "\n����ά��: %d\n"
			"\nѵ����������: %d\n"
			"\n������������: %d\n"
			"\n�����������: %d\n",
			dPtr->numOfInput, dPtr->numOfSample,
			dPtr->numOfTSample, dPtr->numOfClasses );
	}/* end if */
	else printf( "\n����δ���ã�\n" );
}/* end function printDatasParams */
