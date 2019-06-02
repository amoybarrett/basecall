#include "StdAfx.h"
#include "calculateScore.h"

void calculateScore::calculate2(std::vector< std::vector<float>* > &inten, std::vector< char > &bases, std::vector< char >&oscore){
	//oscore.resize(bases.size(), 'N');

	for(unsigned long j = 0; j < (*inten[0]).size(); j++){
		double pro = 0;
		switch(bases[j]){
			case('A'):
				pro += (*inten[1])[j];
				pro += (*inten[2])[j];
				pro += (*inten[3])[j];
				break;
			case('C'):
				pro += (*inten[0])[j];
				pro += (*inten[2])[j];
				pro += (*inten[3])[j];
				break;
			case('G'):
				pro += (*inten[0])[j];
				pro += (*inten[1])[j];
				pro += (*inten[3])[j];
				break;
			case('T'):
				pro += (*inten[0])[j];
				pro += (*inten[1])[j];
				pro += (*inten[2])[j];
				break;
			default:
				pro = 1;
		}

		if(pro > 1)
			pro = 1;
		else if(pro <= 7.9e-5)
			pro = 7.9e-5;

		oscore.push_back(phred(pro));
	}

}

void calculateScore::calculate(std::vector< std::vector<float>* > &intensity,  std::vector< char > &bases, std::vector< char >&oscore)
{
	std::vector< std::vector<float> > noise;
	for(int i = 0; i < intensity.size(); i++){
		std::vector<float> temp;
		for(unsigned long j = 0; j < (*intensity[i]).size(); j++){
			int jb = j > window ? j - window : 0;
			int je = j + window < (*intensity[i]).size() ? j + window : (*intensity[i]).size() - 1;
			float min = 1e30;
			for(unsigned long k = jb; k <= je; k++){
				if(min > (*intensity[i])[k])	min = (*intensity[i])[k];
			}
			temp.push_back(min);
		}
		noise.push_back(temp);
	}

	std::vector<float> mean(noise.size(), 0);
	for(int i = 0; i < noise.size(); i++){
		for(unsigned long j = 0; j < noise[i].size(); j++){
			mean[i] += noise[i][j];
		}
		mean[i] /= noise[i].size();
	}

	cv::Mat cov = cv::Mat::zeros(noise.size(), noise.size(), CV_64F);
	for(int i = 0; i < noise.size(); i++){
		for(int j = 0; j < noise.size(); j++){
			for(unsigned long k = 0; k < noise[0].size(); k++){
				cov.at<double>(i,j) += (noise[i][k] - mean[i]) * (noise[j][k] - mean[j]);
			}
			cov.at<double>(i,j) /= noise[0].size();
		}
	}
	cv::Mat D = cholesky(cov);
	cv::Mat DT = D.t();//cov = DT * D;
	cv::Mat DV = D.inv();

	float temp[] = {0, 0, 0, 0};

	float an1[] ={1/(std::sqrt(2.0)), -1/(std::sqrt(2.0)), 0, 0};
	float an2[] ={1/(std::sqrt(2.0)), 0, -1/(std::sqrt(2.0)), 0};
	float an3[] ={1/(std::sqrt(2.0)), 0, 0, -1/(std::sqrt(2.0))};

	float cn1[] ={-1/(std::sqrt(2.0)), 1/(std::sqrt(2.0)), 0, 0};
	float cn2[] ={0, 1/(std::sqrt(2.0)), -1/(std::sqrt(2.0)), 0};
	float cn3[] ={0, 1/(std::sqrt(2.0)), 0, -1/(std::sqrt(2.0))};

	float gn1[] ={-1/(std::sqrt(2.0)), 0, 1/(std::sqrt(2.0)), 0};
	float gn2[] ={0, -1/(std::sqrt(2.0)), 1/(std::sqrt(2.0)), 0};
	float gn3[] ={0, 0, 1/(std::sqrt(2.0)), -1/(std::sqrt(2.0))};

	float tn1[] ={-1/(std::sqrt(2.0)), 0, 0, 1/(std::sqrt(2.0))};
	float tn2[] ={0, -1/(std::sqrt(2.0)), 0, 1/(std::sqrt(2.0))};
	float tn3[] ={0, 0, -1/(std::sqrt(2.0)), 1/(std::sqrt(2.0))};

	float dvec[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

	float factor = 0.5;//default:0.5///////////////////////////////////////////////////
	float scale = 1 / sqrt(3.0);//default:1 / sqrt(2.0)////////////////////////////////

	double pro = 0;


	for(unsigned long j = 0; j < (*intensity[0]).size(); j++){

		for(int i = 0; i < intensity.size(); i++)
			temp[i] = (*intensity[i])[j];

		dvec[0][0] = jdz(temp, an1, intensity.size()) / tfs(DT, an1);
		dvec[0][1] = jdz(temp, an2, intensity.size()) / tfs(DT, an2);
		dvec[0][2] = jdz(temp, an3, intensity.size()) / tfs(DT, an3);
		dvec[1][0] = jdz(temp, cn1, intensity.size()) / tfs(DT, cn1);
		dvec[1][1] = jdz(temp, cn2, intensity.size()) / tfs(DT, cn2);
		dvec[1][2] = jdz(temp, cn3, intensity.size()) / tfs(DT, cn3);
		dvec[2][0] = jdz(temp, gn1, intensity.size()) / tfs(DT, gn1);
		dvec[2][1] = jdz(temp, gn2, intensity.size()) / tfs(DT, gn2);
		dvec[2][2] = jdz(temp, gn3, intensity.size()) / tfs(DT, gn3);
		dvec[3][0] = jdz(temp, tn1, intensity.size()) / tfs(DT, tn1);
		dvec[3][1] = jdz(temp, tn2, intensity.size()) / tfs(DT, tn2);
		dvec[3][2] = jdz(temp, tn3, intensity.size()) / tfs(DT, tn3);

		switch(bases[j]){
			case('A'):
				pro += (factor - factor * boost::math::erf(mo(dvec[1], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[2], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[3], 3) * scale));
				break;
			case('C'):
				pro += (factor - factor * boost::math::erf(mo(dvec[0], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[2], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[3], 3) * scale));
				break;
			case('G'):
				pro += (factor - factor * boost::math::erf(mo(dvec[1], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[0], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[3], 3) * scale));
				break;
			case('T'):
				pro += (factor - factor * boost::math::erf(mo(dvec[1], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[2], 3) * scale));
				pro += (factor - factor * boost::math::erf(mo(dvec[0], 3) * scale));
				break;
			default:
				pro = 1;
		}

		/////////////////////////////////////////////////////
		if(pro <= 0.001 && pro != 0){
			pro = -3.0 / ((std::log(pro) / log(10.0)) * 1000);
		}
		/////////////////////////////////////////////////////

		if(pro > 1)
			pro = 1;
		else if(pro <= 7.9e-5)
			pro = 7.9e-5;

		oscore.push_back(phred(pro));
	}

}
