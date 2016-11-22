#######

# Testing earth
# Will Grey
# 1 January 2016

# Full testing performed
#   -byte2short  	 Convert from signed char to signed short integer
#   -byte2float  	 Convert from signed char to float
#   -byte2long  	 Convert from signed char to signed long integer
#   -float2byte  	 Convert from float to signed char
#   -long2float  	 Convert from signed long integer to float
#   -long2byte  	 Convert from signed long integer to signed char
#   -short2byte  	 Convert from signed short integer to signed char
#   -short2float  	 Convert from signed short integer to float
#   -short2long  	 Convert from signed short integer to signed long integer
#   -long2short  	 Convert from signed long integer to signed short integer
#   -ushort2float 	 Convert from unsigned short integer to float
#   -ubyte2float 	 Convert from unsigned char to float
#   -ubyte2ushort 	 Convert from unsigned char to unsigned short integer
#   -ushort2ubyte 	 Convert from unsigned short integer to unsigned char
#   -float2ubyte 	 Convert from float to unsigned char
#   -long2ulong  	 Convert from long to unsigned long
#   -ulong2long  	 Convert from unsigned long to long
#   -short2ushort  	 Convert from short to unsigned short
#   -ushout2short  	 Convert from unsigned short to short
#   -ubyte2byte  	 Convert from unsigned char to char
#   -byte2ubyte  	 Convert from char to unsigned char
#   -copy 	 	 Copy binary data file
#   -header  		 Create ENVI header file
#   -mkimg   		 Create a single value raw binary image file
#   -degConv  		 Convert between decimal degrees and degrees, minuts and seconds and vice versa
#   -getPixel    	 Extract pixel value from image
#   -getNumLinesAll   	 Get number of lines in a file including blank lines
#   -diff     	         Calculate the difference between two images
#   -add    	 	 Add two images
#   -ratio   		 Divide pixels values in image 1 by values in image 2
#   -modulus   		 Make all pixel values positive
#   -swap 	 	 Byte swapping from little endian to big endian and vice versa
#   -mosaic    		 Mosaic images
#   -byte2pgm   	 Converts from binary byte data to pgm
#   -pgm2byte  		 Converts pgm to binary byte data
#   -byte2text   	 Convert from char to ASCII text
#   -short2text   	 Convert from short int to ASCII text
#   -float2text   	 Convert from float to ASCII text
#   -float2textRow   	 Convert from float to ASCII text as row
#   -float2textSN   	 Convert from float to ASCII text in scientific notation
#   -sideCat   		 Concatonate 2 text files side by side
#   -thresh   		 Apply threshold to image
#   -areaCounter  	 Count pixels in 1/0 binary value byte image   
#   -rows2cols           Converts rows to columns in text files
#   -crop    		 Extract sub area of an image
#   -calcTotalMean   	 Calculate total and mean of a text file
#   -mean    		 Calculate mean of seqence of input images
#   -text2float   	 Convert from ASCII text to float
#   -mask   		 Apply mask to image
#   -reassign       	 Reassign values within byte image
#   -byte2ppm   	 Converts from binary byte data to ppm
#   -byte2ppm3           Converts from binary 3 channels byte data to ppm
#   -ppm2byte   	 Converts ppm to binary byte data
#   -addNoise 	 	 Box Muller transform to add Gaussian noise to text file
#   -addNoiseImg  	 Box Muller transform to add Gaussian noise to image
#   -xflip 	 	 Flip images left to right
#   -yflip               Flip images up to down
#   -shiftMeridian  	 In global datasets shift meridian from middle to edge
#   -anomalies 	 	 Subtract image mean from pixel values
#   -standardise  	 Subtract image mean from pixel values and divide by standard deviation
#   -getNumLines   	 Get number of lines in a file excluding blank lines
#   -calibrate   	 Apply gain and offset to image pixels 
#   -dimap2bsq  	 Convert from dimap to band sequential image
#   -bsq2dimap  	 Convert from band sequential image to dimap
#   -resample  		 Resamples raw binary image data using nearest-neighbour interpolation
#   -interpText   	 Perform linear interpolation on column in a text file
#   -zenith              Calculate solar zenith

