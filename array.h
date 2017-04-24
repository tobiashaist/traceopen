////////////////////////////////////////////////////////////
/// \file array.h
/// \brief include file for template Class Array
///  \date 27.5.2007
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
///  Copyright Institute of Applied Optics, University of Stuttgart ITO 1999
///  Paffenwaldring 9
///  70569 Stuttgart
///  Germany
/// 
/// This is a rewrite of a very old class (programmed in 1999) by me.

/// To be implemented
/// - wrap 2pi
/// - TIFF Funktion if defined LIBTIFF
/// - Bildverarbeitung:
///    - Gaussfilter
///    - Mittelwertfilter
///    - Median
///    - Threshold globale
///    - Threshold local
///    - Threshold bernsen
///    - Gamma
///    - Schwerpunkt
///    - NGC
///    - SAE
///    - Auflösung Reduzieren um Faktor 2
///    - evtl. die ganzen Funktionen, die netpbm bietet (nur wenn auch Windwos)
///    - evtl. die ganzen Funktionen von imagick (nur wenn auch Windows)
///    - search one peak
///    - locate one peak
///    - pce
///    - draw circle
///    - draw rectangle
/// - Nullstellensuche
/// - Ableitung
///
/// - Matrix * vektor
/// - Matrix * Matrix
/// - SV Zerlegung LGS
/// - Hanning Window
/// - Bartlett Window
/// - Zeropadding
/// - shift
/// - RekonstruktionPhasenholo
/// - RekonstruktionAmplitudenholo
/// - Propagation ebene Wellen
/// - sinc
/// - rect
/// - LCD
/// - Airy
/// - PV Fehler
/// - RMS Fehler
/// - Marcheval usw.
/// - Zernike Fit
/// - gnuplot
/// - Polynomfit
/// - CurveFit
/// - y oder y akkumulieren
/// - Korrelation
/// - SAE


#ifndef ARRAY_HPP 
#define ARRAY_HPP

#define ARRAYDEBUG 0

#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////
///  \brief Management of a 2D (and 1D) Arrays of different Type 
////////////////////////////////////////////////////////////
///  
///  This is the main class/basic building block for representing images (greyscale), 
///  light fields and related data structures. Also some simple and often used
///  methods are implemented.
///
/// This is a rewrite of one of my very old classes (programmed in 1999).
///  \date 27.5.2007
///  \author Tobias Haist  (haist@ito.uni-stuttgart.de)
////////////////////////////////////////////////////////////
template <class Type> 
class Array {

public:
  Array();                      ///< construction with STDIN with an 8Bit binary PGM File
  Array( int c_sx,  int c_sy); ///< construction with given size
  Array( char *);          ///< construction with a 8Bit binary PGM File    	  
  Array(Array<Type>&);		///< construction with another Array 

  ~Array();			///< Destructor
   Type &     operator[] ( int c_ix);     ///< get element i
   Type &     _( int c_x,  int c_y); ///< get element (x,y) 

  inline int  getSizeX(void)  { return mSizeX;} ///< return the horizonal size (# of columns)
  inline int  getSizeY(void)  { return mSizeY;} ///< return the verticall size (# of rows)
  inline Type* getAddress(void)  { return mArray;}  ///< return address of the data block
  void load(const char *);                 ///< load a 8 Bit greyscale binary PGM file
  void save(const char *) ;            ///< save a 8 Bit greyscale binary PGM file

  void set(Type);                           ///< set all values of the Array to a constant

  Array& operator=( Array &);   ///< assignment operator
  Array& operator+( Array &);   ///< pointwise + 
  Array& operator+=( Array &);  ///< pointwise += 
  Array& operator-( Array &);   ///< pointwise -
  Array& operator-=( Array &);  ///< pointwise -= 
  Array& operator*( Array &);   ///< pointwise *
  Array& operator*=( Array &);  ///< pointwise *= 
  Array& operator/( Array &);   ///< pointwise /
  Array& operator/=( Array &);  ///< pointwise /= 

  Array& operator+=( Type);   ///< pointwise += 
  Array& operator+( Type);    ///< pointwise +
  Array& operator-=( Type);   ///< pointwise -= 
  Array& operator-( Type);    ///< pointwise -
  Array& operator*=( Type);   ///< pointwise *= 
  Array& operator*( Type);    ///< pointwise *
  Array& operator/=( Type);   ///< pointwise /= 
  Array& operator/( Type);    ///< pointwise / 

  void show(int x0=0, int y0=0, int xe=0, int ye=0); ///< show numerically the data of the array
  void norm( double);	       ///< normalisation with max and min 
  void normHigh( double);	       ///< normalisation with max and min 
  void paste(Array<Type>& largearray,
	     int topleftX,int topleftY); ///<  copy into a larger array
  Type maxmin(Type *mini) ; ///< search maximum and minimum of the array 
  void random(Type maximum); ///< fill the array with random values
    
  void smooth(int halfwidthx, int halfwidthy); ///< simple constant smoothing window
  void smoothFast(int halfwidthx, int halfwidthy); ///< simple constant smoothing window
  void logicalOr(Array& data2);                 ///< binary or of two images
  Array& resize(int n);                    ///< zooming image by a constant factor

  void globalThreshold(Type threshold, Type value1, Type value2); ///< global Threshold
  void bernsen(int halfwidthx, int halfwidthy); ///< local binarization according to Bernsen
  void local(int halfwidthx, int halfwidthy);  ///< local binarization
  void centerOfGravity(Type threshold, 
		       double* centerX, double* centerY); ///< center of gravity
  double mean(); 		          ///< mean value of the array
  void cutCircle(int cx, int cy, int r, Type value); ///< set circular area to value
    void zeroPadTo(int newsize);           ///< ZeroPad to a new size for quadratic Arrays

    void setChecked(int x, int y, Type value);

protected:
  Type 	    *mArray;	    	          ///< Data 
  int 	    mSizeX;                       ///< width in pixel (# of columns)
  int 	    mSizeY;                       ///< height in pixel (# of rows)
};

#endif
