/**
   ******************************************************************************************************************************************************
   * @file               Data.c
   * @author         Morris
   * @version        V1.0
   * @date             2018年4月16日20:49:24 在VS2017上DeBug模式最终编译运行。
   * @brief            k 近邻算法,数据存储结构
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
 * @brief		样本存储结构体参数设置
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
*/
void DT_SetSampleParameters( DT_TypeDefPtr dPtr )
{
	i32 num1 = 0;

	do{
		printf( "\n输入训练样本总数( 退出: -1 )：" );
		scanf_s("%d", &num1 ); /* 输入用于训练的样本总数 */

		if( num1 == -1 ){
			return;	
		}/* end if */

		if( num1 < 0 ){
			printf("\n输入错误：请输入大于0的数。\n" );
		}/* end if */
	}while( num1 < 0 );/* 循环输入直至用户选择退出或输入正确*/
	dPtr->numOfSample = num1;/*	设置训练样本总数*/

	do{
		printf("\n输入测试样本总数( 退出: -1 )：");
		scanf_s("%d", &num1);	/*输入测试样本总数*/

		if( num1 == -1 ){
			return;
		}/* end if */

		if( num1 < 0 ){
			printf("\n输入错误：请输入大于0的数。\n");
		}/* end if */
	}while( num1 < 0 );
	dPtr->numOfTSample = num1;/*设置测试样本总数*/

	do{
		printf("\n输入数据维数( 退出: -1 )： ");
		scanf_s("%d", &num1);/*输入输入向量的维数*/

		if( num1 == -1 ){
			return;	
		}/* end if */	

		if( num1 < 0 ){
			printf("\n输入错误：请输入大于0的数。\n");
		}/* end if */
	}while( num1 < 0 );
	dPtr->numOfInput = num1;	/*设置输入向量维数*/

	do{
		printf("\n输入样本类别数( 退出: -1 )： ");
		scanf_s("%d", &num1);/*输入输入向量的维数*/

		if( num1 == -1 ){
			return;	
		}/* end if */	

		if( num1 < 0 ){
			printf("\n输入错误：请输入大于0的数。\n");
		}/* end if */
	}while( num1 < 0 );
	
	dPtr->numOfClasses = num1;

	dPtr->samParmLabel = 1;/* 数据参数设置标志	*/
}/*end function setSampleParameters */

/**
 * @brief		创建数据存储结构体
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
 */
