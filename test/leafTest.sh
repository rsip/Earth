#######

# Testing leaf
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
 


leaf="../bin/leaf"

if [ 1 ] ; then
 
 $leaf

 $leaf -byte2short  	
 $leaf -byte2float  	 
 $leaf -byte2long  	 
 $leaf -float2byte  	 
 $leaf -long2float  	 
 $leaf -long2byte  	 
 $leaf -short2byte  	
 $leaf -short2float  	 
 $leaf -short2long  	 
 $leaf -long2short  	 
 $leaf -ushort2float 	 
 $leaf -ubyte2float 	
 $leaf -ubyte2ushort 	 
 $leaf -ushort2ubyte 	 
 $leaf -float2ubyte 	 
 $leaf -long2ulong  	 
 $leaf -ulong2long  	 
 $leaf -short2ushort  	 
 $leaf -ushort2short  	 
 $leaf -ubyte2byte  	 
 $leaf -byte2ubyte  	
 
 $leaf -linear2dB   	
 $leaf -dB2linear
 $leaf -complex2RealImag   	
 $leaf -complex2PwrPhase
   	   	 
 $leaf -modeFilter 	 	 
 $leaf -meanFilter 	 	 
 $leaf -texture 	

 $leaf -confusion  	  	 
 $leaf -separability 		 
 $leaf -classify
 $leaf -reassign 

 $leaf -copy 	 	 
 $leaf -header 
 $leaf -demSlope   		 
 $leaf -degConv  
 $leaf -spectralResponse

 $leaf -getNumLines
 $leaf -getNumLinesAll   	 
 $leaf -sideCat
 $leaf -calcTotalMean
 $leaf -rows2cols
 $leaf -interpText       
 $leaf -addNoise 

 $leaf -histoArea   	 
 $leaf -anomalies 	 	
 $leaf -standardise  	 
 $leaf -meanArea  		  	 
 $leaf -covariance   	 
 $leaf -stats      		 
 $leaf -hist 
 $leaf -stdev
 $leaf -areaCounter  	    
 $leaf -mean    
 $leaf -addNoiseImg  	 

 $leaf -transect    	 
 $leaf -regression
 $leaf -linear2Dinterp
 $leaf -georeference
 $leaf -rad2ref
 $leaf -rotate 		 
 $leaf -mkimg		 
 $leaf -getPixelValue    	 
 $leaf -diff     	         
 $leaf -add    	 	 
 $leaf -ratio   		
 $leaf -modulus   		 
 $leaf -swap 	 	 
 $leaf -mosaic    		 
 $leaf -thresh   		 	
 $leaf -crop     
 $leaf -mask   		 
 $leaf -xflip 	 	 
 $leaf -yflip               
 $leaf -shiftMeridian  	 
 $leaf -calibrate   
 $leaf -resample  	

 $leaf -bip2bsq   		 
 $leaf -bil2bsq   		
 $leaf -bil2bip   		 
 $leaf -bip2bil   
 $leaf -byte2pgm   	 
 $leaf -pgm2byte  		 
 $leaf -byte2text   	
 $leaf -short2text   	 
 $leaf -float2text   	 
 $leaf -float2textRow   	 
 $leaf -float2textSN   	
 $leaf -text2float   	 
 $leaf -byte2ppm   	 
 $leaf -byte2ppm3           
 $leaf -ppm2byte   	 	 	  	 
 $leaf -dimap2bsq  	
 $leaf -bsq2dimap  	 
 	 
  	 

echo "end of syntax tests"

fi

if [ 1 ] ; then
 
 echo "mking test"

 $leaf -mkimg
 $leaf -mkimg leafImg 600 400 1 10 1
 
fi

if [ 1 ] ; then

 echo "getPixelValue test"

 $leaf -getPixelValue
 $leaf -getPixelValue leafImg 600 200 200 1
 $leaf -getPixelValue leafImg 200 200 200 1 3 
 $leaf -getPixelValue leafImg 600 200 407 1

fi

if [ 1 ] ; then
 
 echo "header test"

 $leaf -header leafImg.hdr
 $leaf -header leafImg.hdr 100 200 10
 $leaf -header leafImg.hdr 100 200 10 2
 $leaf -header leafImg.hdr 100 200 10 2 0
 rm leafImg.hdr
