#pragma once

#include <vector>
#include <iostream>
#include <cstdio>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

int parseCoor(const string &path, vector<Point_<int>> &coor);
Rect faceDetect(Mat &frame, bool draw);
void fixCoor(vector<Point_<int>> &qdst, Rect &rect1, Rect &rect2);
void drawPt(Mat &frame, vector<Point_<int>> &pts);