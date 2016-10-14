#include<iostream>
#include <stdio.h>
#include <SOIL.h>

using namespace std;

typedef unsigned char u8;

struct rgb{
	u8 r;
	u8 g;
	u8 b;

	int PosX;
	int PosY;
};

inline rgb RgbColor(u8 R, u8 G, u8 B){
	rgb Result;
	Result.r = R;
	Result.g = G;
	Result.b = B;
	Result.PosX = 0;
	Result.PosY = 0;

	return Result;
}

inline rgb RgbColor(u8 R, u8 G, u8 B, int PosX, int PosY){
	rgb Result;
	Result.r = R;
	Result.g = G;
	Result.b = B;
	Result.PosX = PosX;
	Result.PosY = PosY;

	return Result;
}


inline bool operator ==(rgb Color1, rgb Color2){
	bool Result;
	if (Color1.r == Color2.r &&
		Color1.g == Color2.g &&
		Color1.b == Color2.b)
	{
		return(true);
	}
	else{
		return(false);
	}
}

void LoadImage(const char* FilePath){

	int width;
	int height;

	unsigned char* Image;
	Image = SOIL_load_image(
		FilePath,
		&width,
		&height,
		0,
		SOIL_LOAD_RGB);

	rgb* ColorsArray = (rgb*)calloc(width * height, sizeof(rgb));

	rgb Orange = RgbColor(232, 144, 18);
	rgb Yellow = RgbColor(245, 204, 30);

	u8* CurrentByte = Image;
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++){
			CurrentByte = Image + j * width * 3 + i * 3;
			rgb TempColor;
			TempColor.r = *CurrentByte;
			TempColor.g = *(CurrentByte + 1);
			TempColor.b = *(CurrentByte + 2);
			TempColor.PosX = i;
			TempColor.PosY = j;
			ColorsArray[j * width + i] = TempColor;
		}
	}

	//COUNTING ORANGES AND YELLOWS
	int CountOranges = 0;
	int CountYellows = 0;
	for (int i = 0; i < width * height; i++){
		if (ColorsArray[i] == Orange){
			CountOranges++;
		}
		else if (ColorsArray[i] == Yellow){
			CountYellows++;
		}
	}


	rgb* TempOrangesArray = (rgb*)calloc(CountOranges, (sizeof(rgb)));

	int TempOrCount = 0;
	for (int i = 0; i < width * height; i++){
		if (ColorsArray[i] == Orange){
			TempOrangesArray[TempOrCount] = ColorsArray[i];
			TempOrCount++;
		}
	}

	u8* TempPosString = (u8*)calloc(CountOranges + 1, sizeof(u8));
	for (int i = 0; i < CountOranges; i++){
		u8 Bukva = (TempOrangesArray[i].PosX) | (TempOrangesArray[i].PosY << 8);
		TempPosString[i] = Bukva;
	}
	TempPosString[CountOranges] = '\0';
	free(TempPosString);

	free(TempOrangesArray);

	/*
	u8* TempByteArray = (u8*)calloc(CountOranges + CountYellows + 1, sizeof(u8));
	int TempElementCount = 0;
	for (int i = 0; i < width * height; i++){
		if (ColorsArray[i] == Orange){
			TempByteArray[TempElementCount++] = '1';
		}
		else if (ColorsArray[i] == Yellow){
			TempByteArray[TempElementCount++] = '0';
		}
	}
	TempByteArray[TempElementCount] = '\0';
	free(TempByteArray);
	*/




	/*
	int TargetStrWidth = width;
	char* TempStr = (char*)calloc(TargetStrWidth, sizeof(char));
	for (int i = 0; i < TargetStrWidth; i++){
		TempStr[i] = *(Image + i);
	}

	for (int i = 0; i < 100; i++){
		char* TempStr2 = (char*)calloc(TargetStrWidth, sizeof(char));
		for (int j = 0; j < TargetStrWidth; j++){
			TempStr2[j] = TempStr[j] + i;
		}
		printf("%d: %s\n", i, TempStr2);
	}
	*/

	SOIL_free_image_data(Image);

	return;
}

int main(){

	LoadImage("C:/Users/GOREVOJD/Pictures/256.bmp");

	//FILE* fp = fopen("C:/Users/GOREVOJD/Pictures/256mono.bmp", "rb");
	//if (fp){
	//	fseek(fp, 0, SEEK_END);
	//	int FileSize = ftell(fp);
	//	rewind(fp);

	//	u8* Image = (u8*)malloc(FileSize + 1);
	//	fread(Image, FileSize, 1, fp);

	//	int TargetStrWidth = 400;
	//	u8* TempStr = (u8*)calloc(TargetStrWidth + 1, sizeof(u8));
	//	for (int i = 0; i < TargetStrWidth; i++){
	//		//u8* TargetByte = Image + FileSize - 1 - TargetStrWidth + i;
	//		u8* TargetByte = Image + i;
	//		TempStr[i] = *TargetByte;
	//	}
	//	TempStr[TargetStrWidth] = 0;

	//	for (int i = 0; i < 10; i++){
	//		u8* TempStr2 = (u8*)calloc(TargetStrWidth + 1, sizeof(u8));
	//		for (int j = 0; j < TargetStrWidth; j++){
	//			TempStr2[j] = TempStr[j] + i;
	//		}
	//		TempStr2[TargetStrWidth] = 0;

	//		cout << i << ": " << TempStr2 << endl;
	//		free(TempStr2);
	//	}

	//	free(TempStr);
	//	cout << 4 << endl;
	//}



	/*
	
	int TargetStrWidth = width;
	char* TempStr = (char*)calloc(TargetStrWidth, sizeof(char));
	for (int i = 0; i < TargetStrWidth; i++){
		TempStr[i] = *(Image + width - 1 - i);
	}

	for (int i = 0; i < 100; i++){
		char* TempStr2 = (char*)calloc(TargetStrWidth, sizeof(char));
		for (int j = 0; j < TargetStrWidth; j++){
			TempStr2[j] = TempStr[j] + i;
		}
		printf("%d: %s\n", i, TempStr2);
	}
	*/


	system("pause");
	return 0;
}