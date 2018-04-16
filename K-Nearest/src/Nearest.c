/**
   ******************************************************************************************************************************************************
   * @file                Nearest.c
   * @author          Morris
   * @version         V1.0
   * @date              2018年4月16日20:49:24 在VS2017上DeBug模式最终编译运行。
   * @brief             统计学习方法中的 k 近邻算法
   ******************************************************************************************************************************************************
   * @attention   （1）由于存在递归调用，在样本数量巨大时，并且K值较大时需增大程序所需栈（.exe文件的栈），
   *                                否则容易导致栈溢出错误（可考虑采用循环方式实现）。
   *                      （2）K=1时为最近邻搜索，无需考虑栈问题。
   *                      （3）程序在30万个随机生成样本中，对随机生成的不同数据搜索最近邻30万次正常运行。
   *                      （4）样本容量为10000时，K=5000运行正常，K=10000时出现栈溢出，更改程序栈后运行正常。
   *                      （5）样本容量5万，K=500，出现栈溢出，更改后正常。
   *                      （6）生成K-D树每个节点需排序一次，有待优化。
   *                      （7）搜索K近邻时，路径重复，有待优化。
   *
   ******************************************************************************************************************************************************
   */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "../inc/Nearest.h"
/**
 *@brief	判断节点存储索引是否已存储在近邻数组中
 *@param	i32 *vecPtr k个近邻数据列表中的索引存储数组
 *@param	i32 num 当前节点存储的数据列表中的索引
 *@param	i32 numOfElement 当前搜索的第n个近邻
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
 * @brief		欧氏距离函数
 * @param		d64 *inPtr 存储输入向量的数组指针
 * @param		d64 **vePtr 存储样本数据的二维数组指针
 * @param		i32 colum 样本数据二维数组中的列索引
 * @param		i32 numOfElment 输入数据维数
 * @retval		double类型，欧式距离值
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
 * @brief		曼哈顿距离函数
 * @param		d64 *inPtr 存储输入向量的数组指针
 * @param		d64 **vePtr 存储样本数据的二维数组指针
 * @param		i32 colum 样本数据二维数组中的列索引
 * @param		i32 numOfElment 输入数据维数
 * @retval		double类型，曼哈顿距离值
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
 * @brief		无穷距离函数
 * @param		d64 *inPtr 存储输入向量的数组指针
 * @param		d64 **vePtr 训练样本中的索引
 * @param		i32 colum 样本数据二维数组中的列索引
 * @param		i32 numOfElment 输入数据维数
 * @retval		double类型 无穷（q=无穷）距离值
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
 * @brief		更新当前最近邻函数
 * @param		KNN_NdTypeDefPtr tnPtr 节点结构体指针
 * @param		KNN_PrmTypdeDefPtr prmPtr 算法参数结构体指针
 * @param		DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval		无
*/
static void KNN_NearestDistance( 
	KNN_NdTypeDefPtr tnPtr, 
	KNN_PrmTypdeDefPtr prmPtr, 
	const DT_TypeDefPtr dPtr )
{
	  d64 temp;/* 距离临时变量 */

	  if ( !__isInList( prmPtr->knnIndexPtr, tnPtr->index,  prmPtr->kTimes ) ){ /*判断当前节点是否已被归为近邻 */

		  temp = EuclideanDistance( 
			  prmPtr->inPtr, /* 输入数据 */
			  dPtr->samPtrs, /* 样本数据存储二维数组 */
			  tnPtr->index, /* 当前节点存储的索引值 */
			  dPtr->numOfInput );/* 输入数据维数*/

		  if ( prmPtr->dist >= temp ){/* 判断输入与节点距离是否小于当前最小距离*/

			  prmPtr->dist = temp;/*更新距离*/
			  prmPtr->knnIndexPtr[ prmPtr->kTimes ] = tnPtr->index;/*存储节点索引*/

		  }/* end if */
	  }/* end if */
}/* end function KNN_NearestDistance */

/**
  * @brief		构造k-d树函数
  * @param	KNN_NdTypeDefPtr *tnPtrs k-d树结点结构体指针
  * @param	KNN_NdPrmTypeDefPtr npPtr 生成结点所需参数结构体指针
  * @param	DT_TypeDefPtr dPtr 样本数据存储结构体指针
  * @retval		无
  */