# Only minimal testing performed
#   -linear2dB   	 Convert radar data from linear to dB values
#   -dB2linear   	 Convert radar data from dB to linear values
#   -bip2bsq   		 Convert from byte interleave by pixel to band sequence
#   -bil2bsq   		 Convert from byte interleave by line to band sequence
#   -bil2bip   		 Convert from byte interleave by line to byte interleave by pixel
#   -bip2bil   		 Convert from byte interleave by pixel to byte interleave by line
#   -complex2RealImag    Convert complex radar data to real and imaginary
#   -complex2PwrPhase    Convert complex radar data to power and phase
#   -modeFilter 	 Apply mode (majority) filter to byte image data
#   -meanFilter 	 Apply mean filter
#   -texture 	 	 Apply texture filter
#   -transect    	 Extract pixel values along a transect between two points
#   -stdev               Calculate standard deviation of sequence of input images
#   -demSlope            Calculates the slope and aspect from an input DEM float image    
#   -covariance   	 Calculate covariance and correlation matrix between channels
#   -stats               Calculate univariate statistics of image channels
#   -histogram    	 Calculates histogram of multi channel input data file
#   -histoArea   	 Calculates histogram of multi-channel input data file for each region
#   -meanArea  		 Calculates the statistics with regions
#   -regression   	 Calculate regression between 2 images
#   -confusion 	 	 Calculate confusion matrix for classified image
#   -separability   	 Calculate separability between classes for any number of channels
#   -linear2Dinterp 	 Perform 2D linear interpolation to upscale image  
#   -classify     	 Classiy images using basic box classifier
#   -georeference 	 Georeference Earth observation images
#   -rad2ref   		 Convert from radiance values to reflectance
#   -spectralResponse  	 Calculate broadband spectral response given irriadiance and spectral response function
#   -rotate    		 Rotate images
#   -demVolume           Calculate volume of a DEM difference
#   -ndvi   		 Calculate normalised difference vegetation index
#   -meanWindow   	 Perform smoothing using mean filter
#   -demShade            Creates shaded relief map from DEM
#   -ar   	   	 Calculate AR between 2 columns of data
#   -autoregressive      AR over sequence of images
#   -area                Calculates area
#   -automata		 Run cellular automata Markov simulation
#   -trainCA		 Train transformation matrix for cellular automata
#    -tsspec       	 Calculate time series spectra
#   -byte2bits		 Convert from bits to bytes
#   -bits2byte		 Convert from bytes to bits
#   -eval_clusters	 	
#   -remove_big_clusters_int
#   -remove_small_clusters_int
#   -remove_big_clusters_byte
#   -remove_small_clusters_byte
#   -count_clusters_int
#   -count_clusters_byte

earth="../bin/earth"

if [ ] ; then

