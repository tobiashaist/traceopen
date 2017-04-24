//////////////////////////////////////////////////////////////////////
/// \file array.cc

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "array.h"     
#include "error.h"     

#define ITOARRAYDEBUG 0

// Remark: The following definition doesn't show up in doxygen due to
// the template specialization
//////////////////////////////////////////////////////////////////////////////
/// \warning might not work with all correct binary pgms !
/// \warning only works with 8 Bit images
/// \exception Error with ERRORFILE or bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <> 
Array<unsigned char>::Array()
{
  char id [80];			// for non-evil pgms that should work
  int sx, sy;			// width and height of PGM
  int grey;			// number of greylevels in PGM 
  do				// First we read until all comments (#) and Type are read
    cin.getline(id,79,'\n');
  while (*id == '#' || *id == 'P');

  sscanf(id,"%d %d", &sx, &sy);	// Now width and height 
  cin >> grey;			// and grey levels
  //  cerr << grey << endl;
  if(grey != 255)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"not a valid 16 bit pgm", ERRORFILE);

  mSizeX=sx;
  mSizeY=sy;

  mArray=new unsigned char [mSizeX*mSizeY];   
  if(mArray == 0)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"not enough memory", ERRORMEMORY);

  // You might include more error handling code but for cin I think it is
  // (hopefully) not necessary.

  cin.read((char*)getAddress(), 1); // why is that ???
  cin.read((char*)getAddress(), mSizeX*mSizeY*sizeof(unsigned char));
  if(cin.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while reading", ERRORFILE);
}

//////////////////////////////////////////////////////////////////////////////
/// \param c_sx width 
/// \param c_sy height
/// \exception bad_alloc
/// \warning: No initialization
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>::Array( int c_sx,  int c_sy)
{
  mSizeX = c_sx;
  mSizeY = c_sy;
  mArray = new Type[mSizeX*mSizeY];
  //  for(int t=0; t < mSizeX*mSizeY; t++) // old initialization with zeros !
  //    mArray[t] = 0;
}

//////////////////////////////////////////////////////////////////////////////
/// \param data the Array to be copied
/// \exception bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>::Array(Array<Type>& data)
{
  int c_sx = data.mSizeX;
  int c_sy = data.mSizeY;
  mSizeX = c_sx;
  mSizeY = c_sy;
  mArray = new Type[c_sx*c_sy];

  for(int t=0; t < mSizeX*mSizeY; t++)
    mArray[t] = data[t];
}

//////////////////////////////////////////////////////////////////////////////
/// \param c_filename filename with path of the PGM file
/// \warning might not work with all correct binary pgms !
/// \warning only works with 8 Bit images
/// \warning: inefficient for uchar because data is first copied to a temp buffer  (replace with specialization for uchar)
/// \exception bad_alloc or ERROR with ERRORFILE
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>::Array( char *c_filename)
{
  char id [80];			// for non-evil pgms that should work
  int sx, sy;			// width and height of PGM
  int grey;			// number of greylevels in PGM 

  ifstream input(c_filename, ios::in);
  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"can't open input file", ERRORFILE);

  do 
    input.getline(id,79,'\n');
  while ((*id == '#' || *id == 'P') && input.good());

  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while reading", ERRORFILE);

  sscanf(id,"%d %d", &sx, &sy);
  input >> grey;

  if(grey != 255)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"greyscale != 255", ERRORFILE);

  mSizeX=sx;
  mSizeY=sy;
  unsigned char data[sx*sy];	// temporary buffer because conversion might be nec.
  mArray = new Type[sx*sy];	// the real data
  input.read((char*) data, 1);	// I don't know why that is necessary !
  input.read((char*)data, mSizeX*mSizeY*sizeof(unsigned char));
  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while reading", ERRORFILE);
  input.close();

  for(int t=sx*sy-1; t>=0; t--)	// copy the data into the real buffer
    mArray[t] = data[t];
}