static void KNN_KdTreeCreat( 
	KNN_NdTypeDefPtr *tnPtrs, 
	KNN_NdPrmTypeDefPtr npPtr,
	const DT_TypeDefPtr dPtr 
)
{
	  i32 i; /* 循环临时变量 */
	  i32 midium;/* 中位数临时变量	 */
	  i32 surplurs;/* 子节点样本个数临时变量 */
	  KNN_NdPrmTypeDef nodeParam;/* 生成子节点所需参数结构体变量	*/

	  *tnPtrs = ( KNN_NdTypeDefPtr )malloc( sizeof ( KNN_NdTypeDef ) ); /* 动态分配一个节点内存 */

	  if( *tnPtrs != NULL ){ /* 判断节点内存是否分配成功 */

			( *tnPtrs )->dimention = npPtr->deep % dPtr->numOfInput; /* 根据节点深度计算切分点选择维度  */

			if( npPtr->samSurplus > 1 ){ /* 判断该节点对应样本空间样本个数 */
				  DT_sorftSampleSequence(
					  dPtr,
					  npPtr->sPtr, 
					  ( *tnPtrs )->dimention, 
					  npPtr->samSurplus ); /* 根据当前切分点维度对该节点所对应样本进行排序 */                                                                                                              
			}/* end if */

			midium = npPtr->samSurplus / 2; /* 计算中位数 */
			( *tnPtrs )->index = npPtr->sPtr[ midium ];	/* 存储中位数对应数据索引	 */
			surplurs = midium;

			if( surplurs == 0 ){	 /* 判断样本剩余个数是否为0 */
				  ( *tnPtrs )->leftChildPtr = NULL; /* 当前节点作为叶节点，不再生产左子节点 */
			}/* end if */
			else{
				  nodeParam.deep = npPtr->deep + 1;  /* 下一层深度 */
				  nodeParam.samSurplus = surplurs;	 /* 左子节点对应样本空间样本个数 */
				  nodeParam.sPtr = ( i32 * )malloc( sizeof( i32 ) * nodeParam.samSurplus );/* 左子节点对应样本数据索引存储数组 */

				  for( i = 0; i < nodeParam.samSurplus; i++ ){
						nodeParam.sPtr[ i ] = npPtr->sPtr[ i ];/* 该节点左子节点对应样本数据索引数组*/
				  }/* end for */

				  KNN_KdTreeCreat( ( &( *tnPtrs )->leftChildPtr ), &nodeParam, dPtr );	/* 递归调用生成左子节点 */
				  free( nodeParam.sPtr );/* 释放左子节点索引数组指针*/

			}/* end else */

			if( npPtr->samSurplus > 1 ){	/* 判断该节点对应样本子空间样本个数 */
				  surplurs = npPtr->samSurplus - surplurs - 1;

				  if( surplurs == 0 ){
						( *tnPtrs )->rightChildPtr = NULL;/* 当前节点作为叶节点，不再生成右子节点*/
				  }/* end if */
				  else{
						nodeParam.samSurplus = surplurs;/*右子节点对应样本空间样本个数*/
						nodeParam.sPtr = ( i32 * )malloc( sizeof( i32 ) * nodeParam.samSurplus );/* 右子节点对应样本数据索引存储数组 */

						for( i = 0; i < nodeParam.samSurplus; i++ ){
							  nodeParam.sPtr[ i ] = npPtr->sPtr[ midium + 1 + i ];
						}/* end for */

						KNN_KdTreeCreat( &( ( *tnPtrs )->rightChildPtr ), &nodeParam, dPtr );/* 递归生成右子节点*/
						free( nodeParam.sPtr );/* 释放左子节点索引数组指针*/
				  }/* end else */
			}/* end if */
			else{
				  ( *tnPtrs )->rightChildPtr = NULL;
			}/* end else */
	  }/* end if */
	  else{
			printf( "\n错误：kdTreeCreat() 内存不足！\n" );
			exit( -1 );
	  }/* end else */
}/* end function kdTreeCreat */

/**
 * @brief		构造k近邻算法函数
 * @param		KNN_TypeDefPtr nPtr k近邻算法结构体指针
 * @param		DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval		无
 */
