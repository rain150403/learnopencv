////Ã«±ß¼ì²â
//Ptr<Feature2D>surf = xfeatures2d::SURF::create(500);
//vector<KeyPoint>key1, key2;
//vector<DMatch> matches;
//
//surf->detect(STBurImage, key1);
//surf->detect(roiImg, key2);
//
//if ((key2.size() - key1.size()) > stCamera[camIndex].nBurDetectThr)
//{
//	m_resultBurDetect = 0;  //ÓÐÃ«±ß
//	/*putText(srcImg, "Bur", cv::Point(TOTAL_IMAG_WIDTH - 800, 100), CV_FONT_HERSHEY_COMPLEX,
//	stCamera[camIndex].nFontSize, cv::Scalar(0, 255, 0), 3);*/
//}
//else
//{
//	m_resultBurDetect = 1;  //ÎÞÃ«±ß
//	/*putText(srcImg, "No Bur", cv::Point(TOTAL_IMAG_WIDTH - 600, 100), CV_FONT_HERSHEY_COMPLEX,
//	stCamera[camIndex].nFontSize, cv::Scalar(0, 255, 0), 3);*/
//}