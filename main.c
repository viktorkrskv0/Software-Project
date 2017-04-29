/*
 * main.c
 *
 *  Created on: Apr 27, 2017
 *      Author: viktor
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "unit_test_util.h"
#include "SPPoint.h"
#include "spKDArray_test_util.h"

//-------------------------------------------------------------------------------------------------




SPConfig publicConfig;
int totalNumberOfImages;
/*
char* spGetImagesDirectory(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return "";
	}
	return config.spImagesDirectory;;
}

char* spGetImagesPrefix(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return "";
	}
	return config.spImagesPrefix;;
}

char* spGetImagesSuffix(const SPConfig config, SP_CONFIG_MSG* msg){
	assert(*msg); //err
	*msg = SP_CONFIG_SUCCESS;
	if (!config){
		*msg = SP_CONFIG_INVALID_ARGUMENT;
		return "";
	}
	return config.spImagesSuffix;;
}
*/
//these functions are the functions that I test
// when you finish delete all these functions and put them in the util test file for kdtree
char* concat(const char *s1, const char *s2)
{
	//input: two strings
	//output: the strings concatinated
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* convertIntToStr(int number){
	//input: integer
	//output: a string built from the int
	int length = 0;
	int number1 = number;
	int number2 = number;
	char* strNum;
	while(number1 > 0){
		number1 = number1 / 10;
		length++;
	}
	strNum = (char*) malloc(sizeof(char)*length + 1);
	sprintf(strNum,"%d",number2);
	return strNum;
}

char* buildAddress(int index){
	char* tmp0 = concat(publicConfig.spImagesDirectory,publicConfig.spImagesPrefix);
	char* indexStr = convertIntToStr(index);
	char* tmp1 = concat(tmp0,indexStr);
	char* tmp2 = concat(tmp1,publicConfig.spImagesSuffix);
	free(tmp0);
	free(indexStr);
	free(tmp1);
	return tmp2;
}

char* buildFeatAddress(int index){
	char* tmp0 = concat(publicConfig.spImagesDirectory,publicConfig.spImagesPrefix);
	char* indexStr = convertIntToStr(index);
	char* tmp1 = concat(tmp0,indexStr);
	char* tmp2 = concat(tmp1,".feats");
	free(tmp0);
	free(indexStr);
	free(tmp1);
	return tmp2;
}

// This is a helper function which checks if two files are identical
static bool identicalFiles(const char* fname1, const char* fname2) {
	FILE *fp1, *fp2;
	fp1 = fopen(fname1, "r");
	fp2 = fopen(fname2, "r");
	char ch1 = EOF, ch2 = EOF;

	if (fp1 == NULL) {
		return false;
	} else if (fp2 == NULL) {
		fclose(fp1);
		return false;
	} else {
		ch1 = getc(fp1);
		ch2 = getc(fp2);

		while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
			ch1 = getc(fp1);
			ch2 = getc(fp2);
		}
		fclose(fp1);
		fclose(fp2);
	}
	if (ch1 == ch2) {
		return true;
	} else {
		return false;
	}
}

void writeFeatsToFile(FILE* f, SPPoint** feats,int index, int numOfFeats){
	// input: file, features, index of the img, number of features to write for that img index.
	// output: writes to file the features
	// the first line is the index, the second is number of features, the rest is the features data
	int i, j, dim;
	char* indexStr = convertIntToStr(index);
	char* numOfFeatsStr = convertIntToStr(numOfFeats);
	fputs(indexStr,f);
	fputs("\n",f);
	fputs(numOfFeatsStr,f);
	fputs("\n",f);
	free(indexStr);
	free(numOfFeatsStr);

	for(i = 0; i < numOfFeats; i++){
		dim = spPointGetDimension(feats[i]);
		for(j = 0; j < dim; j++){
			fprintf(f,"%lf",spPointGetAxisCoor(feats[i], j));
			fputs("\n",f);
		}
	}
}

//Vik
KD_ARRAY InitArray(SPPoint** pointArr, int size){
// input: gets an empty array pointer, mallocs it with the size 'size'
//and starts adding points
	KD_ARRAY kdArr;
	int numberOfImages = publicConfig.spNumOfImages;
	int dim = publicConfig.spPCADimension;
	int i = 0;
	int j = 0;
	int k = 0;
	int numOfFeatures;
	//pointArr = (SPPoint**)malloc(sizeof(SPPoint*)*size);// ??? did you allocate ok??? you are not sure about the only one * in the parenthasis
	FILE* f;
	char* featAddress;
	int index;
	int countPosition = 0; //helper index to write in the array
	for(i = 0; i < numberOfImages; i++){
		featAddress = buildFeatAddress(i);
		f = fopen(featAddress,"r");
		if(f == NULL){
			printf("could not open the file\n"); //need to change to the logger msgs
			printf("the feat Address is %s \n", featAddress);
			return kdArr;
		}
		fscanf(f,"%d",&index);
		fscanf(f,"%d",&numOfFeatures);
		for(j = 0; j < numOfFeatures; j++){
			double* data = (double*)malloc(sizeof(double)*numOfFeatures);
			pointArr[countPosition] = spPointCreate(data, dim,index);
			for(k = 0; k < dim; k++){
				fscanf(f,"%lf",&pointArr[countPosition]->data[k]);
			}
			countPosition++;
		}
		free(featAddress);
	}
	kdArr.size = size;
	kdArr.arr = pointArr;
	//kdArr.mat = initMatrix(kdArr);
	return kdArr;
}