void KNN_NearestCreat( 
	KNN_TypeDefPtr nPtr , 
	const DT_TypeDefPtr dPtr )
{
	  i32 i;
	  KNN_NdPrmTypeDef nodeParam;

	  if( dPtr->TrainDataEntered == 1 && nPtr->rootPtr == NULL ){

			nPtr->rootPtr = ( KNN_NdTypeDefPtr )malloc( sizeof( KNN_NdTypeDef  ) );/* 根节点 */

			if( nPtr->rootPtr != NULL ){ /*判断根节点内存分配是否成功*/

				  nodeParam.deep = 0;/* 根节点深度 */
				  nodeParam.samSurplus = dPtr->numOfSample;/* 根节点对应样本个数 */
				  nodeParam.sPtr = ( i32 * )malloc( sizeof( i32 ) * nodeParam.samSurplus );/* 根节点对应样本数据索引数组 */

				  for( i = 0; i < nodeParam.samSurplus; i++ ){
						nodeParam.sPtr[ i ] = i;
				  }/* end for */

				  printf( "\n正在生成算法模型...\n" );

				  KNN_KdTreeCreat( &(nPtr->rootPtr), &nodeParam, dPtr );/*生成 kd 树*/
				  free( nodeParam.sPtr );/* 释放临时数组内存 */

				  nPtr->treeLabel = 1;
				  printf( "\n成功生成算法模型！\n" );

			}/* end if */
			else{
				  printf("\n错误：NearestCreat() 内存不足!\n");
				  exit( -1 );/*退出应用程序*/
			}/* end else */
	  }/* end if */
	  else{
			if( dPtr->TrainDataEntered != 1 ) printf( "\n无可用数据，请输入样本!\n" );
			nPtr->rootPtr = NULL;
	  }/* end else */
}/* end function NearestCreat */

/**
 * @brief		递归搜索叶节点函数
 * @param		KNN_NdTypeDefPtr tnPtr k-d树结点结构体指针
 * @param		KNN_PrmTypdeDefPtr prmPtr 算法参数结构体指针
 * @param		DT_TypeDefPtr dPtr 样本数据存储结构体指针
 * @retval		无
 */
static void KNN_SearchLeafNode( 
	KNN_NdTypeDefPtr tnPtr, 
	KNN_PrmTypdeDefPtr prmPtr, 
	const DT_TypeDefPtr dPtr )
{
	  prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = tnPtr;/* 将当前节点压栈，记录搜索叶节点路径 */

	  if( tnPtr->leftChildPtr == NULL && tnPtr->rightChildPtr == NULL ) return;/* 如果当前节点为叶节点，则退出递归 */

	  if( prmPtr->inPtr[ tnPtr->dimention ] < dPtr->samPtrs[ tnPtr->dimention ][ tnPtr->index ] ){ /* 判断输入与当前节点存储样本数据当前维大小*/
			if( tnPtr->leftChildPtr != NULL ){/* 若当前节点的左子节点不为空，移动至左节点*/

				  prmPtr->KNN_Stack.top++;/* 栈指针增加 */
				  KNN_SearchLeafNode( tnPtr->leftChildPtr, prmPtr, dPtr );/* 搜索叶节点 */

			}/* end if */
			else return;/* 当前节点是伪叶节点，退出递归 */
	  }/* end if */
	  else if( tnPtr->rightChildPtr != NULL ){/* 若当前节点的右子节点不为空，移动至右节点*/

			prmPtr->KNN_Stack.top++;/* 栈指针增加 */
			KNN_SearchLeafNode( tnPtr->rightChildPtr, prmPtr, dPtr );/* 搜索叶节点 */

	  }/* end else if */
	  else return;/* 当前节点是伪叶节点，退出递归 */
}/* end function KNN_SearchLeafNode */

