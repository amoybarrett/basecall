#include "Metrics.h"

#ifndef M_PI
#define M_PI 3.14159265358979
#endif
////////////////////////////////////////////////////////////////////////////////
NormalCDF::NormalCDF()
{
    numBuffered_ = 801; 
    bufferSpan_ = (float)(numBuffered_-1);
    cdf_.resize(numBuffered_); 
    for ( size_t i=0; i<numBuffered_; ++i )
    {
        cdf_[i] = NormalCDF::cdft(((float)i)/bufferSpan_*8.0f - 4.0f, 100);
    }
}

float NormalCDF::cumulativeDensity(float x) const
{
    if ( x < -4.0f ) return 0.0f;
    if ( x >  4.0f ) return 1.0f;
    size_t i = (size_t)((x+4.0f)/8.0f*bufferSpan_);
    return cdf_[i];
}

float NormalCDF::cdft(float x, size_t maxPolynomial)
{
    double s = (double)x;
    double b = s;
    double q = s*s;
    double ii = 1.0;
    for ( size_t i=3; i<maxPolynomial; i+=2 )
    {
        b = b*q;
        ii = ii*(double)i;
        s = s + b/ii;
    }
    return (float)(0.5 + s*1.0/sqrt(2.0*3.14159265358979)*exp(-0.5*q));
}
////////////////////////////////////////////////////////////////////////////////

void  Metrics::calculateScores(std::vector< std::vector<double> > &intensities_)
{  
    size_t NDnb_ = intensities_[0].size(); 
    std::vector<float>   yMax1 (NDnb_);
    std::vector<float>   yMax12(NDnb_);
    std::vector<float>   yMax12good(NDnb_);
    
    size_t good = 0;
    
    const float very_negative = -std::numeric_limits<float>::max(),
                eps           =  std::numeric_limits<float>::epsilon();
    for (size_t idnb = 0; idnb < NDnb_; ++idnb) 
    {   
        int c = call(intensities_, idnb);
        if ( c < 0 || c > 3 )
        {
            yMax1 [idnb] = 0.0f;
            yMax12[idnb] = 1.0f;
            continue;
        }
        float max1 = 0.0f;
        float yMax2 = very_negative;
        for ( int i=0;  i<BaseTypes; ++i)
        {
            float y = intensities_[i][idnb];
            if ( i == c ) { max1 = y; }
            else          { if ( yMax2 < y ) yMax2 = y; }
        }
        yMax1[idnb]     = max1;
        float tm = max1/(yMax2+eps) > 0 ? max1/(yMax2+eps) : 0 - max1/(yMax2+eps);
        yMax2            = tm > 1.0 ? tm : 1.0; 
        yMax12[idnb]    = yMax2;        
        yMax12good[good] = yMax2; 
        ++good;
    }

    yMax12good.resize(good);

    size_t pct_element = yMax12good.size()/10;
    nth_element(yMax12good.begin(), yMax12good.begin()+pct_element, yMax12good.end());
    float yMax12pct = yMax12good[pct_element];

    float field_log_odds_ratio = 0.0f;

   
    {
        if ( yMax12pct > 5.0f )
        {
            yMax12pct = 5.0f;
        }
        field_log_odds_ratio = (-0.1170642f) + 2.1515030f*yMax12pct + (-0.2127391f)*(yMax12pct*yMax12pct);
    }
    scores.resize(NDnb_);
    static const NormalCDF normCDF_;

    {
        for ( size_t idnb = 0; idnb < NDnb_; ++idnb )
        {
            float y1  = yMax1[idnb],
                 y12_log = log10(yMax12[idnb]);
            float yMax1_t = 0.85f*normCDF_.cumulativeDensity((y1-0.16f)/0.11f) + 0.15f*normCDF_.cumulativeDensity((y1-0.55f)/0.30f);
            float yMax12_t = 0.97f*normCDF_.cumulativeDensity((y12_log+0.01f)/0.40f) + 0.03f*normCDF_.cumulativeDensity((y12_log-0.95f)/0.70f);
            float link = (-6.07433297873612f) + 3.68687665581271f*yMax1_t + 6.61663992294833f*yMax12_t + 0.383204046138289f*field_log_odds_ratio;
            scores[idnb] = (1.0f/(1.0f+exp(-link)));
        }
    }

}

void Metrics::calculateBasecallInformationContent(){
    std::cout<<"Calculate Basecall Information Content..."<<std::endl; /////////////////////////////// 
    calculateScores(intst);
    size_t NDnb_ = intst[0].size(); 
    size_t nNotPad = 0;
    double informationContent = 0.0;
for ( size_t idnb = 0; idnb < NDnb_; idnb += dnbSkipClusterMetrics_)
{
        int c = call(intst, idnb);
        if ( c < 0 || c > 3 )
        {
            continue;
        }
        ++nNotPad;

		float bp = scores[idnb]; 
		float nbp = (1.0f - bp)/3.0f;
		// log base 4 of x == log4(x) = log(x)/log(4) = log(x)*log(1/4) = log(x)*log(0.25)
		// information content is defined as 1-information entropy and information entropy is sum of -p*log(p) over all 4 probabilities
		// => information content for a base = bi = 1 - (-bp*log4(bp) - nbp*log4(nbp) - nbp*log4(nbp) - nbp*log4(nbp)) = 1 + bp*log4(bp) + 3*nbp*log4(nbp)
		float bi = 1 + bp*log4(bp) + 3.0f*nbp*log4(nbp);
		informationContent += bi;
}		

	informationContent = (float)informationContent*dnbSkipClusterMetrics_;
	if (NDnb_ > 0) bic = (float)(100.0 * informationContent / nNotPad);
                        
}