void DT_DatasCreat( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 numS		= dPtr->numOfSample;/* 读取训练样本总数*/
	i32 numI		= dPtr->numOfInput;/* 读取输入向量维数	*/
	i32 numT		= dPtr->numOfTSample;	/* 读取测试样本总数	*/
																					
	if( dPtr->samParmLabel == 1 ){/* 判断是否设置了样本参数*/
		dPtr->samPtrs = ( d64 ** )malloc	( sizeof( d64 * ) * ( numI ) );/* 动态分配存储训练样本数据的指针数组 */

		if( dPtr->samPtrs != NULL ){	 /* 判断指针数组内存是否分配成功*/	
			for( i = 0; i < numI; i++ ){
				dPtr->samPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numS );/* 指针数组动态分配一维数组，构成二维数组*/

				if( dPtr->samPtrs[ i ] == NULL ){/* 判断训练样本二维数组动态分配是否为空 */
					printf("内存错误：DT_DatasCreat（）内存分配失败！\n");
					exit( -1 );/* 结束应用程序 */
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("内存错误：DT_DatasCreat（）内存分配失败！\n");
			exit( -1 );/* 结束应用程序 */
		}/* end else */

		dPtr->aimPtr = ( i32 * )malloc( sizeof( i32 ) * numS );/* 动态分配存储训练样本目标输出的数组*/

		if( dPtr->aimPtr == NULL ){/* 判断训练样本目标输出数组动态分配是否为空*/
			printf("内存错误：DT_DatasCreat（）内存分配失败！\n");
			exit( -1 );/* 结束应用程序*/
		}/* end if */

		dPtr->tSamPtrs = ( d64 ** )malloc( sizeof( d64 * ) * numI );	/* 动态分配存储测试样本数据的指针数组	*/
		if( dPtr->tSamPtrs != NULL ){/* 判断指针数组内存是否分配成功*/
			for( i = 0; i < numI; i++ ){
				dPtr->tSamPtrs[ i ] = ( d64 * )malloc( sizeof( d64 ) * numT );/* 指针数组动态分配一维数组，构成二维数组*/

				if( dPtr->tSamPtrs[ i ] == NULL ){/* 判断测试样本二维数组动态分配是否为空	*/
					printf("内存错误：DT_DatasCreat（）内存分配失败！\n");
					exit( -1 );/* 结束应用程序*/
				}/* end if */
			}/* end for */
		}/* end if */
		else{
			printf("内存错误：DT_DatasCreat（）内存分配失败！\n");
			exit( -1 );/* 结束应用程序*/
		}/* end else */

		dPtr->tAimPtr = ( i32 * )malloc( sizeof( i32 ) * numT );/* 动态分配一个存储测试样本目标输出的数组 */

		if( dPtr->tAimPtr == NULL ){/* 判断测试样本目标输出数组动态分配是否为空*/
			printf("内存错误：DT_DatasCreat（）内存分配失败！\n");
			exit( -1 );/* 结束应用程序*/
		}/* end if */
	}/* end if */
	else{
		printf("\n设置错误：数据存储结构参数未设置！\n");
		return;
	}/* end else */

	dPtr->creatLabel = 1;	/* 样本存储结构创建标志置1*/

}/* end function  DatasCreat */

/**
 * @brief		输出训练样本函数
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
 */
void DT_InputTrainSamples( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	i32 numI = dPtr->numOfInput;	/* 读取输入向量维数	*/
	i32 numS = dPtr->numOfSample; /* 读取训练样本总数 */
	
	if( dPtr->creatLabel == 1 ){ /* 判断样本存储结构是否创建 */
		printf( "\n输入训练样本, 样本总数：%d, 数据维数：%d\n", numS, numI );
		for( i = 0; i < numS; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->samPtrs[ j ][ i ] );
			}/* end for */
		}/* end for */

		printf( "\n输入训练样本类别( 1-%d )，样本总数：%d\n", dPtr->numOfClasses, numS );
		for( i = 0; i < numS; i++ ){
			scanf_s("%d", &dPtr->aimPtr[ i ]);
		}/* end for */

		dPtr->TrainDataEntered = 1;

	}/* end if */
	else{
		printf( "\n设置错误：请建立数据结构！\n" );
	}/* end else */
}/*end function InputTrainSamples */

/**
 * @brief		输出测试样本函数
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
 */
void DT_InputTestSamples( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 j;
	i32 numI = dPtr->numOfInput;	/* 读取输入向量维数 */
	i32 numT = dPtr->numOfTSample;	/* 读取测试样本总数	*/

	if( dPtr->creatLabel == 1 ){/* 判断样本存储结构是否创建	 */
		printf("\n输入测试样本，样本总数 %d, 数据维数：%d\n", numT, numI);
		for( i = 0; i < numT; i++ ){
			for( j = 0; j < numI; j++ ){
				scanf_s("%lf", &dPtr->tSamPtrs[ j ][ i ]);
			}/* end for */
		}/* end for */

		printf("\n输入测试样本类别( 1 - %d )，样本总数：%d:\n", dPtr->numOfClasses, numT );
		for( i = 0; i < numT; i++ ){
			scanf_s("%d", &dPtr->tAimPtr[ i ]);
		}/* end for */

		dPtr->TestDataEntered = 1;

	}/* end if */
	else{
		printf("\n设置错误：请建立数据结构！\n");
	}/* end else */

}/*end function InputTestSamples */

/**
 * @brief		排序函数
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @param		i32 num1 排序维度
 * @param		i32 num2 数据维数
 * @retval		无
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
 * @brief		数据存储结构初始化函数
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
 */
void DT_DatasInit( DT_TypeDefPtr  dPtr )
{
	i32 i;
	i32 j;
	i32 numI   = dPtr->numOfInput;/* 读取输入向量维数	*/
	i32 numS  = dPtr->numOfSample;/* 读取训练样本总数*/
	i32 numT = dPtr->numOfTSample;	/* 读取测试样本总数	*/

	if ( dPtr->creatLabel == 1 ){
		for ( i = 0; i < numS; i++ ){
			for ( j = 0; j < numI; j++ ){
				dPtr->samPtrs[ j ][ i ] =  0.0;	/*初始化训练样本存储二维数组*/
			}/* end for */

			dPtr->aimPtr[ i ] = 0;/* 初始化训练样本目标输出存储数组*/

		}/* end for */

		for ( i = 0; i < numT; i++ ){
			for ( j = 0; j < numI; j++ ){
				dPtr->tSamPtrs[ j ][ i ] = 0.0; /* 初始化测试样本目标输出存储二位数组*/
			}/*  end for */

			dPtr->tAimPtr[ i ] =0;	/* 初始化测试样本目标输出存储二位数组	 */

		}/* end for */
	}/* end if */
	else printf( "\n不存在数据存储结构.\n" );
}/* end function DataInit */

