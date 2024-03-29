#image = image.cpp
#image.o : $(image) 
	#g++ -c $(image) #####tab#####
#-c -o -O0 -O -O2 -O3 -I -L -l -shared -static -Wall shell
#opencv_core/opencv_imgproc/opencv_highgui/opencv_ml/opencv_gpu/fftw3/gsl/gslcblas/xml2/z/tiff/pthread/boost_system/boost_thread/boost_program_options/boost_date_time

#CXX = gcc
#CXXFLAGS = -I/usr/include -Wall -g
#LDFLAGS = -L/usr/local/lib
#gcc   -D   MACRONAME=MACRODEF //�궨��

all : test_block.out test_tile.out
.PHONY : all

test_block.out : test_block.cpp grid.cpp check.cpp field.cpp image.cpp gaussWeighting.cpp readWriteTIFF.cpp registration.cpp imReconstruct.cpp erodeDilate.cpp peakPosition.cpp RLE.cpp readWriteTXT.cpp Intensity.cpp readWriteCH.cpp charity.cpp crosstalk.cpp normalization.cpp standard.cpp regression.cpp LeastSquare.h phasingPrephasing.cpp calling.cpp readWriteGZ.cpp CDReconstruct.cpp squareFit.cpp ANN.cpp bayescall.cpp svm.cpp wiener.cpp errorStream.cpp htmlReport.cpp imageAnalysis.cpp intensityAnalysis.cpp memory.cpp multithreading.cpp myTime.cpp findFile.cpp BB.cpp block.cpp affineTransformation.cpp
	g++ -o test_block.out -O3 test_block.cpp grid.cpp check.cpp field.cpp image.cpp gaussWeighting.cpp readWriteTIFF.cpp imReconstruct.cpp registration.cpp erodeDilate.cpp peakPosition.cpp RLE.cpp readWriteTXT.cpp Intensity.cpp readWriteCH.cpp charity.cpp crosstalk.cpp normalization.cpp standard.cpp regression.cpp LeastSquare.h phasingPrephasing.cpp calling.cpp readWriteGZ.cpp squareFit.cpp CDReconstruct.cpp ANN.cpp bayescall.cpp svm.cpp wiener.cpp  errorStream.cpp htmlReport.cpp imageAnalysis.cpp intensityAnalysis.cpp memory.cpp multithreading.cpp myTime.cpp BB.cpp findFile.cpp block.cpp affineTransformation.cpp -L/home/xuweibin/workgroup/CPPLib/boost_1_56_0/boost_1_56_0/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -ltiff -lgsl -lgslcblas -lz -lboost_system -lboost_thread -lboost_date_time -lboost_filesystem

test_tile.out : test_tile.cpp image.cpp gaussWeighting.cpp readWriteTIFF.cpp registration.cpp erodeDilate.cpp imReconstruct.cpp peakPosition.cpp RLE.cpp readWriteTXT.cpp Intensity.cpp readWriteCH.cpp charity.cpp crosstalk.cpp normalization.cpp standard.cpp regression.cpp LeastSquare.h phasingPrephasing.cpp calling.cpp readWriteGZ.cpp CDReconstruct.cpp squareFit.cpp bayescall.cpp ANN.cpp svm.cpp wiener.cpp errorStream.cpp htmlReport.cpp imageAnalysis.cpp intensityAnalysis.cpp memory.cpp multithreading.cpp myTime.cpp affineTransformation.cpp  FFT.cpp imageCrop.cpp block.cpp findFile.cpp check.cpp
	g++ -o test_tile.out -O3 test_tile.cpp image.cpp gaussWeighting.cpp readWriteTIFF.cpp registration.cpp erodeDilate.cpp imReconstruct.cpp peakPosition.cpp RLE.cpp readWriteTXT.cpp Intensity.cpp readWriteCH.cpp charity.cpp crosstalk.cpp normalization.cpp standard.cpp regression.cpp LeastSquare.h phasingPrephasing.cpp calling.cpp readWriteGZ.cpp squareFit.cpp CDReconstruct.cpp bayescall.cpp ANN.cpp svm.cpp wiener.cpp  errorStream.cpp htmlReport.cpp imageAnalysis.cpp intensityAnalysis.cpp memory.cpp multithreading.cpp myTime.cpp affineTransformation.cpp  FFT.cpp imageCrop.cpp block.cpp findFile.cpp check.cpp -L/home/xuweibin/workgroup/CPPLib/boost_1_56_0/boost_1_56_0/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -ltiff -lgsl -lgslcblas -lz -lfftw3 -lboost_system -lboost_thread -lboost_date_time -lboost_filesystem 

clean:
	@rm -rf *.o
	@echo clean done.
