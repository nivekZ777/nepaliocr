#pragma once

using namespace System::Drawing;

public __gc class ThresholedValue
{
private:
	static int num_bins=256; 
	int xsize;
	int ysize;
	float *counts;
    float sum_counts;
    float *p;
    float *omega;
    float *mu;
    float mu_t;
	

	Bitmap* ImageFile;
	
	void ImHist();

public:
	ThresholedValue(System::Drawing::Bitmap*);

	float GetThresholed();
	void calculateValue();
};