fi

if [ 1 ] ; then

 echo "copy test"

 $leaf -copy
 $leaf -copy leafImg
 $leaf -copy leafImg leafImg2.out
 
 diff leafImg2.out leafImg.out
 diff leafImg leafImg2.out
 rm leafImg2.out leafImg.out
fi

if [ 1 ] ; then

  echo "degConv test"

 $leaf -degConv
 $leaf -degConv -101 45 0
 $leaf -degConv -95 45 0
 $leaf -degConv -1 45 0
 $leaf -degConv 54 45 0 
 $leaf -degConv 54.75 

fi

if [ 1 ] ; then

 echo "Data type conversion tests"

 $leaf -byte2float leafImg leafImg2
 $leaf -getPixelValue leafImg2 300 200 200 4 2
 $leaf -float2byte leafImg2 leafImg3
 diff leafImg leafImg3
 rm leafImg2 leafImg3

 $leaf -ubyte2float leafImg leafImg2
 $leaf -getPixelValue leafImg2 300 200 200 4 2
 $leaf -float2ubyte leafImg2 leafImg3
 diff leafImg leafImg3
 rm leafImg2 leafImg3

 $leaf -byte2long leafImg leafImg2
 $leaf -getPixelValue leafImg2 600 200 200 3 1
 $leaf -long2byte leafImg2 leafImg3
 diff leafImg leafImg3
 rm leafImg2 leafImg3

 $leaf -byte2short leafImg leafImg2
 $leaf -getPixelValue leafImg2 600 200 200 2 1
 $leaf -short2byte leafImg2 leafImg3
 diff leafImg leafImg3
 rm leafImg2 leafImg3

 $leaf -byte2ubyte leafImg leafImg2
 $leaf -getPixelValue leafImg2 600 200 200 1 1
 $leaf -byte2ubyte leafImg2 leafImg3
 diff leafImg leafImg3
 rm leafImg2 leafImg3

 $leaf -ubyte2ushort leafImg leafImg2
 $leaf -getPixelValue leafImg2 600 200 200 2 1
 $leaf -ushort2ubyte leafImg2 leafImg3
 diff leafImg leafImg3
 rm leafImg2 leafImg3

 $leaf -byte2short leafImg leafImg2
 $leaf -getPixelValue leafImg2 600 200 200 2 1
 $leaf -short2ushort leafImg2 leafImg3
 $leaf -getPixelValue leafImg3 600 200 200 2 1
 $leaf -ushort2short leafImg3 leafImg4
 diff leafImg2 leafImg4
 rm leafImg2 leafImg3 leafImg4

 $leaf -byte2short leafImg leafImg2
 $leaf -short2long leafImg2 leafImg3
 $leaf -getPixelValue leafImg3 600 200 200 3 1
 $leaf -long2short leafImg3 leafImg4
 diff leafImg2 leafImg4
 rm leafImg2 leafImg3 leafImg4

 $leaf -byte2short leafImg leafImg2
 $leaf -short2ushort leafImg2 leafImg3
 $leaf -getPixelValue leafImg3 600 200 200 2 1
 $leaf -ushort2short leafImg3 leafImg4
 diff leafImg2 leafImg4
 rm leafImg2 leafImg3 leafImg4

 $leaf -byte2long leafImg leafImg2
 $leaf -long2ulong leafImg2 leafImg3
 $leaf -getPixelValue leafImg3 600 200 200 3 1
 $leaf -ulong2long leafImg3 leafImg4
 diff leafImg2 leafImg4
 rm leafImg2 leafImg3 leafImg4

 $leaf -byte2short leafImg leafImg2
 $leaf -short2float leafImg2 leafImg3 
 $leaf -getPixelValue leafImg3 600 200 200 4 1
 rm leafImg2 leafImg3

 $leaf -byte2short leafImg leafImg2
 $leaf -ushort2float leafImg2 leafImg3 
 $leaf -getPixelValue leafImg3 600 200 200 4 1
 rm leafImg2 leafImg3

 $leaf -byte2long leafImg leafImg2
 $leaf -long2float leafImg2 leafImg3 
 $leaf -getPixelValue leafImg3 600 200 200 4 1
 rm leafImg2 leafImg3

fi

