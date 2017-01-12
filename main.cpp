#include"header.h"
//@author:		Li Zhengcheng
//@date:		2017.Jan,10th
//@environment: opencv3.1.0   vs2015   x64  Maybe you can't run the code right now,but be patient!  Thanks!    ^_^
//@description:
//@this program aims to get the track of an object using color-detected
//       ^^            ^^
//        *            *
//              |
//             ---

int main()
{
	//open the camera which connected with your computer
	//you can change the number in 'cap()' 
	//0 is your default camera,
	//1,2,3,is other cameras connected with your computer
	VideoCapture cap(1);

	//some assignment
	Mat frame, hsv, dst;
	cap >> frame;
	cap >> frame;
	Mat threshed, frame_blred;
	frame.assignTo(threshed);
	frame.assignTo(frame_blred);
	Mat Scribbe(frame.size(), frame.type(), Scalar(0,0,0));
	
	double area;
	//the object's positon now
	Point pt;
	//the object's old position
	Point last_pt;
	//init the old position
	last_pt.x = last_pt.y = 0;
	while (waitKey(20) != 'q') {

		cap >> frame;


		//a Gaussian filter,you can change the kernel size and the sigma
		GaussianBlur(frame, frame_blred, Size(5,5), 2.3);
		if (!frame.data) {
			cerr << "can not load the frame";
		}


		//change the RGB To HSV
		cvtColor(frame_blred, hsv, CV_BGR2HSV);

		//get the HSV image thresholed
		//if you want to detect objects with other colors,change the scalar
		inRange(hsv, Scalar(100, 50, 50), Scalar(130, 100, 100), threshed);
		Moments moment = moments(threshed, true);

		area=moment.m00;
		//the object's position is the center of the area
		pt.y = moment.m01 / area;
		pt.x = moment.m10 / area;
		cout << "Position" << "(" << pt.x << "," << pt.y << ")" << endl;

		//draw line on the Scribbe image
		if (last_pt.x != pt.x&&last_pt.y != pt.y&&last_pt.x != 0 && last_pt.y != 0) {
			line(Scribbe, last_pt, pt, Scalar(20, 100, 150),1);
		}

		//add the Scribbe image to frame,so that we can get the line on the "frame" window
		add(Scribbe, frame, dst);

		//update the old position
		last_pt = pt;


		//show the result!!
		imshow("hsv", hsv);
		imshow("threshed", threshed);
		imshow("frame", dst);
	}
	return 0;
}