if [ 1 ] ; then
 
 $earth -ar
 $earth -demVolume
 $earth -demShade
 $earth -ndvi
 $earth -meanWindow
 $earth -autoregressive
 $earth -area

 $earth -byte2short  	
 $earth -byte2float  	 
 $earth -byte2long  	 
 $earth -float2byte  	 
 $earth -long2float  	 
 $earth -long2byte  	 
 $earth -short2byte  	
 $earth -short2float  	 
 $earth -short2long  	 
 $earth -long2short  	 
 $earth -ushort2float 	 
 $earth -ubyte2float 	
 $earth -ubyte2ushort 	 
 $earth -ushort2ubyte 	 
 $earth -float2ubyte 	 
 $earth -long2ulong  	 
 $earth -ulong2long  	 
 $earth -short2ushort  	 
 $earth -ushort2short  	 
 $earth -ubyte2byte  	 
 $earth -byte2ubyte  	
 
 $earth -linear2dB   	
 $earth -dB2linear
 $earth -complex2RealImag   	
 $earth -complex2PwrPhase
   	   	 
 $earth -modeFilter 	 	 
 $earth -meanFilter 	 	 
 $earth -texture 	

 $earth -confusion  	  	 
 $earth -separability 		 
 $earth -classify
 $earth -reassign 

 $earth -copy 	 	 
 $earth -header 
 $earth -demSlope   		 
 $earth -degConv  
 $earth -spectralResponse

 $earth -getNumLines
 $earth -getNumLinesAll   	 
 $earth -sideCat
 $earth -calcTotalMean
 $earth -rows2cols
 $earth -interpText       
 $earth -addNoise 

 $earth -histoArea   	 
 $earth -anomalies 	 	
 $earth -standardise  	 
 $earth -meanArea  		  	 
 $earth -covariance   	 
 $earth -stats      		 
 $earth -hist 
 $earth -stdev
 $earth -areaCounter  	    
 $earth -mean    
 $earth -addNoiseImg  	 

 $earth -transect    	 
 $earth -regression
 $earth -linear2Dinterp
 $earth -georeference
 $earth -rad2ref
 $earth -rotate 		 
 $earth -mkimg		 
 $earth -getPixelValue    	 
 $earth -diff     	         
 $earth -add    	 	 
 $earth -ratio   		
 $earth -modulus   		 
 $earth -swap 	 	 
 $earth -mosaic    		 
 $earth -thresh   		 	
 $earth -crop     
 $earth -mask   		 
 $earth -xflip 	 	 
 $earth -yflip               
 $earth -shiftMeridian  	 
 $earth -calibrate   
 $earth -resample  	

 $earth -bip2bsq   		 
 $earth -bil2bsq   		
 $earth -bil2bip   		 
 $earth -bip2bil   
 $earth -byte2pgm   	 
 $earth -pgm2byte  		 
 $earth -byte2text   	
 $earth -short2text   	 
 $earth -float2text   	 
 $earth -float2textRow   	 
 $earth -float2textSN   	
 $earth -text2float   	 
 $earth -byte2ppm   	 
 $earth -byte2ppm3           
 $earth -ppm2byte   	 	 	  	 
 $earth -dimap2bsq  	
 $earth -bsq2dimap  	 
 $earth -tsspec	 
 $earth -bits2byte  	 
 $earth -byte2bits
 $earth -eval_clusters	
 $earth -remove_big_clusters_int
 $earth -remove_small_clusters_int
 $earth -remove_big_clusters_byte
 $earth -remove_small_clusters_byte
 $earth -count_clusters_int
 $earth -count_clusters_byte	 	 

echo "end of syntax tests"

fi

if [ 1 ] ; then
 
 echo "mking test"

 $earth -mkimg
 $earth -mkimg earthImg 600 400 1 10 1
 
fi

if [ 1 ] ; then

 echo "getPixelValue test"

 $earth -getPixelValue
 $earth -getPixelValue earthImg 600 200 200 1
 $earth -getPixelValue earthImg 200 200 200 1 3 
 $earth -getPixelValue earthImg 600 200 407 1

fi

if [ 1 ] ; then
 
 echo "header test"

 $earth -header earthImg.hdr
 $earth -header earthImg.hdr 100 200 10
 $earth -header earthImg.hdr 100 200 10 2
 $earth -header earthImg.hdr 100 200 10 2 0
 rm earthImg.hdr
fi

if [ 1 ] ; then

 echo "copy test"

 $earth -copy
 $earth -copy earthImg
 $earth -copy earthImg earthImg2.out
 
 diff earthImg2.out earthImg.out
 diff earthImg earthImg2.out
 rm earthImg2.out earthImg.out
fi

if [ 1 ] ; then

  echo "degConv test"

 $earth -degConv
 $earth -degConv -101 45 0
 $earth -degConv -95 45 0
 $earth -degConv -1 45 0
 $earth -degConv 54 45 0 
 $earth -degConv 54.75 