if [ 1 ] ; then  
 echo " Arithmetic tests"
 $leaf -mkimg leafImg2 600 400 1 5 1
 $leaf -add leafImg leafImg2 leafImg3 1
 $leaf -getPixelValue leafImg3 600 200 200 1 1
 rm leafImg2 leafImg3
fi

if [ 1 ] ; then  
 $leaf -mkimg leafImg2 600 400 1 5 1
 $leaf -diff leafImg leafImg2 leafImg3 1
 $leaf -getPixelValue leafImg3 600 200 200 1 1
 rm leafImg2 leafImg3
fi

if [ 1 ] ; then  
 $leaf -mkimg leafImg2 600 400 4 5
 $leaf -mkimg leafImg3 600 400 4 15
 $leaf -ratio leafImg3 leafImg2 leafImg4 4
 $leaf -getPixelValue leafImg4 600 200 200 4 1
 rm leafImg2 leafImg3 leafImg4
fi

if [ 1 ] ; then  
 $leaf -mkimg leafImg2 600 400 4 5
 $leaf -modulus leafImg2 leafImg3 4
 $leaf -getPixelValue leafImg2 600 200 200 4 1
 $leaf -getPixelValue leafImg3 600 200 200 4 1
 rm leafImg2 leafImg3 
fi

if [ 1 ] ; then  
 $leaf -mkimg leafImg2 600 400 4 -5
 $leaf -modulus leafImg2 leafImg3 4
 $leaf -getPixelValue leafImg2 600 200 200 4 1
 $leaf -getPixelValue leafImg3 600 200 200 4 1
 rm leafImg2 leafImg3 
fi

if [ 1 ] ; then
 echo " Swap tests"
 $leaf -mkimg leafImg 600 400 2 10
 $leaf -getPixelValue leafImg 600 200 200 2 1
 $leaf -swap leafImg leafImg2 2
 $leaf -getPixelValue leafImg2 600 200 200 2 1
 rm leafImg2

fi



if [ 1 ] ; then

  $leaf -mkimg leafImg 600 600 1 10
  $leaf -byte2text leafImg leafImg.txt 600
    
  $leaf -mkimg leafImg2 600 600 2 10
  $leaf -short2text leafImg2 leafImg2.txt 600

  $leaf -mkimg leafImg3 50 50 4 10
  $leaf -float2text leafImg3 leafImg3.txt 50
  $leaf -float2textRow leafImg3 leafImg4.txt 50
  $leaf -float2textSN leafImg3 leafImg5.txt 50

  rm leafImg.txt leafImg2.txt leafImg3.txt leafImg4.txt leafImg5.txt

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

 $leaf -sideCat test3.txt textTest.txt testout.txt
 $leaf -sideCat textTest.txt test3.txt testout.txt
 rm test3.txt textTest.txt testout.txt

fi

if [ 1 ] ; then

 echo  "1 2 3 4 5 6 7" > testrow2col.txt
 echo  "8 9 10 11 12 13 14" >> testrow2col.txt
 echo  "15 16 17 18 19 20 21" >> testrow2col.txt
 echo  "22 23 24 25 26 27 28" >>  testrow2col.txt  
   
 $leaf -rows2cols testrow2col.txt testoutrow2col.txt
 $leaf -text2float testrow2col.txt testFloat
 $leaf -getPixelValue testFloat 7 1 1 4 1
 $leaf -getPixelValue testFloat 7 1 2 4 1
 $leaf -getPixelValue testFloat 7 7 4 4 1

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

 $leaf -calcTotalMean meanTest.txt
 rm meanTest.txt
fi


if [ 1 ] ; then
 
 echo "leafImg" > meanImgtest.txt
 echo "leafImg2" >> meanImgtest.txt
 echo "leafImg3" >> meanImgtest.txt
 
 $leaf -mkimg leafImg 600 600 1 10
 $leaf -mkimg leafImg2 600 600 1 5
 $leaf -mkimg leafImg3 600 600 1 6   
 $leaf -mean meanImgtest.txt leafImg4	 
 $leaf -getPixelValue leafImg4 600 200 200 4 1  

 rm leafImg leafImg2 leafImg3 meanImgtest.txt leafImg4

fi