//--------------------------------------------------------------------------------------------------
//these are the test functions
static bool concatTest() {
	char* s1 = "Hello";
	char* s2 = "World";
	char* s3 = concat(s1,s2);
	ASSERT_TRUE(strcmp(s3,"HelloWorld") == 0);
	ASSERT_TRUE(strlen(s3)==10);
	return true;
}

static bool convertIntToStrTest(){
	int num1 = 123;
	int num2 = 3;
	int num3 = 1234567890;
	char* str1 = convertIntToStr(num1);
	char* str2 = convertIntToStr(num2);
	char* str3 = convertIntToStr(num3);
	ASSERT_TRUE(strcmp(str1,"123") == 0);
	ASSERT_TRUE(strcmp(str2,"3") == 0);
	ASSERT_TRUE(strcmp(str3,"1234567890") == 0);
	free(str1);
	free(str2);
	free(str3);
	return true;
}

static bool buildAddressTest(){
	publicConfig.spImagesDirectory = "images/";
	publicConfig.spImagesPrefix = "img";
	publicConfig.spImagesSuffix = ".jpg";
	char* address1 = buildAddress(1);
	char* address2 = buildAddress(2);
	char* address3 = buildAddress(3);
	ASSERT_TRUE(strcmp(address1,"images/img1.jpg") == 0);
	ASSERT_TRUE(strcmp(address2,"images/img2.jpg") == 0);
	ASSERT_TRUE(strcmp(address3,"images/img3.jpg") == 0);
	free(address1);
	free(address2);
	free(address3);
	return true;
}

static bool buildFeatAddressTest(){
	char* address1 = buildFeatAddress(1);
	char* address2 = buildFeatAddress(2);
	char* address3 = buildFeatAddress(3);
	ASSERT_TRUE(strcmp(address1,"images/img1.feats") == 0);
	ASSERT_TRUE(strcmp(address2,"images/img2.feats") == 0);
	ASSERT_TRUE(strcmp(address3,"images/img3.feats") == 0);
	free(address1);
	free(address2);
	free(address3);
	return true;
}

static bool writeFeatsToFileTest(){
	//allocating five points
	//point arr is the features
	int i;
	int j;
	FILE* f_feats = fopen("f_feats.txt","w+");
	SPPoint** pointArr = (SPPoint**)malloc(sizeof(SPPoint*)*5);
	for(i = 0; i < 5; i++){
		double* data = (double*)malloc(sizeof(double)*5);
		for(j = 0; j < 5; j++){
			data[j] =  i*j;
		}
		pointArr[i] = spPointCreate(data,5,2);
	}
	writeFeatsToFile(f_feats,pointArr,2,5);
//	identicalFiles("f_feats.txt","f_test.txt") ? printf("identical\n") : printf("not indentical\n");
//DELETE AFTER
	ASSERT_FALSE(identicalFiles("f_feats.txt","f_test.txt"));
	for(i = 0; i < 5; i++){
		spPointDestroy(pointArr[i]);
	}
	free(pointArr);
	return true;
}

static bool InitArrayTest(){
	//this test depend on a pre-written feats files
	publicConfig.spNumOfImages = 3;
	publicConfig.spPCADimension = 3;
	SPPoint** pointArr = (SPPoint**)malloc(sizeof(SPPoint*)*9);
	KD_ARRAY kdArr = InitArray(pointArr,9);
	SPPoint** pointArrTest = (SPPoint**)malloc(sizeof(SPPoint*)*9);
	double data1[] = {0.000,1.000,2.000};
	double data2[] = {3.000,4.000,5.000};
	double data3[] = {6.000,7.000,8.000};
	double data4[] = {0.000,1.000,2.000};
	double data5[] = {3.000,4.000,5.000};
	double data6[] = {6.000,7.000,8.000};
	double data7[] = {0.000,1.000,2.000};
	double data8[] = {3.000,4.000,5.000};
	double data9[] = {6.000,7.000,8.000};
	pointArrTest[0] = spPointCreate(data1,3,1);
	pointArrTest[1] = spPointCreate(data2,3,1);
	pointArrTest[2] = spPointCreate(data3,3,1);
	pointArrTest[3] = spPointCreate(data4,3,2);
	pointArrTest[4] = spPointCreate(data5,3,2);
	pointArrTest[5] = spPointCreate(data6,3,2);
	pointArrTest[6] = spPointCreate(data7,3,3);
	pointArrTest[7] = spPointCreate(data8,3,3);
	pointArrTest[8] = spPointCreate(data9,3,3);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[0],kdArr.arr[0])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[1],kdArr.arr[1])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[2],kdArr.arr[2])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[3],kdArr.arr[3])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[4],kdArr.arr[4])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[5],kdArr.arr[5])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[6],kdArr.arr[6])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[7],kdArr.arr[7])==0);
	ASSERT_TRUE(spPointL2SquaredDistance(pointArrTest[8],kdArr.arr[8])==0);
	//isIdentical()
	return true;
}

int main(){
	//this is the tests running -
	RUN_TEST(concatTest);
	RUN_TEST(convertIntToStrTest);
	RUN_TEST(buildAddressTest);
	RUN_TEST(buildFeatAddressTest);
	RUN_TEST(writeFeatsToFileTest);
	RUN_TEST(InitArrayTest);
	//RUN_TEST(ConfigNonValidVarTest);
	//RUN_TEST(ConfigNonValidVarTest);
	//RUN_TEST(ConfigNonValidVarTest);
	return 0;
}
