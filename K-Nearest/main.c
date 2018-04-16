#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "./inc/Data.h"
#include "./inc/Nearest.h" 
 
#define	MODE					1 

 int main( void ) 
 { 
	 i32 classOfInput;
	 i32 i;

	 DT_TypeDef kND;
	 KNN_TypeDef kNN;
#if MODE
	 DT_SetSampleParameters( &kND );
	 DT_DatasCreat( &kND );
	 DT_DatasInit( &kND );
	 DT_InputTrainSamples( &kND );
	 DT_InputTestSamples( &kND );
#if 0
	 DT_PrintTrainSamples( &kND ); /* 用于显示训练样本数据，若需要可激活 */
	 DT_PrintTestSamples( &kND );
#endif

	 KNN_NearestInit( &kNN );
	 KNN_NearestCreat( &kNN, &kND );
	 KNN_SetKNNParameters( &kNN, &kND );
	 KNN_InputData( &kNN, &kND );
	 KNN_printData( &kNN,  &kND );

#if 1 /* 对k近邻搜索，显示在数据kND中的索引，若需要可激活编译 */
	 KNN_SearchKNearest( &kNN, &kND );
	 printf( "\nKNN扫描K个最近邻索引:\n" );
	 for ( i = 0; i < kNN.k; i++ ){
		 printf( "(%d) %d\n", i, kNN.parameters.knnIndexPtr[ i ] );
	 }/* end for */
#endif

#if 0 /* 线性扫描搜索k个近邻，可用于验证k-d树搜索结果，若需要可激活编译 */
	KNN_LinnerScan( &kNN,  &kND );
#endif

#if 0 /* 用于测试样本的分类，输出测试样本分类错误和正确率，若需要可激活编译 */
	KNN_TestModelPerformence( &kNN,  &kND );
#endif

#if 0  /* 对输入进行分类 */
	classOfInput = KNN_ClassifyInputData( &kNN, &kND );
	printf( "\n输入数据所属类别：%d\n",  classOfInput );
#endif

#endif

#if !MODE /* 在DOS窗口选择指令，进行操作若需要可将MODE宏定义为0 */
	 i32 chose;
	 i32 i;
	 kNN.parameters.knnIndexPtr = NULL;
	 kNN.parameters.inPtr = NULL;
	 kNN.rootPtr = NULL;
	 do{
		 KNN_PrintConmand( &chose );

		 switch ( chose ){
		 case 1:
			 DT_SetSampleParameters( &kND );
			 break;
		 case 2:
			 printDatasParams( &kND );
			 break;
		 case 3:
			 DT_DatasCreat( &kND );
			 break;
		 case 4:
			 DT_DatasInit( &kND );
			 break;
		 case 5:
			 KNN_SetKNNParameters( &kNN, &kND );
			 break;
		 case 6:
			 DT_InputTrainSamples( &kND );
			 break;
		 case 7:
			 DT_InputTestSamples( &kND );
			 break;
		 case 8:
			 DT_PrintTrainSamples( &kND );
			 break;
		 case 9:
			 DT_PrintTestSamples( &kND );
			 break;
		 case 10:
			 KNN_NearestInit( &kNN, &kND );
			 KNN_NearestCreat( &kNN, &kND );
			 break;
		 case 11:
			 KNN_SearchKNearest( &kNN, &kND );
			 printf( "\nKNN扫描K个最近邻索引:\n" );
			 for ( i = 0; i < kNN.k; i++ ){
				 printf( "%d\n", kNN.parameters.knnIndexPtr[ i ] );
			 }/* end for */
			 break;
		 case 12:
			 KNN_LinnerScan( &kNN, &kND );
			 printf( "\n线性扫描K个最近邻索引:\n" );
			 for ( i = 0; i < kNN.k; i++ ){
				 printf( "%d\n", kNN.parameters.knnIndexPtr[ i ] + 1 );
			 }/* end for */
			 break;
		 case 13:
			 KNN_TestModelPerformence( &kNN, &kND );
			 break;
		 case 14:
			 KNN_InputData( &kNN, &kND );
			 break;
		 case 15:
			 KNN_printData( &kNN, &kND );
			 break;
		 case 16:
			 printf( "\n输入数据所属类别：%d\n", KNN_ClassifyInputData( &kNN, &kND ) );
			 break;
		 }/* end switch */

	 } while ( chose != 0 );/* end while */
#endif
	 return 0;

}/* end main function */ 