/**
 * @brief		搜索最近邻递归函数
 * @param		KNN_NdTypeDefPtr tnPtr k-d树结点结构体指针
 * @param		KNN_PrmTypdeDefPtr prmPtr 算法参数结构体指针
 * @param		DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval		无
*/
static void KNN_SearchNearest( 
	KNN_NdTypeDefPtr tnPtr, 
	KNN_PrmTypdeDefPtr prmPtr, 
	const DT_TypeDefPtr dPtr )
{
	  if( prmPtr->KNN_Stack.top >= 0 ){ /* 判断当前节点是否是根节点的父节点 */

			KNN_NearestDistance( tnPtr, prmPtr, dPtr );/* 计算当前节点与输入点距离 */

			if( fabs( prmPtr->inPtr[ tnPtr->dimention ] - 
				dPtr->samPtrs[ tnPtr->dimention ][ tnPtr->index ] ) 
				< prmPtr->dist  ){/* 判断以输入和当前最近点之间的距离为半径的超球体与当前节点的另一子节点是否相交 */

				  if( prmPtr->inPtr[ tnPtr->dimention ] < 
					  dPtr->samPtrs[ tnPtr->dimention ][ tnPtr->index ] ){/* 若是由左子节点移动到当前节点 */

						if( tnPtr->rightChildPtr != NULL ){/* 若当前节点不是伪叶节点 */
							  KNN_SearchLeafNode( tnPtr->rightChildPtr, prmPtr, dPtr );/* 以当前节点的右子节点为根节点搜索叶节点 */
						}/* end if */
						else{/*若当前节点为伪叶节点*/
							prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = NULL;
							prmPtr->KNN_Stack.top--;/* 退回当前子节点的父节点 */
						}/* end else */
				  }/* end if */
				  else{/* 若是由右子节点移动到当前节点 */
						if( tnPtr->leftChildPtr != NULL ){/* 当前节点不是伪叶节点*/
							KNN_SearchLeafNode( tnPtr->leftChildPtr, prmPtr, dPtr );/* 以当前节点的左子节点为根节点搜索叶节点 */
						 }/* end if */
						else{/* 若当前节点是为叶节点 */
								prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = NULL;
								prmPtr->KNN_Stack.top--;/* 退回当前子节点的父节点 */
						}/* end else */
				  }/* end else */
			}/* end if */
			else{/* 若不相交 */
				prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ] = NULL;
				prmPtr->KNN_Stack.top--;/* 直接退回当前节点的父节点 */
			}/* end else */

			KNN_SearchNearest( 
				prmPtr->KNN_Stack.kStkPtrs[ prmPtr->KNN_Stack.top ],/*若搜索了叶节点则栈顶为叶节点，否则栈顶为当前节点的父节点 */
				prmPtr, dPtr );

	  }/* end if */
	  else return;/* 退出最近邻搜索 */
}/* end function KNN_SearchNearest */

/**
 * @brief		搜索K近邻函数
 * @param		KNN_TypeDefPtr nPtr 算法结构体指针
 * @param		DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval		无
*/
void KNN_SearchKNearest( 
	KNN_TypeDefPtr nPtr, 
	const DT_TypeDefPtr dPtr )
{
	if ( nPtr->treeLabel == 1 && nPtr->k != 0 && nPtr->parameters.inPtr != NULL ){
		while ( nPtr->parameters.kTimes < nPtr->k ){/* k次搜索 */

			nPtr->parameters.dist = +INFINITY;

			KNN_SearchLeafNode( nPtr->rootPtr, &nPtr->parameters, dPtr );/* 搜索叶节点 */
			KNN_SearchNearest(
				nPtr->parameters.KNN_Stack.kStkPtrs[ nPtr->parameters.KNN_Stack.top ], /* 叶节点 */
				&nPtr->parameters, dPtr );/* 搜索最近邻 */

			nPtr->parameters.kTimes++;
			nPtr->parameters.KNN_Stack.top = 0;/* 栈指针指向栈底 */
		}/* end while */

		nPtr->parameters.kTimes = 0;
	}
	else{ 
		if( nPtr->treeLabel != 1 ) printf( "\n错误：k-d 树不存在！\n" );
		else if( nPtr->k != 1) printf( "\n错误：请设置k值!\n" );
		else printf( "\n请输入数据点！\n" );
	}/* end else */
}/* end function KNN_SearchKNearest */

/**
  * @brief		初始化算法结构体参数函数
  * @param	KNN_TypeDefPtr nPtr 算法结构体指针
  * @param	DT_TypeDefPtr dPtr 数据存储结构体指针
  * @retval		无
  */
