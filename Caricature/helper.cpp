#include "helper.h"
#include <fstream>
#include <sstream>

int parseCoor(const string &path, vector<Point_<int>> &coor) {
	ifstream file(path);
	if (!file.good())
		return 1;
	string line;
	int n;
	double x, y;
	getline(file, line);
	while (getline(file, line)) {
		stringstream ss(line);
		ss >> n >> x >> y;
		Point_<int> pt((int)x, (int)y);
		coor.push_back(pt);
		//printf("%d: (%d, %d)\n", n, pt.x, pt.y);
	}
	file.close();
	return 0;
}

Rect faceDetect(Mat &frame, bool draw) {
	String path = "C:/opencv/opencv300/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
	CascadeClassifier faceCascade;
	if (!faceCascade.load(path)) {
		printf("--(!)Error loading\n");
		return Rect();
	}

	vector<Rect> faces;
	Mat frameGray;

	cvtColor(frame, frameGray, COLOR_BGR2GRAY);
	equalizeHist(frameGray, frameGray);

	faceCascade.detectMultiScale(frameGray, faces, 1.1, 2, 0, Size(200, 200));

	for (int i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		if (draw)
			rectangle(frame, faces[i], Scalar(255, 0, 255), 2);
		return faces[i];
	}
}

void fixCoor(vector<Point_<int>> &qdst, Rect &rect1, Rect &rect2) {
	Point_<int> c1(rect1.x + rect1.width / 2, rect1.y + rect1.height / 2);
	Point_<int> c2(rect2.x + rect2.width / 2, rect2.y + rect2.height / 2);
	double xScale = (double)rect1.width / rect2.width;
	double yScale = (double)rect1.height / rect2.height;

	for (auto it = qdst.begin(); it != qdst.end(); it++) {
		(*it).x = c2.x + ((*it).x - c2.x) * xScale;
		(*it).y = c2.y + ((*it).y - c2.y) * yScale;
		(*it).x += c1.x - c2.x;
		(*it).y += c1.y - c2.y;
	}
}

void drawPt(Mat &frame, vector<Point_<int>> &pts) {
	for (auto it = pts.begin(); it != pts.end(); it++) {
		circle(frame, *it, 5, Scalar(255, 255, 255), 3);
	}
}