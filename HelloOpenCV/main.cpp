#include "main.h" // t�m ba�l�klar�m�z� ve tan�mlamalar�m�z� i�eren ba�l�k dosyas�.



int main( int argc, char** argv )
{
	int key = -1;

	CvCapture* capture = 0;
	CvCapture* capture2 = 0;

	// �lk tan�ml� kameran�n tutaca��n� al. (tutacak = handle).
	capture = cvCaptureFromCAM( 0 ); 
	if( !capture )
	{
		// Tutacak ge�ersiz ise programdan ��k.
		fprintf( stderr, "Kamera tutaca�� edinilemedi...\n" ); // bilgilendiiir.
		exit( EXIT_FAILURE );
	}

	// G�r�nt� i�in pointer.
	IplImage* videoFrame = NULL; 
	
	// ilk kareyi yakala.
	videoFrame = cvQueryFrame( capture ); 

	if( !videoFrame )
	{
		// Kare yakalanamad�, programdan ��k.
		printf( "Kare yakalanamad�...\n" );
		exit( EXIT_FAILURE );
	}
	
	// MainVideo ad�nda bir g�sterim penceresi yarat.
	cvNamedWindow( "MainVideo", 1 );
	
	IplImage* resizedImage = cvCreateImage(cvSize(640, 480), videoFrame->depth, videoFrame->nChannels);

	//ISingleImageFilter* myFilter1 = new SingleCudaFilter(deviceInvertLaunch);
	ISingleImageFilter* myFilter2 = new CpuInvertFilter();
	//ISingleImageFilter* myFilter3 = new SingleCudaFilter(deviceTileFlipLaunch);
	//ISingleImageFilter* myFilter4 = new SingleCudaTexFilter(deviceTexBoxBlurLaunch, "texBlur1");
	ISingleImageFilter* myFilter5 = new SingleCudaTexFilter(deviceTexAbsDiffLaunch, "texAbsDiff1");
	ISingleImageFilter* myFilter6 = new SingleCudaTexFilter(deviceTexInvertLaunch, "tex");
	
	SingleImageFilterChain* myFilter = new SingleImageFilterChain();
	myFilter->AppendFilter( myFilter5 );
	myFilter->AppendFilter( myFilter2 );
	//myFilter->AppendFilter( myFilter6 );

	myFilter->InitFilter(resizedImage->width, resizedImage->height);
	
	// q tu�una basana kadar d�n.
	while( key != 'q' )
	{
		// Bir kare al.
		videoFrame = cvQueryFrame( capture );

		cvResize( videoFrame, resizedImage );

		// Kare ge�ersiz ise loop biter.
		if( !resizedImage )
			break;

		myFilter->FilterImage(resizedImage->imageData);

		// Negatif g�r�nt�y� pencerede g�ster.
		cvShowImage( "MainVideo", resizedImage );

		key = cvWaitKey( 10 ); // 10ms tu� i�in bekle.

	}

	cvDestroyAllWindows(); // yaratt���m�z pencereyi yokeder.

	cvReleaseCapture( &capture ); // Kameran�n tutaca��n� b�rak�r.

	myFilter->ReleaseFilter();

	cudaThreadExit();

	//exit( EXIT_SUCCESS );
}