if [ 1 ] ; then

 $leaf -mkimg leafImg1 100 100 1 50
 $leaf -mkimg leafImg2 100 100 1 127
 $leaf -mkimg leafImg3 100 100 1 225
 $leaf -mkimg leafImgb1 200 200 1 0
 $leaf -mkimg leafImgb2 200 200 1 0
 $leaf -mkimg leafImgb3 200 200 1 0

 $leaf -mosaic leafImgb1 leafImg1 200 100 0 100 1
 $leaf -mosaic leafImgb1 leafImg2 200 100 100 100 1
 $leaf -mosaic leafImgb1 leafImg3 200 100 100 0 1

 $leaf -mosaic leafImgb2 leafImg1 200 100 0 0 1 
 $leaf -mosaic leafImgb2 leafImg2 200 100 0 100 1
 $leaf -mosaic leafImgb2 leafImg3 200 100 100 0 1

 $leaf -mosaic leafImgb3 leafImg1 200 100 100 0 1
 $leaf -mosaic leafImgb3 leafImg2 200 100 0 0 1
 $leaf -mosaic leafImgb3 leafImg3 200 100 0 100 1

 cat leafImgb1 leafImgb2 leafImgb3 > leafImg
 $leaf -byte2ppm3 leafImg leafImg3.ppm 200

fi 

if [ 1 ] ; then
 
 echo "Test flip"
 $leaf -mkimg leafImg 600 600 2 10
 $leaf -mkimg leafImg1 100 100 2 5
 $leaf -mosaic leafImg leafImg1 600 100 0 0 2
 $leaf -xflip leafImg leafImgx 600 2 1
 $leaf -short2byte leafImgx leafImg2
 $leaf -byte2pgm leafImg2 leafImgXflip.pgm 600 15
 
 $leaf -yflip leafImg leafImgy 600 2 1
 $leaf -short2byte leafImgy leafImg3
 $leaf -byte2pgm leafImg3 leafImgYflip.pgm 600 15

 $leaf -shiftMeridian leafImg leafImgS 600 2 1
 $leaf -short2byte leafImgS leafImg4
 $leaf -byte2pgm leafImg4 leafImgS.pgm 600 15

 rm leafImg leafImg1 leafImgx leafImg2 leafImgy leafImgS leafImg4 leafImg3

fi


if [ 1 ] ; then

 echo "1" > test3.txt
 echo "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt
 echo  "1" >> test3.txt

 $leaf -addNoise test3.txt test4.txt 0.2
 $leaf -mkimg leafImgb1 600 600 1 10
 $leaf -addNoiseImg leafImgb1 leafImgNoise 0.2  
 $leaf -getPixelValue leafImgNoise 600 100 100 4 1
 $leaf -getPixelValue leafImgNoise 600 50 100 4 1
 $leaf -getPixelValue leafImgNoise 600 100 50 4 1
  
 $leaf -anomalies leafImgNoise leafImgb2 4
 $leaf -getPixelValue leafImgb2 600 50 100 4 1  
 
 $leaf -standardise leafImgNoise leafImgb2 4
 $leaf -getPixelValue leafImgb2 600 50 100 4 1

 rm test3.txt test4.txt leafImgb1 leafImgNoise leafImgb2 leafImgb3
 
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

 #$leaf  -getNumLines ../src/getPixel.c
 #$leaf -getNumLinesAll ../src/getPixel.c   	
 $leaf  -getNumLines textTest.txt 	
 $leaf -getNumLinesAll textTest.txt  	
 rm textTest.txt

fi

if [ 1 ] ; then
 
 echo "Calibrate test"

 echo  "0 10" >  Test3.txt
 echo  "10 0" >> Test3.txt
 echo  "1 1"   >> Test3.txt
 echo  " "   >> Test3.txt
 echo  " "   >> Test3.txt

 $leaf -mkimg leafImg1 100 100 1 1
 $leaf -mkimg leafImg2 100 100 1 2
 $leaf -mkimg leafImg3 100 100 1 3

 cat leafImg1 leafImg2 leafImg3 > leafImg
 rm leafImg1 leafImg2 leafImg3

 $leaf -calibrate leafImg leafImg.out Test3.txt 1 3
 $leaf -getPixelValue leafImg.out 100 50 50 4 3
 rm leafImg Test3.txt leafImg.out

fi