fi

if [ 1 ] ; then

 echo "Data type conversion tests"

 $earth -byte2float earthImg earthImg2
 $earth -getPixelValue earthImg2 300 200 200 4 2
 $earth -float2byte earthImg2 earthImg3
 diff earthImg earthImg3
 rm earthImg2 earthImg3

 $earth -ubyte2float earthImg earthImg2
 $earth -getPixelValue earthImg2 300 200 200 4 2
 $earth -float2ubyte earthImg2 earthImg3
 diff earthImg earthImg3
 rm earthImg2 earthImg3

 $earth -byte2long earthImg earthImg2
 $earth -getPixelValue earthImg2 600 200 200 3 1
 $earth -long2byte earthImg2 earthImg3
 diff earthImg earthImg3
 rm earthImg2 earthImg3

 $earth -byte2short earthImg earthImg2
 $earth -getPixelValue earthImg2 600 200 200 2 1
 $earth -short2byte earthImg2 earthImg3
 diff earthImg earthImg3
 rm earthImg2 earthImg3

 $earth -byte2ubyte earthImg earthImg2
 $earth -getPixelValue earthImg2 600 200 200 1 1
 $earth -byte2ubyte earthImg2 earthImg3
 diff earthImg earthImg3
 rm earthImg2 earthImg3

 $earth -ubyte2ushort earthImg earthImg2
 $earth -getPixelValue earthImg2 600 200 200 2 1
 $earth -ushort2ubyte earthImg2 earthImg3
 diff earthImg earthImg3
 rm earthImg2 earthImg3

 $earth -byte2short earthImg earthImg2
 $earth -getPixelValue earthImg2 600 200 200 2 1
 $earth -short2ushort earthImg2 earthImg3
 $earth -getPixelValue earthImg3 600 200 200 2 1
 $earth -ushort2short earthImg3 earthImg4
 diff earthImg2 earthImg4
 rm earthImg2 earthImg3 earthImg4

 $earth -byte2short earthImg earthImg2
 $earth -short2long earthImg2 earthImg3
 $earth -getPixelValue earthImg3 600 200 200 3 1
 $earth -long2short earthImg3 earthImg4
 diff earthImg2 earthImg4
 rm earthImg2 earthImg3 earthImg4

 $earth -byte2short earthImg earthImg2
 $earth -short2ushort earthImg2 earthImg3
 $earth -getPixelValue earthImg3 600 200 200 2 1
 $earth -ushort2short earthImg3 earthImg4
 diff earthImg2 earthImg4
 rm earthImg2 earthImg3 earthImg4

 $earth -byte2long earthImg earthImg2
 $earth -long2ulong earthImg2 earthImg3
 $earth -getPixelValue earthImg3 600 200 200 3 1
 $earth -ulong2long earthImg3 earthImg4
 diff earthImg2 earthImg4
 rm earthImg2 earthImg3 earthImg4

 $earth -byte2short earthImg earthImg2
 $earth -short2float earthImg2 earthImg3 
 $earth -getPixelValue earthImg3 600 200 200 4 1
 rm earthImg2 earthImg3

 $earth -byte2short earthImg earthImg2
 $earth -ushort2float earthImg2 earthImg3 
 $earth -getPixelValue earthImg3 600 200 200 4 1
 rm earthImg2 earthImg3

 $earth -byte2long earthImg earthImg2
 $earth -long2float earthImg2 earthImg3 
 $earth -getPixelValue earthImg3 600 200 200 4 1
 rm earthImg2 earthImg3

fi

if [ 1 ] ; then  
 echo " Arithmetic tests"
 $earth -mkimg earthImg2 600 400 1 5 1
 $earth -add earthImg earthImg2 earthImg3 1
 $earth -getPixelValue earthImg3 600 200 200 1 1
 rm earthImg2 earthImg3
