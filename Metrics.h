#ifndef _METRICS_H_
#define _METRICS_H_

#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <limits>
#include <string.h>

class Metrics{
public:
      Metrics(std::vector< std::vector<double> > & iinten){
                dnbSkip_ = 1;
                fastQuantiles_ = 32000; 
                dnbSkipClusterMetrics_ = 1;
                bic = 0;
                fitScore = 0;
                intensityScalingQuantile_ = 0.99f;
                
                scaleFactors_.resize(BaseTypes);
                normCenters_.resize(BaseTypes);
                normFactors_.resize(BaseTypes);
                postScaleFactors.resize(BaseTypes); 
                
                postScaleFactors[BaseC] = 1.0f; 
                postScaleFactors[BaseT] = 1.0f; 
                postScaleFactors[BaseA] = 1.0f; 
                postScaleFactors[BaseG] = 1.0f;
                devPhi95.resize(BaseTypes); 
                intst = iinten;
                std::cout<<"Normalize Intensity..."<<std::endl; 
                normalizeIntensities(intst);
                std::cout<<"Scale Intensity..."<<std::endl;
                scaleIntensities(intst);                 
      }
      ~Metrics(){}
      
public:
       float getFS(){ calculateFitScore(); return this->fitScore; }
       float getBIC(){ calculateBasecallInformationContent(); return this->bic; }
       void setFS(float fitScore){ this->fitScore = fitScore; }
       void setBIC(float fitScore){ this->bic = bic; }
       void print(){ calculateFitScore(); calculateBasecallInformationContent(); std::cout<<"Fit Score:"<<fitScore<<std::endl; std::cout<<"Basecall Information Content:"<<bic<<std::endl;}
       void calculateBasecallInformationContent();
       void calculateFitScore();
       int call(std::vector< std::vector<double> > &, size_t);
       void scaleIntensities(std::vector< std::vector<double> > &);
       void normalizeIntensities(std::vector< std::vector<double> > &);
       void calculateScores(std::vector< std::vector<double> > &);
       
private:
      float fitScore; 
      float bic;
      int dnbSkip_;               
      size_t fastQuantiles_;
      int dnbSkipClusterMetrics_;  
      float intensityScalingQuantile_;                      
      std::vector<float> scaleFactors_;
      std::vector<float> normCenters_;
      std::vector<float> normFactors_;       
      std::vector<float> postScaleFactors;
      std::vector<float> devPhi95;
      std::vector<float> scores;
      std::vector< std::vector<double> > intst;
      
private:
        enum BaseType
        {
             BaseA = 0,    //< C = TxRed
             BaseT,        //< T = FITC
             BaseC,        //< A = Cy5
             BaseG,        //< G = Cy3
             BaseTypes,    //< Number of base types
             Base2Base = BaseTypes*(BaseTypes-1)/2
        };
      
public:
       template <class T> T zmf(T val, T left, T right)
       {
                T center = (left + right) / 2;
		        T width  = right-left;
		        if (width > 0 && val >left && val <= center)
			       return 1 - 2 * pow((val - left) / width, 2);
		        else if (width > 0 && val <= right && val > center)
			         return 2 * pow((val - right) / width, 2);
                else if (val > right)
			         return (T)0.0;
                else
			        return (T)1.0;
      } 
      template<class T> T log4(T x) 
      { 
                     return x == (T)0.0 
                     ?  (T)0.0 
                     :  log(x)/log((T)4.0); 
      }
      inline float   normalizedIntensity ( size_t color, float   intensity, float   postScaleFactor = 1.0 )
      {
             return intensity * postScaleFactor * scaleFactors_[color];
      }
      inline float originalIntensity ( size_t color, float   intensity, float   postScaleFactor = 1.0 )
      {
             return intensity * postScaleFactor * scaleFactors_[color] * normFactors_[color] + normCenters_[color];
      }        
};

namespace METRICS{
    template<class T> inline void  multiply ( T* dest, const T& value, size_t count )
    {
        for ( ; count; --count, ++dest ) *dest *= value;
    }
    template<class T> inline void  mresize( std::vector<T>& v, size_t size )
    {
        v.resize(size);
        if ( size ) memset( &v[0], 0, size*sizeof(T) );
    }
    template<class T> inline T*  begin( std::vector<T>& v )
    {
        T* out = new T[v.size()];
        size_t index = 0;
        for(; index < v.size(); index++ ){
              *(out + index) = v[index];                       
        }
        return out;
    }
      template<class T> inline T squared(  const T& x )
      {
             return x*x;
      } 
};