//////////////////////////////////////////////////////////////////////////////
template <>
Array<short int>::Array( char *c_filename)
{
  char id [80];			// for non-evil pgms that should work
  int sx, sy;			// width and height of PGM
  int grey;			// number of greylevels in PGM 

  cerr << "nun !" << endl;
  ifstream input(c_filename, ios::in);
  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"can't open input file", ERRORFILE);

  do 
    input.getline(id,79,'\n');
  while ((*id == '#' || *id == 'P') && input.good());

  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while reading", ERRORFILE);

  sscanf(id,"%d %d", &sx, &sy);
  input >> grey;

  if(grey != 65535)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"not a valid 16 bit pgm", ERRORFILE);

  mSizeX=sx;
  mSizeY=sy;
  mArray = new short int[sx*sy*2];	// the real data
  input.read((char*) mArray, 1);	// I don't know why that is necessary !
  input.read((char*) mArray, mSizeX*mSizeY*sizeof(short int));
  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while reading", ERRORFILE);
  input.close();

  for(int y=0; y < mSizeY; y++)
    for(int x=0; x < mSizeX; x++)
      {
	short int a = mArray[x + y*sx];
	unsigned short int a1 = a & 255;
	unsigned short int a2 = a & 0xff << 8;
	if(a != 0)
	  cerr << a << "  " << (a & (short int) 0x00ff) << endl;
	  //	  cerr << (int) a1 << "  " << (int) a2 << "  " << a << "  " << static_cast<short int>(a & 0xff) << endl;
	mArray[x+y*sx] = a2+ a1*255;
      }
}

//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>::~Array()
{
   delete [] mArray;
}


//////////////////////////////////////////////////////////////////////////////
/// \param newsize new size for the array (quadratic array !)
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::zeroPadTo(int newsize)
{
  Type* arrayNew = new Type[newsize*newsize];
  for(int t = newsize*newsize-1; t >= 0; t--)
    arrayNew[t] = 0;
  
  int newcenter = newsize/2;
  int xc = mSizeX/2;
  int yc = mSizeY/2;
  int shiftX = newcenter - xc;
  int shiftY = newcenter - yc;

  for(int y=0; y < mSizeY; y++)
    for(int x=0; x < mSizeX; x++)
      arrayNew[ x+shiftX + newsize*(y+shiftY)] = mArray[ x + y*mSizeX];

  delete [] mArray;
  mSizeY = mSizeX = newsize;
  mArray = arrayNew;
   
}

//////////////////////////////////////////////////////////////////////////////
/// \param c_ix index within the array
/// \return reference to element
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
inline Type& Array<Type>::operator[](int c_ix)
{
#if ARRAYDEBUG
  if(c_ix <0 || c_ix >= mSizeX*mSizeY)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"wrong index []", ERRORARRAY);
#endif
  return mArray[c_ix];
}

//////////////////////////////////////////////////////////////////////////////
/// \param c_x index within the array x
/// \param c_y index within the array y
/// \return reference to element
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
inline Type& Array<Type>::_( int c_x,  int c_y) 
{
#if ARRAYDEBUG
  if(c_x <0 || c_x >= mSizeX || c_y < 0 || c_y >= mSizeY )
    throw Error(__PRETTY_FUNCTION__, __LINE__,"wrong index _(x,y)", ERRORARRAY);
#endif
  return mArray[c_x + c_y*mSizeX];
} 

//////////////////////////////////////////////////////////////////////////////
/// \param c_x index within the array x
/// \param c_y index within the array y
/// \return reference to element
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
inline void Array<Type>::setChecked( int c_x,  int c_y, Type value) 
{
  if(c_x <0 || c_x >= mSizeX || c_y < 0 || c_y >= mSizeY )
    return;

  mArray[c_x + c_y*mSizeX] = value;
} 