fi

if [ 1 ] ; then  
 $earth -mkimg earthImg2 600 400 1 5 1
 $earth -diff earthImg earthImg2 earthImg3 1
 $earth -getPixelValue earthImg3 600 200 200 1 1
 rm earthImg2 earthImg3
fi

if [ 1 ] ; then  
 $earth -mkimg earthImg2 600 400 4 5
 $earth -mkimg earthImg3 600 400 4 15
 $earth -ratio earthImg3 earthImg2 earthImg4 4
 $earth -getPixelValue earthImg4 600 200 200 4 1
 rm earthImg2 earthImg3 earthImg4
fi

if [ 1 ] ; then  
 $earth -mkimg earthImg2 600 400 4 5
 $earth -modulus earthImg2 earthImg3 4
 $earth -getPixelValue earthImg2 600 200 200 4 1
 $earth -getPixelValue earthImg3 600 200 200 4 1
 rm earthImg2 earthImg3 
fi

if [ 1 ] ; then  
 $earth -mkimg earthImg2 600 400 4 -5
 $earth -modulus earthImg2 earthImg3 4
 $earth -getPixelValue earthImg2 600 200 200 4 1
 $earth -getPixelValue earthImg3 600 200 200 4 1
 rm earthImg2 earthImg3 
fi

if [ 1 ] ; then
 echo " Swap tests"
 $earth -mkimg earthImg 600 400 2 10
 $earth -getPixelValue earthImg 600 200 200 2 1
 $earth -swap earthImg earthImg2 2
 $earth -getPixelValue earthImg2 600 200 200 2 1
 rm earthImg2

fi



if [ 1 ] ; then

  $earth -mkimg earthImg 600 600 1 10
  $earth -byte2text earthImg earthImg.txt 600
    
  $earth -mkimg earthImg2 600 600 2 10
  $earth -short2text earthImg2 earthImg2.txt 600

  $earth -mkimg earthImg3 50 50 4 10
  $earth -float2text earthImg3 earthImg3.txt 50
  $earth -float2textRow earthImg3 earthImg4.txt 50
  $earth -float2textSN earthImg3 earthImg5.txt 50

  rm earthImg.txt earthImg2.txt earthImg3.txt earthImg4.txt earthImg5.txt

fi

if [ 1 ] ; then
 
 echo "1" > test3.txt
 echo "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt

 echo  "hello" >  textTest.txt
 echo  "world" >> textTest.txt
 echo  "how"   >> textTest.txt
 echo  "are"   >> textTest.txt
 echo  "you"   >> textTest.txt
 echo  "today" >> textTest.txt

 $earth -sideCat test3.txt textTest.txt testout.txt
 $earth -sideCat textTest.txt test3.txt testout.txt
 rm test3.txt textTest.txt testout.txt

fi

if [ 1 ] ; then

 echo  "1 2 3 4 5 6 7" > testrow2col.txt
 echo  "8 9 10 11 12 13 14" >> testrow2col.txt
 echo  "15 16 17 18 19 20 21" >> testrow2col.txt
 echo  "22 23 24 25 26 27 28" >>  testrow2col.txt  
   
 $earth -rows2cols testrow2col.txt testoutrow2col.txt
 $earth -text2float testrow2col.txt testFloat
 $earth -getPixelValue testFloat 7 1 1 4 1
 $earth -getPixelValue testFloat 7 1 2 4 1
 $earth -getPixelValue testFloat 7 7 4 4 1

 rm  testrow2col.txt testoutrow2col.txt testFloat

fi

if [ 1 ] ; then


 echo "20" > meanTest.txt
 echo "30" >> meanTest.txt
 echo "40" >> meanTest.txt
 echo "50" >> meanTest.txt
 echo "60" >> meanTest.txt
 echo "70" >> meanTest.txt
 echo "80" >> meanTest.txt
 echo "90" >> meanTest.txt
 echo "100" >> meanTest.txt

 $earth -calcTotalMean meanTest.txt
 rm meanTest.txt
