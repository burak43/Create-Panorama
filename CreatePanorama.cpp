/*
 * CreatePanorama.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: Burak Mandira
 */

#include <opencv2/opencv.hpp>
#include <opencv2/stitching/stitcher.hpp>
#include <opencv2/stitching/warpers.hpp>
#include <boost/filesystem.hpp>

using namespace cv;
using namespace std;
using namespace boost::filesystem;

int main()
{
	vector<Mat> images;

	// read images
	for( directory_iterator it("./Images"), end_iter; it != end_iter; it++)
	{
		string img_name = it->path().filename().string();
		string path = it->path().string();
		cout << img_name << " located in " << path << endl;

		images.push_back( imread(path));
	}

	// create panorama
	Mat panorama;

	Stitcher stitcher = Stitcher::createDefault();
/**/

	Stitcher::Status stat = stitcher.stitch( images, panorama);

//	 OR

//	stitcher.setWarper( new PlaneWarper());
////	stitcher.setWarper( new CylindricalWarper());
////	stitcher.setWarper( new SphericalWarper());
//	stitcher.estimateTransform( images);
//	Stitcher::Status stat = stitcher.composePanorama( images, panorama);

/**/

	if( stat != Stitcher::OK)
	{
		cout << "Error while stitching, error code = " << int(stat) << endl;
		return -1;
	}

	imwrite( "panorama.jpg", panorama);
	resize( panorama, panorama, Size(1360,710));
	imshow( "Panoramic Image", panorama);

	while( char(waitKey(0)) != 'q');
}