void Metrics::scaleIntensities(std::vector< std::vector<double> > &intensity_)
{
    size_t NDnb_ = intensity_[0].size(); 
    double qnt = (double)intensityScalingQuantile_;
    Histogram<double> hist;
    for ( int color = 0; color < BaseTypes; color++ ) 
    {
        hist.init (intensity_[color], fastQuantiles_ );
        float q      = hist.quantile(qnt);
        double scale  = (q != 0.0f) ? 1.0f/q : 0.0f;     
        scaleFactors_[color] = q;
        METRICS::multiply( &intensity_[color][0], scale, NDnb_ );
    }
    
}

void Metrics::normalizeIntensities(std::vector< std::vector<double> > &intensity_)
{
    size_t NDnb_ = intensity_[0].size(); 
    float   zero          = 0.0f,
            qNrm          = 0.0f;          
    double qnt = intensityScalingQuantile_,
           med = 0.5 ;
    float initialScale = 0.0;
    Histogram<double> hist;
    for ( int color = 0; color < BaseTypes; color++ ) 
    {
        hist.init (intensity_[color], fastQuantiles_);
        zero = (float)hist.quantile(med);
        qNrm = (float)hist.quantile(qnt);

        if ( initialScale < qNrm ) initialScale = qNrm;

        float scale = qNrm-zero;       
        normCenters_[color] = zero;
        normFactors_[color] = scale;
        if (scale != 0.f) scale = 1.0f/scale;
        
        std::cout<<scale<<std::endl;
        
        long long counter = 0;
        for ( size_t count = NDnb_; count; --count, ++counter ) intensity_[color][counter] = (intensity_[color][counter]-zero)*scale;
    }
}

int Metrics::call(std::vector< std::vector<double> > &inten, size_t t){
    float tm = -1e10;
    int out;
    for(int i = 0; i < inten.size(); i++){
            if(inten[i][t] > tm){tm = inten[i][t]; out = i;}                   
    }    
    return out;
}

void Metrics::calculateFitScore(){
std::cout<<"Calculate Fit Score..."<<std::endl;  
size_t NDnb_ = intst[0].size();      
Histogram<float> hist;
std::vector<float>   rho[BaseTypes],
        psi[BaseTypes],
        phi[BaseTypes];
for ( int c = 0; c < BaseTypes; c++ )
{
        rho[c].reserve(NDnb_/dnbSkip_+1);
        phi[c].reserve(NDnb_/dnbSkip_+1);
        psi[c].reserve(NDnb_/dnbSkip_+1);
}

for ( size_t idnb = 0, skip = (dnbSkip_>1); idnb < NDnb_; ++idnb)
{
       int cval = call(intst, idnb);
       if ( cval < 0 || cval > 3){continue;}  
       if ( skip &&  idnb%dnbSkip_ ) continue;     
       float  intensity =  intst[cval][idnb],
               normRho   = normalizedIntensity(cval,intensity,postScaleFactors[cval]),
               origRho   = originalIntensity  (cval,intensity,postScaleFactors[cval]);

        rho[cval].push_back( origRho );
        
        float   normPhi = 0;
        for ( int c = 0, ucall = cval; c < BaseTypes; c++ )
        {
            if ( c == ucall ) continue;
            normPhi += METRICS::squared( normalizedIntensity(c,intst[c][idnb],postScaleFactors[c]) );
        }

        normPhi = ( normRho > 0.0f ) ? (float)sqrt(normPhi)/normRho : 0.0f;
        phi[cval].push_back( (float)(atan(normPhi)*(180.0/M_PI)) );
}

for ( size_t c = 0; c < BaseTypes; c++ )
{
        if ( !rho[c].size() ) continue;

        float   rho_mean = 0.0f;
        
        float* p = METRICS::begin(rho[c]);
        hist.init( rho[c].size(), p, fastQuantiles_ );
        rho_mean  = hist.trimmean( 0.1f, 0.1f );
        delete[] p;

        hist.init( phi[c], fastQuantiles_ );

        for ( size_t i = 0, s = phi[c].size(); i < s; i++ )
        {
            if ( rho[c][i] > rho_mean )
            {
                psi[c].push_back( phi[c][i] );
            }
        }

        if ( !psi[c].size() ) continue;

        hist.init( psi[c], fastQuantiles_ );
        devPhi95[c] = hist.quantile(0.95f);
}
float tm = -1e10;
for(std::vector<float>::iterator it = devPhi95.begin(); it != devPhi95.end(); it++){
     if(*it > tm) tm = *it;                                                           
}
float   phiMax = tm;
fitScore = (float)zmf<double>((double)phiMax, 0, 70);
}

int main(void){
    std::vector< std::vector<double> > intensity;
    
    std::vector<double> temp;
    temp.push_back(5000);
    temp.push_back(2000);
    temp.push_back(3000);
    temp.push_back(4000);
    temp.push_back(5000);
    intensity.push_back(temp);
    temp.clear();
    temp.push_back(5000);
    temp.push_back(4000);
    temp.push_back(3000);
    temp.push_back(2000);
    temp.push_back(1000);
    intensity.push_back(temp);
    temp.clear();
    temp.push_back(3000);
    temp.push_back(5000);
    temp.push_back(6000);
    temp.push_back(3000);
    temp.push_back(2000);
    intensity.push_back(temp);
    temp.clear();
    temp.push_back(2000);
    temp.push_back(1000);
    temp.push_back(1000);
    temp.push_back(6000);
    temp.push_back(1000);
    intensity.push_back(temp);
    
    Metrics mt(intensity);
    mt.print();
    system("pause");
    
    return 0;    
}