fi


if [ 1 ] ; then
 
 echo "earthImg" > meanImgtest.txt
 echo "earthImg2" >> meanImgtest.txt
 echo "earthImg3" >> meanImgtest.txt
 
 $earth -mkimg earthImg 600 600 1 10
 $earth -mkimg earthImg2 600 600 1 5
 $earth -mkimg earthImg3 600 600 1 6   
 $earth -mean meanImgtest.txt earthImg4	 
 $earth -getPixelValue earthImg4 600 200 200 4 1  

 rm earthImg earthImg2 earthImg3 meanImgtest.txt earthImg4

fi

if [ 1 ] ; then

 $earth -mkimg earthImg1 100 100 1 50
 $earth -mkimg earthImg2 100 100 1 127
 $earth -mkimg earthImg3 100 100 1 225
 $earth -mkimg earthImgb1 200 200 1 0
 $earth -mkimg earthImgb2 200 200 1 0
 $earth -mkimg earthImgb3 200 200 1 0

 $earth -mosaic earthImgb1 earthImg1 200 100 0 100 1
 $earth -mosaic earthImgb1 earthImg2 200 100 100 100 1
 $earth -mosaic earthImgb1 earthImg3 200 100 100 0 1

 $earth -mosaic earthImgb2 earthImg1 200 100 0 0 1 
 $earth -mosaic earthImgb2 earthImg2 200 100 0 100 1
 $earth -mosaic earthImgb2 earthImg3 200 100 100 0 1

 $earth -mosaic earthImgb3 earthImg1 200 100 100 0 1
 $earth -mosaic earthImgb3 earthImg2 200 100 0 0 1
 $earth -mosaic earthImgb3 earthImg3 200 100 0 100 1

 cat earthImgb1 earthImgb2 earthImgb3 > earthImg
 $earth -byte2ppm3 earthImg earthImg3.ppm 200

fi 

if [ 1 ] ; then
 
 echo "Test flip"
 $earth -mkimg earthImg 600 600 2 10
 $earth -mkimg earthImg1 100 100 2 5
 $earth -mosaic earthImg earthImg1 600 100 0 0 2
 $earth -xflip earthImg earthImgx 600 2 1
 $earth -short2byte earthImgx earthImg2
 $earth -byte2pgm earthImg2 earthImgXflip.pgm 600 15
 
 $earth -yflip earthImg earthImgy 600 2 1
 $earth -short2byte earthImgy earthImg3
 $earth -byte2pgm earthImg3 earthImgYflip.pgm 600 15

 $earth -shiftMeridian earthImg earthImgS 600 2 1
 $earth -short2byte earthImgS earthImg4
 $earth -byte2pgm earthImg4 earthImgS.pgm 600 15

 rm earthImg earthImg1 earthImgx earthImg2 earthImgy earthImgS earthImg4 earthImg3

fi


if [ 1 ] ; then

 echo "1" > test3.txt
 echo "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt

 $earth -addNoise test3.txt test4.txt 0.2
 $earth -mkimg earthImgb1 600 600 1 10
 $earth -addNoiseImg earthImgb1 earthImgNoise 0.2  
 $earth -getPixelValue earthImgNoise 600 100 100 4 1
 $earth -getPixelValue earthImgNoise 600 50 100 4 1
 $earth -getPixelValue earthImgNoise 600 100 50 4 1
  
 $earth -anomalies earthImgNoise earthImgb2 4
 $earth -getPixelValue earthImgb2 600 50 100 4 1  
 
 $earth -standardise earthImgNoise earthImgb2 4
 $earth -getPixelValue earthImgb2 600 50 100 4 1

 rm test3.txt test4.txt earthImgb1 earthImgNoise earthImgb2 earthImgb3
 
fi