//////////////////////////////////////////////////////////////////////////////
/// \param value of the ant
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void  Array<Type>::show(int x0, int y0, int xe, int ye)
{
  if(xe < x0 || ye < y0)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"wrong parameters for show", ERRORARRAY);
  if(xe == 0 || ye == 0)
    {
      x0 = y0 = 0;
      xe = mSizeX;
      ye = mSizeY;
    }
  for(int y=y0; y < ye; y++)
    {
      for(int x=x0; x < xe; x++)
	cout << static_cast<float>(_(x,y)) << "\t";
      cout << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////
/// \param value of the constant
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void  Array<Type>::set(Type value)
{
  for(int t=mSizeX * mSizeY-1; t>= 0; t--)
    mArray[t] = value;
}

//////////////////////////////////////////////////////////////////////////////
/// \param c_filename  Filename with path of the pgm file
/// \exception bad_alloc or ERROR with ERRORFILE
/// \warning: inefficient for uchar because data is first copied to a temp buffer (replace with specialization for uchar)
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void  Array<Type>::save(const char *c_filename) 
{
  // -- Copy to temporary buffer because of conversion to uchar
  unsigned char* bild = new unsigned char[mSizeX * mSizeY];
  for(int t=0; t < mSizeX * mSizeY; t++)
    *(bild + t) = static_cast<unsigned char>(mArray[t]);

  ofstream output(c_filename, ios::out);
  if(output.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"can't open output file", ERRORFILE);

  output <<  "P5" << endl << mSizeX << " " << mSizeY << endl << 255 << endl;
  if(output.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while writing", ERRORFILE);

  output.write((char*) bild, mSizeX*mSizeY*sizeof(unsigned char));
  if(output.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"can't open output file", ERRORFILE);

  delete [] bild;
}       

//////////////////////////////////////////////////////////////////////////////
/// \param c_filename the filename of the pgm file
/// \warning: inefficient because data is first copied to a temp buffer (replace with specialization for uchar)
// Nearly the same than the ctor(filename). Therefore one main function might/should
// be created to avoid code duplication (do it if you like !)
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::load(const char *c_filename)
{
  char id [80];			// for non-evil pgms that should work
  int sx, sy;			// width and height of PGM
  int grey;			// number of greylevels in PGM 

  ifstream input(c_filename, ios::in);
  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"can't open input file", ERRORFILE);

  do 
    input.getline(id,79,'\n');
  while ((*id == '#' || *id == 'P') && input.good());

  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while reading", ERRORFILE);

  sscanf(id,"%d %d", &sx, &sy);
  input >> grey;

  if(grey != 255)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"greyscale != 255", ERRORFILE);

  if(mSizeX != sx || mSizeY != sy)
    {  
      delete [] mArray;
      mArray = new Type[sx*sy];	// the real data
    }

  mSizeX=sx;
  mSizeY=sy;
  
  unsigned char data[sx*sy];	// temporary buffer because conversion might be nec.
  input.read((char*) data, 1);	// I don't know why that is necessary !
  input.read((char*)data, mSizeX*mSizeY*sizeof(unsigned char));
  if(input.fail())
    throw Error(__PRETTY_FUNCTION__, __LINE__,"error while reading", ERRORFILE);
  input.close();

  for(int t=sx*sy-1; t>=0; t--)	// copy the data into the real buffer
    mArray[t] = data[t];
}

//////////////////////////////////////////////////////////////////////////////
/// \param quelle source
/// \warning should also work with arrays of different size, but NOT WELL TESTED yet
/// \exception bad_alloc 
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator=(Array<Type> &quelle)
{
 if(this == &quelle)
   return *this;

 int qsx=quelle.mSizeX;
 int qsy=quelle.mSizeY;
 if(mSizeX != qsx || mSizeY != qsy)
   {
     delete [] mArray;
     mArray=new Type[qsx*qsy];    
     mSizeX=qsx;
     mSizeY=qsy;     
   }

 for(int t=0; t < qsx*qsy; t++)
   mArray[t] = quelle.mArray[t];

 return *this;
}

 
//////////////////////////////////////////////////////////////////////////////
/// \param source source data
/// \exception Error "Array Size 1 != Array Size 2"
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator+=( Array<Type> &source)
{
 if(mSizeX != source.mSizeX)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 x", ERRORARRAY);
 if(mSizeY != source.mSizeY)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 y", ERRORARRAY);
   
 for(int t=0; t < source.mSizeX * source.mSizeY; t++)
   mArray[t] += source.mArray[t];
 return *this;     
}

//////////////////////////////////////////////////////////////////////////////
/// \param source source data
/// \exception Error "Array Size ! != Array Size 2"
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator-=( Array<Type> &source)
{
 if(mSizeX != source.mSizeX)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 x", ERRORARRAY);
 if(mSizeY != source.mSizeY)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 y", ERRORARRAY);
   
 for(int t=0; t < source.mSizeX * source.mSizeY; t++)
   mArray[t] -= source.mArray[t];
 return *this;
}

