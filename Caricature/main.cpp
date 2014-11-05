#include <cassert>
#include "helper.h"
#include "imgwarp_mls_rigid.h"

int main(int argc, char *argv[])
{
	Mat img1 = imread("C:/Users/Alan/Documents/GitHub/Caricature/3.jpg");
	Mat img2 = imread("C:/Users/Alan/Documents/GitHub/Caricature/2.jpg");

	vector<Point_<int>> qsrc;
	vector<Point_<int>> qdst;

	assert(!parseCoor(string("C:/Users/Alan/Documents/GitHub/Caricature/3.txt"), qsrc));
	assert(!parseCoor(string("C:/Users/Alan/Documents/GitHub/Caricature/2.txt"), qdst));

	ImgWarp_MLS_Rigid warpper;
	warpper.alpha = 3;
	warpper.gridSize = 40;

	//img_out = warpper.genNewImg(img, 1);
	
	Rect rect1 = faceDetect(img1, false);
	Rect rect2 = faceDetect(img2, true);
	imwrite("C:/Users/Alan/Documents/GitHub/Caricature/out1.jpg", img1);
	imwrite("C:/Users/Alan/Documents/GitHub/Caricature/out2.jpg", img2);
	fixCoor(qdst, rect1, rect2);
	Mat img = warpper.setAllAndGenerate(img1, qsrc, qdst, img1.cols, img1.rows, 0.9);
	//drawPt(img, qdst);
	imwrite("C:/Users/Alan/Documents/GitHub/Caricature/out.jpg", img);
	return 0;
}