if [ 1 ] ; then

 echo  "hello" >  textTest.txt
 echo  "world" >> textTest.txt
 echo  "how"   >> textTest.txt
 echo  "are"   >> textTest.txt
 echo  "you"   >> textTest.txt
 echo  "today" >> textTest.txt
 echo  "" >> textTest.txt
 echo  "   	" >> textTest.txt

 #$earth  -getNumLines ../src/getPixel.c
 #$earth -getNumLinesAll ../src/getPixel.c   	
 $earth  -getNumLines textTest.txt 	
 $earth -getNumLinesAll textTest.txt  	
 rm textTest.txt

fi

if [ 1 ] ; then
 
 echo "Calibrate test"

 echo  "0 10" >  Test3.txt
 echo  "10 0" >> Test3.txt
 echo  "1 1"   >> Test3.txt
 echo  " "   >> Test3.txt
 echo  " "   >> Test3.txt

 $earth -mkimg earthImg1 100 100 1 1
 $earth -mkimg earthImg2 100 100 1 2
 $earth -mkimg earthImg3 100 100 1 3

 cat earthImg1 earthImg2 earthImg3 > earthImg
 rm earthImg1 earthImg2 earthImg3

 $earth -calibrate earthImg earthImg.out Test3.txt 1 3
 $earth -getPixelValue earthImg.out 100 50 50 4 3
 rm earthImg Test3.txt earthImg.out

fi



if [ 1 ] ; then
 
 echo "DIMAP Test"
 
 mkdir dimapTest
 $earth -mkimg dimapTest/earthImg1 100 100 1 1
 $earth -mkimg dimapTest/earthImg2 100 100 1 2
 $earth -mkimg dimapTest/earthImg3 100 100 1 3

 cat dimapTest/earthImg1 dimapTest/earthImg2 dimapTest/earthImg3 > earthImgTest
 
 $earth -dimap2bsq dimapTest earthImg
 diff earthImgTest earthImg
 
 $earth -bsq2dimap earthImg dimapTest2 3
 diff dimapTest/earthImg1 dimapTest2/earthImg-channel-1
 diff dimapTest/earthImg2 dimapTest2/earthImg-channel-2
 diff dimapTest/earthImg3 dimapTest2/earthImg-channel-3

 rm -rf dimapTest dimapTest2
 rm earthImgTest earthImg

 

fi

if [ 1 ] ; then
 
 echo "Test resample"
 $earth -mkimg earthImg 600 600 2 10
 $earth -mkimg earthImg1 300 300 2 5
 $earth -mosaic earthImg earthImg1 600 300 0 0 2
 $earth -short2byte earthImg earthImg3
 $earth -byte2pgm earthImg3 earthImg3.pgm 600 15
 
 
 $earth -resample earthImg earthImgx 600 0.5 2
 $earth -short2byte earthImgx earthImg2
 $earth -byte2pgm earthImg2 earthImgResample.pgm 300 15
 
 rm earthImg earthImg1 earthImg2 earthImgx earthImg3

fi