//////////////////////////////////////////////////////////////////////////////
/// \param source source data
/// \exception Error "Array Size ! != Array Size 2"
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator*=( Array<Type> &source)
{
 if(mSizeX != source.mSizeX)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 x", ERRORARRAY);
 if(mSizeY != source.mSizeY)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 y", ERRORARRAY);
   
 for(int t=0; t < source.mSizeX * source.mSizeY; t++)
   mArray[t] *= source.mArray[t];
 return *this;
}

//////////////////////////////////////////////////////////////////////////////
/// \param source source data
/// \exception Error "Array Size ! != Array Size 2"
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator/=( Array<Type> &source)
{
 if(mSizeX != source.mSizeX)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 x", ERRORARRAY);
 if(mSizeY != source.mSizeY)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 y", ERRORARRAY);
   
 for(int t=0; t < source.mSizeX * source.mSizeY; t++)
   mArray[t] /= source.mArray[t];
 return *this;
}

//////////////////////////////////////////////////////////////////////////////
/// \param source source data
/// \warning time consuming
/// \exception Error "Array Size ! != Array Size 2" or bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator+( Array<Type> &source)
{
 Array<Type> *result;
 result = new Array(source.mSizeX, source.mSizeY);
 *result = *this;

 for(int t=0; t < source.mSizeX * source.mSizeY; t++) 
   result->mArray[t] += source.mArray[t];
 return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param source source
/// \warning time consuming
/// \exception Error "Array Size ! != Array Size 2" or bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator-( Array<Type> &source)
{
  Array<Type> *result;
  result = new Array(source.mSizeX, source.mSizeY);
  *result = *this;
  for(int t=0; t < source.mSizeX * source.mSizeY; t++) 
    result->mArray[t] -= source.mArray[t];
  return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param source source data
/// \warning time consuming
/// \exception Error "Array Size ! != Array Size 2" or bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator*( Array<Type> &source)
{
 Array<Type> *result;
 result = new Array(source.mSizeX, source.mSizeY);
 *result = *this;

 for(int t=0; t < source.mSizeX * source.mSizeY; t++) 
   result->mArray[t] *= source.mArray[t];
 return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param source source data
/// \warning time consuming
/// \exception Error "Array Size ! != Array Size 2" or bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator/( Array<Type> &source)
{
 Array<Type> *result;
 result = new Array(source.mSizeX, source.mSizeY);
 *result = *this;

 for(int t=0; t < source.mSizeX * source.mSizeY; t++) 
   result->mArray[t] /= source.mArray[t];
 return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
/// \exception bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator*( Type val )
{
 Array<Type> *result;
 result = new Array(this->mSizeX, this->mSizeY);
 *result = *this;
 *result *= val;
 return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator*=( Type val )
{
 for(int t=0; t < mSizeX * mSizeY; t++) 
   mArray[t] *= static_cast<Type>(val);
 return *this;
}

//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
/// \exception bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator+( Type val )
{
 Array<Type> *result;
 result = new Array(this->mSizeX, this->mSizeY);
 *result = *this;
 *result += val;
 return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator+=( Type val )
{
 for(int t=0; t < mSizeX * mSizeY; t++) 
   mArray[t] += static_cast<Type>(val);
 return *this;
}


//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
/// \exception bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator-( Type val )
{
 Array<Type> *result;
 result = new Array(this->mSizeX, this->mSizeY);
 *result = *this;
 *result += val;
 return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator-=( Type val )
{
 for(int t=0; t < mSizeX * mSizeY; t++) 
   mArray[t] += static_cast<Type>(val);
 return *this;
}

//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
/// \exception bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator/( Type val )
{
 Array<Type> *result;
 result = new Array(this->mSizeX, this->mSizeY);
 *result = *this;
 *result /= val;
 return *result;
}

//////////////////////////////////////////////////////////////////////////////
/// \param val scalar value
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::operator/=( Type val )
{
 for(int t=0; t < mSizeX * mSizeY; t++) 
   mArray[t] /= static_cast<Type>(val);
 return *this;
}

//////////////////////////////////////////////////////////////////////////////
/// \param *mini pointer to the minimum (result 1)
/// \result maximum (result2)
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Type Array<Type>::maxmin(Type *mini) 
{
 Type max = mArray[0];
 *mini = mArray[0];

 for(int t=1; t < mSizeX*mSizeY; t++)
 {
   if(mArray[t] > max)
     max = mArray[t];
   if(mArray[t] < *mini) // might be accelerated
     *mini = mArray[t];  
 }
 return max;
}

//////////////////////////////////////////////////////////////////////////////
/// \param smaller array
/// \param  X coordinate of top left corner where smaller array shall be placed
/// \param  Y coordinate of top left corner where smaller array shall be placed
/// \exception Error with ERRORARRAY
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::paste(Array<Type>& smallarray, int c_topleftX, int c_topleftY)
{
  int k,l;
  int sx = mSizeX;
  int sy = mSizeY;
  int small_sx = smallarray.mSizeX;
  int small_sy = smallarray.mSizeY;

  if(c_topleftX+small_sx > sx)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"Paste: Array Index x > max", ERRORARRAY);
  if(c_topleftY+small_sy > sy)
    throw Error(__PRETTY_FUNCTION__, __LINE__,"Paste: Array Index y> max", ERRORARRAY);  

  for(k = 0; k < small_sx; k++)
    for(l = 0; l < small_sy; l++)
	_(k + c_topleftX, l + c_topleftY)= smallarray._(k,l);
}


//////////////////////////////////////////////////////////////////////////////
/// \param newmax new maximum value
/// \todo: constant 1e31 should be avoided
/// \todo  if all values = 0 -> no change; all values the same -> all newmax  
/// \warning scaling greater than 100000 times is not performed !
/// \warning if maximum-minimum < 10^-31 (Array is constant) the value will be set to newmax for the whole Array
//////////////////////////////////////////////////////////////////////////////
template <class Type>
void Array<Type>::norm( double newmax)
{
 float scale;              /* scaling factor */
 int size = mSizeX * mSizeY;     
 Type maxi, minimum;
 maxi = maxmin(&minimum);

 if (maxi - minimum < 1e-31) // TODO: statt Konstanter 
   {
     for(int t = 0; t < size; t++)
       mArray[t] = static_cast<Type>(newmax);
     return;
   }
 scale = (Type) newmax / (maxi - minimum);
 cerr << size << endl;

 for(int t = 0;t < size; t++)
   mArray[t] =  static_cast<Type> ((mArray[t] - minimum ) * scale);

 return;
}

//////////////////////////////////////////////////////////////////////////////
/// \param newmax new maximum value
/// \todo: constant 1e31 should be avoided
/// \todo  if all values = 0 -> no change; all values the same -> all newmax  
/// \warning scaling greater than 100000 times is not performed !
/// \warning if maximum-minimum < 10^-31 (Array is constant) the value will be set to newmax for the whole Array
//////////////////////////////////////////////////////////////////////////////
template <class Type>
void Array<Type>::normHigh( double newmax)
{
 float scale;              /* scaling factor */
 int size = mSizeX * mSizeY;     
 Type maxi, minimum;
 maxi = maxmin(&minimum);

 if (maxi - minimum < 1e-31) // TODO: statt Konstanter 
   {
     for(int t = 0; t < size; t++)
       mArray[t] = static_cast<Type>(newmax);
     return;
   }

 minimum = 0;
 scale = (Type) newmax / (maxi - minimum);
 for(int t = 0;t < size; t++)
   mArray[t] =  static_cast<Type> ((mArray[t] - minimum ) * scale);
 return;
}

//////////////////////////////////////////////////////////////////////////////
/// \param maximum maximum value of the random data
//////////////////////////////////////////////////////////////////////////////
template <class Type>
void Array<Type>::random(Type maximum)
{
  double factor = static_cast<double>(maximum);

  for(int t=mSizeX*mSizeY-1; t >= 0; t--)
    *(mArray + t) = static_cast<Type>(((float) rand()) / RAND_MAX * factor);
}

//////////////////////////////////////////////////////////////////////////////
/// \param halfwidthx filter kernel width
/// \param halfwidthy filter kernel height
/// \warning border will not be processed
/// \todo: iir
/// \todo: more efficient memory management
//////////////////////////////////////////////////////////////////////////////
template <class Type>
void Array<Type>::smooth(int halfwidthx, int halfwidthy)
{
  int xe = mSizeX - halfwidthx -1;
  int ye = mSizeY - halfwidthy -1;

  Array<Type> erg(mSizeX, mSizeY);
  float faktor = 1.0 / ((2*halfwidthx +1) * (2*halfwidthy + 1));

  for(int y = halfwidthy; y < ye; y++)
    for(int x = halfwidthx; x < xe; x++)
      {
	double mean = 0;
	for(int y2=-halfwidthy; y2 <= halfwidthy; y2++)
	  for(int x2=-halfwidthx; x2 <= halfwidthx; x2++)
	     mean += _(x+x2,y+y2);
	erg._(x,y) = static_cast<Type> (mean * faktor);
      }

  for(int y = halfwidthy; y < ye; y++)
    for(int x = halfwidthx; x < xe; x++)
      _(x,y) = erg._(x,y);

  return; 
}


//////////////////////////////////////////////////////////////////////////////
/// \brief simple rectangular smoothing window
/// \param halfwidthx filter kernel width
/// \param halfwidthy filter kernel height
/// \warning border will not be processed
/// \todo: more efficient memory management
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::smoothFast(int halfwidthx, int halfwidthy)
{
  int xe = mSizeX - halfwidthx -1;
  int ye = mSizeY - halfwidthy -1;

  Array<Type> erg(mSizeX, mSizeY);
  float faktor = 1.0 / ((2*halfwidthx +1) * (2*halfwidthy + 1));

  // ---- Das ist der Hauptteil
  for(int y = halfwidthy; y < ye; y++)
    {
      int x = halfwidthx; 
      double mean = 0;
      for(int y2=-halfwidthy; y2 <= halfwidthy; y2++)
	for(int x2=-halfwidthx; x2 <= halfwidthx; x2++)
	  mean += _(x+x2,y+y2);

      for(int x = halfwidthx; x < xe; x++)
	{
	  // Alte Zeile abziehen
	  for(int y2=-halfwidthy; y2 <= halfwidthy; y2++)
	    {
	      mean -= _(x-halfwidthx,y+y2);
	      mean += _(x+halfwidthx+1,y+y2);
	    }
	  erg._(x,y) = static_cast<Type> (mean * faktor);
	}
    }

  for(int y = 0; y < ye; y++)
    for(int x = 0; x < xe; x++)
       _(x,y) = erg._(x,y);

  return;
}

//////////////////////////////////////////////////////////////////////////////
/// \param data2 = input. Every pixel that is > 0 is assumed  to be TRUE
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::logicalOr(Array<Type>& data2)
{
 if(mSizeX != data2.mSizeX)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 x", ERRORARRAY);
 if(mSizeY != data2.mSizeY)
   throw Error(__PRETTY_FUNCTION__, __LINE__,"Array Size 1 != Array Size 2 y", ERRORARRAY);

  for(int y=0; y < mSizeY; y++)
    for(int x=0; x < mSizeX; x++)
      if(_(x,y) > 0 || data2._(x,y) > 0)
	_(x,y) = 255;
      else
	_(x,y) = 0;

  return;
}

//////////////////////////////////////////////////////////////////////////////
/// \param n zoom factor, positive -> zoom in, negative -> zoom out
/// \exception bad_allox
/// \warning no deletion of the original object that data pointed to 
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
Array<Type>& Array<Type>::resize(int n)
{
  int sx = mSizeX;
  int sy = mSizeY;
  if(n > 0)			// Zoom in 
    {
      Array<Type>* d = new Array<Type>(sx*n,sy*n);

      for(int y=0; y < sy; y++)
	for(int x=0; x < sx; x++)
	  {
	    Type value = _(x,y);
	    for(int y2=0; y2 < n; y2++)
	      for(int x2=0; x2 < n; x2++)
		d->_(x*n+x2,y*n+y2) = value;
	  }
      return *d;
    }
  else				// Zoom out
    {
      Array<Type>* d = new Array<Type>(sx/n,sy/n);

      for(int y=0; y < sy/n; y++)
	for(int x=0; x < sx/n; x++)
	  d->_(x,y) = _(x*n,y*n);
      return *d;
    }

}

//////////////////////////////////////////////////////////////////////////////
/// \param threshold threshold value
/// \param value1 lower value
/// \param value2 higher value
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::
globalThreshold(Type threshold, Type value1, Type value2)
{
  for(int t = mSizeX * mSizeY-1; t>= 0; t--)
    if(operator[](t) < threshold)
      operator[](t) = value1;
    else
      operator[](t) = value2;
  return;
}

//////////////////////////////////////////////////////////////////////////////
/// \param data Image 
/// \param halfwidthx window widthX = halfwidthx * 2 +1
/// \param halfwidthy window widthY = halfwidthy * 2 +1
/// \exception bad_alloc
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::local(int halfwidthx, int halfwidthy)
{
  Array<Type> erg(mSizeX, mSizeY);
  int sizex = halfwidthx * 2 + 1;
  int sizey = halfwidthx * 2 + 1;

  for(int y=halfwidthy; y < mSizeY - halfwidthy -1; y++)
    for(int x=halfwidthx; x < mSizeX - halfwidthx -1; x++)
      {
	double sum = 0;
	for(int x2=-halfwidthx; x2 <= halfwidthx; x2++)
	  for(int y2=-halfwidthy; y2 <= halfwidthy; y2++)
	    sum += _(x+x2,y+y2);
	sum /= (sizex * sizey);

	if(_(x,y) > sum)
	  erg._(x, y) = 255;
	else
	  erg._(x, y) = 0;
      }
  
  for(int t = mSizeX * mSizeY - 1; t >= 0; t--)
    operator[](t) = erg[t];

  return;
}

//////////////////////////////////////////////////////////////////////////////
/// \param halfwidthx window widthX = halfwidthx * 2 +1
/// \param halfwidthy window widthY = halfwidthy * 2 +1
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::bernsen(int halfwidthx, int halfwidthy)
{
  Array<Type> erg(mSizeX, mSizeY);

  for(int y=halfwidthy; y < mSizeY - halfwidthy -1; y++)
    for(int x=halfwidthx; x < mSizeX - halfwidthx -1; x++)
      {
	Type maxi = 0;
	Type mini = _(0,0);

	for(int x2=-halfwidthx; x2 <= halfwidthx; x2++)
	  for(int y2=-halfwidthy; y2 <= halfwidthy; y2++)
	    {
	      if(_(x+x2,y+y2) > maxi)
		maxi = _(x+x2,y+y2);
	      if(_(x+x2,y+y2) < mini)
		mini = _(x+x2,y+y2);
	    }

	Type th = static_cast<Type> (((int) maxi - mini) / 2 + mini);

	if(_(x,y) > th)
	  erg._(x, y) = 255;
	else
	  erg._(x, y) = 0;
      }
  
  for(int t = mSizeX * mSizeY - 1; t >= 0; t--)
    operator[](t) = erg[t];

  return;
}

//////////////////////////////////////////////////////////////////////////////
/// \param threshold only use pixels larger than threshold
/// \param centerX result x position
/// \param centerY result y position
/// \todo only in local region
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::centerOfGravity(Type threshold, double* centerX, double* centerY)
{
  double count = 0;
  double resultx = 0;
  double resulty = 0;
  for(int y = 0; y < mSizeY; y++)
    for(int x = 0; x < mSizeX; x++)
      if(_(x,y) > threshold)
	{
	  count += (_(x,y)-threshold);
	  resultx += x* (_(x,y)-threshold);
	  resulty += y* (_(x,y)-threshold);
	}
  *centerX = resultx / count;
  *centerY = resulty / count;
}


//////////////////////////////////////////////////////////////////////////////
/// \param cx center circle position x
/// \param cy center circle position y
/// \param r radius of circle
/// \param value value to set in the circular area
/// \warning very uneffective for large Arrays
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
void Array<Type>::cutCircle(int cx, int cy, int r, Type value) ///< set circular area to value
{
  double r2 = r*r;
  for(int y=0; y < mSizeY; y++)
    for(int x=0; x < mSizeX; x++)
      if((x-cx)*(x-cx) + (y-cy)*(y-cy) < r2)
	_(x,y) = value;
}


//////////////////////////////////////////////////////////////////////////////
/// \return mean value
//////////////////////////////////////////////////////////////////////////////
template <class Type> 
double Array<Type>::mean()
{
  double mean = 0;
  for(int t= mSizeX * mSizeY -1; t >= 0; t--)
    mean += operator[](t);
  return mean/(mSizeX * mSizeY);
}


/*==================================================================*/
template class Array<float>;
template class Array<double>;
template class Array<unsigned char>;
template class Array<int>;
template class Array<short int>;