class NormalCDF
{
    public:
        NormalCDF();
        float cumulativeDensity(float x) const;

    protected:
        std::vector<float> cdf_;
        size_t numBuffered_;
        float bufferSpan_;
        static float cdft(float x, size_t maxPolynomial=100); 
};




template <class T> class Histogram
{
    protected:   

    size_t              total_; 
    size_t              size_;   
    std::vector<T>      bottom_; 
    std::vector<size_t> count_;  
    std::vector<size_t> sum_;    

    public:  

    Histogram() : total_(0), size_(0) {}

    Histogram( size_t nx, const T* x, size_t nbins, T xmin = (T)1, T xmax = (T)0 )
    {
        init ( nx, x, nbins, xmin, xmax );
    }

    void init ( const std::vector<T>& x, size_t nbins, T xmin = (T)1, T xmax = (T)0 )
    {
		init ( x.size(), (x.size() ? &x[0] : NULL), nbins, xmin, xmax );
    }
    
    void init ( size_t nx, const T* x, size_t nbins, T xmin = (T)1, T xmax = (T)0 )
    {
        if ( !nx )
        {
            size_ = 0;
            return;
        }

        if ( xmin >= xmax )
        {
            xmin = xmax = *x;
            const T* px = x+1;
            for ( size_t i = nx-1; i; --i, ++px )
            {
                if      ( xmin > *px ) xmin = *px;
                else if ( xmax < *px ) xmax = *px;
            }
        }

        total_ = nx;
        size_  = nbins;

        METRICS::mresize( bottom_, size_+1 );
        METRICS::mresize( count_ , size_   );
        METRICS::mresize( sum_   , size_+1 );

        size_t  maxbin = nbins-1;
        T       delta  = ((T)(xmax-xmin))/nbins,
                bottom = xmin,
               *pb     = &bottom_[0];

        for ( size_t bin = 0; bin < size_; ++pb, ++bin )
        {
            *pb    = bottom;
            bottom = xmin + delta*(T)bin;
        }
        *pb = xmax;


        for ( size_t bin = 0; nx; ++x, --nx )
        {
            bin = (size_t)(((*x)-xmin)/delta);
            if      ( bin > maxbin ) bin = maxbin;
            else if ( bin < 0      ) bin = 0;
            (count_[bin])++;
        }

        for ( size_t b = size_, *pc = &count_[0], *ps = &sum_[0], sum = 0; b; --b, ++pc, ++ps )
        {
            *ps  = sum;
            sum += *pc;
        }
        sum_[size_] = total_;
    }

    void quantiles ( size_t n, const double* q, T* result )
    {
        for ( ; n; --n, ++q, ++result )
        {
            *result = quantile(*q);
        }
    }

    void quantiles ( size_t n, const float* q, T* result )
    {
        for ( ; n; --n, ++q, ++result )
        {
            *result = quantile((double)(*q));
        }
    }

    void quantiles ( const std::vector<double>& q, std::vector<T>& result )
    {
        result.resize(q.size());
        quantiles( q.size(), &q[0], &result[0] );
    }

    void quantiles ( const std::vector<float>& q, std::vector<T>& result )
    {
        result.resize(q.size());
        quantiles( q.size(), &q[0], &result[0] );
    }

    T quantile ( double q, size_t* bin = NULL ) const
    {
       if ( !size_ ) return (T)0;
       size_t   s     = (size_t)(q*total_),
                left  = 0,
                right = size_,
                mid   = 0;

        while ( left < right )
        {
            if ( s >= sum_[mid=(left+right)/2]  )
            {
                if ( left == mid ) break;
                left=mid;
            }
            else
            {
                right = mid;
            }
        }

        if ( bin ) *bin = right;
        return bottom_[right];
    }

    T trimmean ( const T& trimLeft, const T& trimRight  ) const
    {
        if ( !size_ ) return (T)0;

        if ( trimLeft + trimRight >= (T)1.0 )
        {
            return quantile((T)0.5);
        }

        size_t bLeft  = 0,
               bRight = 0;
        T      vLeft  = quantile(trimLeft,  &bLeft );
        quantile((T)1.0-trimRight, &bRight);

        if ( bLeft >= bRight )
        {
            return vLeft;
        }

        if ( bRight >= size_ ) bRight = size_-1;

        size_t count  = 0;
        T      result = (T)0.0;

        for ( size_t b = bLeft; b <= bRight; b++ )
        {
            result += bottom_[b]*count_[b];
            count  += count_[b];
        }

        if ( count > 0 ) result /= (T)count;

        return result;
    }

};


#endif

