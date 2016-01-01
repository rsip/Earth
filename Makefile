#####################################
#  Makefile for compiling Numerical.
#  Creates both a static and a
#  dynamic library. 
#
# Need to set up LD_LIBRARY_PATH
# for shared libraries.
#
# Will Grey
# 18 Nobember 2015
#####################################

CC=gcc
BINDIR = bin/
SRCDIR = src/
NUMDIR = numerical/
LIBDIR = lib/
LIB = -lm
CFLAGS = -Wall -I. -Inumerical -Isrc

SRC = leaf.c swap.c copy.c header.c flip.c utility.c convertType.c diff.c add.c text.c areaCounter.c\
      ratio.c modulus.c mask.c thresh.c calibrate.c interleave.c bin2text.c shiftMeridian.c degConv.c\
      byte2pgm.c byte2ppm.c ppm2byte.c pgm2byte.c linear2dB.c mkimg.c complex.c crop.c getPixel.c mosaic.c\
      reassign.c confusion.c modeFilter.c meanFilter.c mean.c anomalies.c bsq2dimap.c dimap2bsq.c standardise.c\
      georeference.c resample.c texture.c regression.c rotate.c covarianceMatrix.c meanArea.c transect.c stats.c\
      histogram.c histoArea.c classify.c separability.c interpText.c spectralResponse.c linear2Dinterp.c\
      rad2ref.c rows2cols.c text2float.c noise.c noiseImg.c stdev.c demSlope.c

NUMERICAL = bivariateStats.c matrix.c univariateStats.c
   
CSources = $(addprefix $(SRCDIR),$(SRC))
NUMSources = $(addprefix $(NUMDIR),$(NUMERICAL))

all : $(BINDIR)leaf

$(BINDIR)leaf : $(CSources) $(NUMSources)
	$(CC) $(CSources) $(NUMSources) -o $(BINDIR)leaf -Llib $(LIB) $(CFLAGS)

clean :
	rm -f $(BINDIR)leaf
	