if [ 1 ] ; then
 
 echo "DIMAP Test"
 
 mkdir dimapTest
 $leaf -mkimg dimapTest/leafImg1 100 100 1 1
 $leaf -mkimg dimapTest/leafImg2 100 100 1 2
 $leaf -mkimg dimapTest/leafImg3 100 100 1 3

 cat dimapTest/leafImg1 dimapTest/leafImg2 dimapTest/leafImg3 > leafImgTest
 
 $leaf -dimap2bsq dimapTest leafImg
 diff leafImgTest leafImg
 
 $leaf -bsq2dimap leafImg dimapTest2 3
 diff dimapTest/leafImg1 dimapTest2/leafImg-channel-1
 diff dimapTest/leafImg2 dimapTest2/leafImg-channel-2
 diff dimapTest/leafImg3 dimapTest2/leafImg-channel-3

 rm -rf dimapTest dimapTest2
 rm leafImgTest leafImg

 

fi

if [ 1 ] ; then
 
 echo "Test resample"
 $leaf -mkimg leafImg 600 600 2 10
 $leaf -mkimg leafImg1 300 300 2 5
 $leaf -mosaic leafImg leafImg1 600 300 0 0 2
 $leaf -short2byte leafImg leafImg3
 $leaf -byte2pgm leafImg3 leafImg3.pgm 600 15
 
 
 $leaf -resample leafImg leafImgx 600 0.5 2
 $leaf -short2byte leafImgx leafImg2
 $leaf -byte2pgm leafImg2 leafImgResample.pgm 300 15
 
 rm leafImg leafImg1 leafImg2 leafImgx leafImg3

fi

if [ 1 ] ; then

 $leaf -mkimg leafImg 600 600 1 10
 $leaf -mkimg leafImg1 100 100 1 5
 $leaf -mosaic leafImg leafImg1 600 100 100 100 1
 $leaf -byte2pgm leafImg leafImg.pgm 600 15
 $leaf -pgm2byte leafImg.pgm leafImg2
 $leaf -byte2pgm leafImg2 leafImg2.pgm 600 15 
 diff leafImg.pgm leafImg2.pgm

 $leaf -getPixelValue leafImg2 600 300 300 1 1
 $leaf -getPixelValue leafImg 600 300 300 1 1
 $leaf -getPixelValue leafImg2 600 120 120 1 1
 $leaf -getPixelValue leafImg 600 120 120 1 1

 $leaf -thresh leafImg leafImg3 7 7 1		 
 $leaf -byte2pgm leafImg3 leafImg2.pgm 600 2
 $leaf -areaCounter leafImg3     

 $leaf -crop leafImg leafImg4 600 100 100 200 200 1
 $leaf -byte2pgm leafImg4 leafImg3.pgm 200 15

 $leaf -mask leafImg leafImg3 leafImg5 1
 $leaf -getPixelValue leafImg5 600 300 300 1 1
 $leaf -getPixelValue leafImg5 600 120 120 1 1
 
 echo "5 7" > reassign.txt
 echo "10 6" >> reassign.txt 
 
 $leaf -reassign leafImg leafImg6 reassign.txt
 $leaf -getPixelValue leafImg6 600 300 300 1 1
 $leaf -getPixelValue leafImg6 600 120 120 1 1

 diff leafImg leafImg2

 $leaf -byte2ppm leafImg4 leafImgCol.pgm 200
 $leaf -ppm2byte leafImgCol.pgm leafImg7
 $leaf -byte2ppm leafImg7 leafImgCol2.pgm 200

 $leaf -getPixelValue leafImg7 200 25 25 1 1
 $leaf -getPixelValue leafImg4 200 25 25 1 1
 $leaf -getPixelValue leafImg7 200 125 125 1 1
 $leaf -getPixelValue leafImg4 200 125 125 1 1

 diff leafImg4 leafImg7

 rm leafImg leafImg1 leafImg2 leafImg3 leafImg5 leafImg6 leafImg4 leafImg7 reassign.txt
  
fi

if [ ] ; then

 $leaf -interpText ../data/wehrli85c.txt oot 500 1 700 2 0
 $leaf -spectralResponse oot
 rm oot tmp

fi

if [ 1 ] ; then

 rm *.pgm *.ppm

fi 



