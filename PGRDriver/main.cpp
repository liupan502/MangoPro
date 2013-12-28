#include "PGRReader.h"
#include <time.h>
const char* path = "E:\\pgr\\gangjianglu10hz\\Ladybug-Stream-000000.pgr";
int main()
{
	PGRReader reader;
	
	if(reader.Init(path))
	{
		reader.SetSaveImageSize(616,808);
		Mat mat0,mat1,mat2;
		clock_t time0 = clock();
		reader.GetImage(2,mat0,LADYBUG_RECTIFIED_CAM0);
		clock_t time1 = clock();
		reader.GetImage(2,mat1,LADYBUG_RECTIFIED_CAM1);
		clock_t time2 = clock();
		reader.GetImage(2,mat2,LADYBUG_RECTIFIED_CAM2);
		clock_t time3 = clock();
		cout << (double)(time1 - time0)/ CLOCKS_PER_SEC << endl;
		cout << (double)(time2 - time1)/ CLOCKS_PER_SEC << endl;
		cout << (double)(time3 - time2)/ CLOCKS_PER_SEC << endl;
		//reader.GetImage(2,mat0,LADYBUG_RECTIFIED_CAM0);
	}
	char a;
	cin >> a;
	return 1;
}