if [ 1 ] ; then

 $earth -mkimg earthImg 600 600 1 10
 $earth -mkimg earthImg1 100 100 1 5
 $earth -mosaic earthImg earthImg1 600 100 100 100 1
 $earth -byte2pgm earthImg earthImg.pgm 600 15
 $earth -pgm2byte earthImg.pgm earthImg2
 $earth -byte2pgm earthImg2 earthImg2.pgm 600 15 
 diff earthImg.pgm earthImg2.pgm

 $earth -getPixelValue earthImg2 600 300 300 1 1
 $earth -getPixelValue earthImg 600 300 300 1 1
 $earth -getPixelValue earthImg2 600 120 120 1 1
 $earth -getPixelValue earthImg 600 120 120 1 1

 $earth -thresh earthImg earthImg3 7 7 1		 
 $earth -byte2pgm earthImg3 earthImg2.pgm 600 2
 $earth -areaCounter earthImg3     

 $earth -crop earthImg earthImg4 600 100 100 200 200 1
 $earth -byte2pgm earthImg4 earthImg3.pgm 200 15

 $earth -mask earthImg earthImg3 earthImg5 1
 $earth -getPixelValue earthImg5 600 300 300 1 1
 $earth -getPixelValue earthImg5 600 120 120 1 1
 
 echo "5 7" > reassign.txt
 echo "10 6" >> reassign.txt 
 
 $earth -reassign earthImg earthImg6 reassign.txt
 $earth -getPixelValue earthImg6 600 300 300 1 1
 $earth -getPixelValue earthImg6 600 120 120 1 1

 diff earthImg earthImg2

 $earth -byte2ppm earthImg4 earthImgCol.pgm 200
 $earth -ppm2byte earthImgCol.pgm earthImg7
 $earth -byte2ppm earthImg7 earthImgCol2.pgm 200

 $earth -getPixelValue earthImg7 200 25 25 1 1
 $earth -getPixelValue earthImg4 200 25 25 1 1
 $earth -getPixelValue earthImg7 200 125 125 1 1
 $earth -getPixelValue earthImg4 200 125 125 1 1

 diff earthImg4 earthImg7

 rm earthImg earthImg1 earthImg2 earthImg3 earthImg5 earthImg6 earthImg4 earthImg7 reassign.txt
  
fi

if [ ] ; then

 $earth -interpText ../data/wehrli85c.txt oot 500 1 700 2 0
 $earth -spectralResponse oot
 rm oot tmp

fi





if [ 1 ] ; then

 rm *.pgm *.ppm

fi 


if [ 1 ] ; then
 $earth -zenith 3 27 10 10 55.00
 #answer=57.601476
fi

if [ ] ; then

 echo "1.707106 12.500000" > fit.dat
 echo "2.490711 4.166667" >> fit.dat
 echo "3.605550 31.250000" >> fit.dat
 echo "4.297620 81.250000" >> fit.dat
 echo "5.656853 112.500000" >> fit.dat

 echo "f(x)=m*x + c" >  fit.gp
 echo "fit f(x) \"fit.dat\" using 1:2 via m, c" >> fit.gp

 echo "g(x)=m*x" >  fit.gp
 echo "fit g(x) \"fit.dat\" using 1:2 via m" >> fit.gp

 gnuplot fit.gp


 $earth -bivariate fit.dat
 rm fit.dat fit.gp

fi 



fi


if [ ] ; then

 echo "1	5	100" >  kriging.dat
 echo "3  4  105" >> kriging.dat
 echo "1 3 105 " >> kriging.dat
 echo " " >> kriging.dat
 echo "4 5 100" >> kriging.dat
 echo "5 1 115" >> kriging.dat
 echo " " >> kriging.dat
 echo " " >> kriging.dat

 $earth -kriging
 $earth -kriging kriging.dat kriging.img
 rm kriging.dat

fi

if [ ] ; then
 # test data from Isaaks and Srivastra P 291
 echo "61 139 477" >  kriging.dat
 echo "63 140 696" >> kriging.dat
 echo "64 129 227 " >> kriging.dat
 echo "68 128 646" >> kriging.dat
 echo "71 140 606" >> kriging.dat
 echo "73 141 791" >> kriging.dat
 echo "75 128 783 " >> kriging.dat
 echo " " >> kriging.dat

 $earth -kriging kriging.dat kriging.img
 rm kriging.dat

fi


if [ 1 ] ; then

 echo "1	5	100" >  kriging.dat
 echo "3  4  105" >> kriging.dat
 echo "1 3 105 " >> kriging.dat
 echo "4 5 100" >> kriging.dat
 echo "5 1 115" >> kriging.dat
 echo " " >> kriging.dat
 echo " " >> kriging.dat

 # $earth -kriging kriging.dat kriging.img 1 1.0 1
 
 $earth -kriging_point kriging.dat 1.0 4.0 1 1.0 0
 rm kriging.dat

fi