void KNN_NearestInit( KNN_TypeDefPtr nPtr )
{
	i32 i;

	for ( i = 0; i < KNN_STACK_SIZE; i++ ){
		nPtr->parameters.KNN_Stack.kStkPtrs[ i ] = NULL; /* 初始化栈 */
	}/* end for */

	/*初始化参数*/
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
 * @brief		对输入数据进行分类函数
 * @param		KNN_TypeDefPtr nPtr 算法结构体指针
 * @param		DT_TypeDefPtr dPtr 数据存储结构体指针
 * @retval		int变量，输入数据类别
 */
i32 KNN_ClassifyInputData( 
	KNN_TypeDefPtr nPtr, 
	const DT_TypeDefPtr dPtr )
{

	i32 i, KNN_class, count = 0, max = 0;

	if ( nPtr->treeLabel == 1  && nPtr->k != 0 && dPtr->numOfClasses != 0 && nPtr->parameters.inPtr != NULL ){
		i32 *freqPtr = ( i32 * )malloc( sizeof( i32 ) * ( dPtr->numOfClasses + 1 ) );/* 用于计算k个近邻中某一类出现频数 */
		i32 *maxFreqPtr = ( i32 * )malloc( sizeof( i32 ) * dPtr->numOfClasses );/* 存储最大频数的类别 */

			/* 初始化 */
		for ( i = 0; i < dPtr->numOfClasses + 1; i++ ){
			freqPtr[ i ] = 0;

			if ( i < dPtr->numOfClasses ){
				maxFreqPtr[ i ] = 0;
			}/* end if */
		}/* end for */

		KNN_SearchKNearest( nPtr, dPtr );/* 搜索k个近邻 */

		for ( i = 0; i < nPtr->k; i++ ){
			freqPtr[ dPtr->aimPtr[ nPtr->parameters.knnIndexPtr[ i ] ] ]++;/* 统计k个近邻中每个类别的频数 */
		}/* end for */

		for ( i = 1; i < dPtr->numOfClasses + 1; i++ ){

			if ( freqPtr[ i ] > max ){/* 寻找频数最大的类别 */
				max = freqPtr[ i ];
				count = 1;
				maxFreqPtr[ 0 ] = i;
			}/* end if */
			else if ( freqPtr[ i ] == max && freqPtr[ i ] != 0 ){/* 最大频数相同的类别 */
				count++;
				maxFreqPtr[ count - 1 ] = i;
			}/* end else if */
		}/*end for */

		KNN_class = maxFreqPtr[ rand( ) % count ];/* 在 count 个最大频数相同的类别中随机分类 */

		free( freqPtr );
		free( maxFreqPtr );/* 释放内存 */

		return KNN_class;/* 返回输入的类别 */
	}/* end if */
	else{
		if( !nPtr->treeLabel ) printf( "\n错误：k-d树未生成！\n" );
		else if( !nPtr->k )printf( "\n请设置k值！\n" );
		else if( nPtr->parameters.inPtr == NULL ) printf( "\n请输入数据！\n" );
		else printf( "\n请设置类别总数！\n" );
		return 0;
	}/* end else */
}/* end function KNN_ClassifiedInput */

/**
 * @brief		测试模型分类性能函数，性能由k值决定
 * @param		KNN_TypeDefPtr nPtr 算法参数结构体指针
 * @param		DT_TypeDefPtr dPtr 样本数据存储结构体指针
 * @retval		无
 */
void KNN_TestModelPerformence( 
	KNN_TypeDefPtr nPtr, 
	const DT_TypeDefPtr dPtr )
{
	i32 i, j, correct = 0, error = 0;
	d64 correctRate, errorRate;
	if ( nPtr->treeLabel == 1  && dPtr->TestDataEntered == 1&& dPtr->numOfClasses != 0 ){
		printf( "\n算法测试...\n" );

		if( nPtr->parameters.inPtr == NULL ){
			nPtr->parameters.inPtr = ( d64 * )malloc( sizeof( d64 ) * dPtr->numOfInput );
		}/* end if */

		for ( i = 0; i < dPtr->numOfTSample; i++ ){
			for ( j = 0; j < dPtr->numOfInput; j++ ){
				nPtr->parameters.inPtr[ j ] = dPtr->tSamPtrs[ j ][ i ];/* 导入测试数据*/
			}/* end inner for */

			if ( dPtr->tAimPtr[ i ]  ==  KNN_ClassifyInputData( nPtr, dPtr ) ){
				correct++;/* 分类正确数增加 */
			}/* end if */
		}/* end outer for */

		correctRate = ( ( d64 )correct / dPtr->numOfTSample ) * 100.0;/* 测试样本分类正确率*/
		errorRate = 100 - correctRate;/* 错误率 */

		printf( "\n测试样本集正确率： %.2lf%%\n"
			"\n测试样本集错误率： %.2lf%%\n", correctRate, errorRate );
	}
	else{
		if ( !nPtr->treeLabel ) printf( "\n错误：k-d树未生成！\n" );
		else if ( !dPtr->TestDataEntered ) printf( "\n错误：无可用测试样本！\n" );
		else printf( "\n请设置样本类别总数!\n" );
	}/* end else */
}/* end function KNN_TestModelPerformence */

/**
 * @brief		线性扫描函数
 * @param		KNN_TypeDefPtr nPtr 算法结构体指针
 * @param		数据存储结构体指针
 * @retval		无
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
				dPtr->numOfInput ); /* 计算输入与每个样本的距离 */

			linerIndPtr[ i ] = i; /* 存储索引 */
		}/* end for */

		/* 对距离进行排序 */
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

		printf( "\n线性扫描k个距离最近数据索引：\n" );

		for ( i = 0; i < nPtr->k; i++ ){
			printf( "(%d) %d\n", i + 1, linerIndPtr[ i ] );
		}/*end for */

		free( linerPtr );
		free( linerIndPtr );/* 释放内存*/
	}/* end if */
	else{
		printf( "\n错误：无可用训练样本！\n" );
	}/* end else */
}/* end function KNN_LinnerScan */