/**
 * @brief		数据存储结构内存释放函数
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
 */
void DT_DatasDeInit( DT_TypeDefPtr dPtr )
{
	i32 i;
	i32 numI		= dPtr->numOfInput; /* 读取输入向量维数 */
	i32 numS		= dPtr->numOfSample; /* 读取训练样本总数 */
	i32 numT		= dPtr->numOfTSample; /* 读取测试样本总数	 */

	for( i = 0; i < numI; i++ ){
		free( dPtr->samPtrs[ i ]);	/* 释放存储训练样本数据二维数组	内存 */
		free( dPtr->tSamPtrs[ i ]);/* 释放存储测试样本数据二维数组内存 */
	}/* end for */

	free( dPtr->samPtrs ); /* 释放训练样本数据的指针数组 */
	free( dPtr->tSamPtrs ); /*	释放测试样本数据的指针数组 */
	free( dPtr->aimPtr );	/* 释放训练样本目标输出的指针数组 */
	free( dPtr->tAimPtr ); /*	释放测试样本目标输出的指针数组 */

	dPtr->creatLabel	= 0; /* 初始化创建标志 */
	dPtr->samParmLabel	= 0;/* 初始化创建标志 */
	dPtr->numOfInput = 0; /* 初始化输入维数 */
	dPtr->numOfSample	= 0; /* 初始化训练样本总数 */
	dPtr->numOfTSample = 0; /* 初始化测试样本总数 */

}/* end function DatasDeInit */

/**
 * @brief		训练样本显示信息函数
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
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
				printf( "\n训练样本输入 %d - %d:\n", temp3 + 1, temp4 + 10 );

				for ( i = 0; i < numI; i++ ){
					for ( j = temp3; j < temp4 + 10; j++ ){
						printf( "%-10.3lf ", dPtr->samPtrs[ i ][ j ] );
					}/* end for */
					printf( "\n" );
				}/* end for */

				printf( "\n目标输出：\n" );

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

			printf( "\n训练样本输入 %d - %d:\n", temp3 + 1, temp4 );

			for ( i = 0; i < numI; i++ ){
				for ( j = temp3; j < temp4; j++ ){
					printf( "%-10.3lf ", dPtr->samPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */

			printf( "\n目标输出：\n" );

			for ( j = temp3; j < temp4; j++ ){
				printf( "%-10d ", dPtr->aimPtr[ j ] );
			}/* end for */
			printf( "\n" );
		}/* end if */
	}
	else printf( "\n数据不存在！\n" );
}/* end function printSamples */

/**
 * @brief		测试样本显示信息函数
 * @param		DT_TypeDefPtr dPtr 样本存储结构体
 * @retval		无
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
			printf( "\n测试样本输入 %d - %d:\n", temp3 + 1, temp4 + 10 );

			for ( i = 0; i < numI; i++ ){
				for ( j = temp3; j < temp4 + 10; j++ ){
					printf( "%-10.3lf ", dPtr->tSamPtrs[ i ][ j ] );
				}/* end for */
				printf( "\n" );
			}/* end for */

			printf( "\n目标输出：\n" );

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

		printf( "\n测试样本输入 %d - %d:\n", temp3 + 1, temp4 );

		for ( i = 0; i < numI; i++ ){
			for ( j = temp3; j < temp4; j++ ){
				printf( "%-5.3lf ", dPtr->tSamPtrs[ i ][ j ] );
			}/* end for */
			printf( "\n" );
		}/* end for */

		printf( "\n目标输出：\n" );

		for ( j = temp3; j < temp4; j++ ){
			printf( "%-10d ", dPtr->tAimPtr[ j ] );
		}/* end for */
		printf( "\n" );

	}/* end if */
}
else printf( "\n数据不存在！\n" );
}/* end function printTestSamples */

void printDatasParams( DT_TypeDefPtr dPtr )
{
	if ( dPtr->samParmLabel == 1 ){
		printf( "\n输入维数: %d\n"
			"\n训练样本总数: %d\n"
			"\n测试样本总数: %d\n"
			"\n样本类别总数: %d\n",
			dPtr->numOfInput, dPtr->numOfSample,
			dPtr->numOfTSample, dPtr->numOfClasses );
	}/* end if */
	else printf( "\n参数未设置！\n" );
}/* end function printDatasParams */
