/*
 * @kangkang,DNB或者Cluster重构定位 
 */
 #ifndef _CD_RECONSTRUCT_H_
 #define _CD_RECONSTRUCT_H_
 
 #include <vector>
 #include "squareFit.h"
 #include "image.h"
 #include "regression.h"
 
 class CDReconstruct{
 public:
        CDReconstruct(){                          
        }
        ~CDReconstruct(){                          
        } 
 public:
        void fit(std::vector< std::pair<float, float> > &, image&); 
        void fit2(std::vector< std::pair<float, float> > &, image&);         
 private:
         const static short gsize = 3;//////////////////////////////////////////
 };
 #endif