void KNN_SetKNNParameters( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr )
{
	i32 temp;
	if ( dPtr->samParmLabel  == 1){
		do{
			printf( "\n输入K值( 小于或等于训练样本总数%d, 退出: -1 )：", dPtr->numOfSample );
			scanf_s( "%d", &temp );

			printf( "\n" );

			if ( temp == -1 ) break;

			if ( temp < 0 ) printf( "\n输入错误: 请输入大于0的数值！\n" );

			if ( temp >  dPtr->numOfSample )printf( "\n输入错误: 请输入小于%d的数值！\n", dPtr->numOfSample );
		} while ( temp < 0 || temp > dPtr->numOfSample );

		nPtr->k = temp;

		if ( nPtr->parameters.knnIndexPtr != NULL ){
			free( nPtr->parameters.knnIndexPtr );
		}/* end if */

		nPtr->parameters.knnIndexPtr = ( i32 * )malloc( sizeof( i32 ) * nPtr->k );/* 动态分配内存存储k个近邻索引*/

		for ( temp = 0; temp < nPtr->k; temp++ ){
			nPtr->parameters.knnIndexPtr[ temp ] = -1;
		}/* end for */
	}/* end if */
	else printf( "\n设置错误: 请设置数据结构信息！\n" );

}/* end function KNN_SetKNNParameters */

void KNN_InputData( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr)
{
	i32 i;
	if ( dPtr->samParmLabel == 1 ){
		if ( nPtr->parameters.inPtr == NULL ){
			nPtr->parameters.inPtr = ( d64 * )malloc( sizeof( d64 ) * dPtr->numOfInput );
		}/*end if */

		printf( "\n输入数据：\n" );

		for( i = 0; i < dPtr->numOfInput; i++ ){
			scanf_s( "%lf", &nPtr->parameters.inPtr[ i ] );
		}/* end for */
	}/* end if */
	else printf( "\n请设置数据信息！\n" );
}/* end function KNN_InputData */

void KNN_printData( KNN_TypeDefPtr nPtr, const DT_TypeDefPtr dPtr )
{
	i32 i;
	if( nPtr->parameters.inPtr == NULL ){
		printf( "\n无\n" );
	}/* end if */
	else{
		printf( "\n输入数据：\n" );
		for( i = 0; i < dPtr->numOfInput; i++ ){
			printf( "%.3lf\n", nPtr->parameters.inPtr[ i ] );
		}/* end for */
	}/* end else */
}/* end function KNN_printData */

void KNN_PrintConmand( i32 *chose )
{
	printf( "\n1.  设置数据存储参数.\n"
			"2.  显示数据存储参数.\n"
			"3.  生成数据存储结构.\n"
			"4.  初始化数据结构体.\n"
			"5.  设置k值.\n"
			"6.  输入训练样本.\n"
			"7.  输入测试样本.\n"
			"8.  显示训练样本.\n"
			"9.  显示测试样本.\n"
			"10. 生成k-d树.\n"
			"11. k-d树搜索k近邻.\n"
			"12. 线性扫描搜索k近邻.\n"
			"13. 测试模型性能.\n"
			"14. 输入识别数据.\n"
			"15. 显示输入数据.\n"
			"16. KNN分类.\n"
			"0.  退出.\n"
			"选择序号：");
	scanf_s( "%d", chose );
}/* end function KNN_PrintConmand */

/********************************************************************************************* END OF FILE *********************************************************************************************/