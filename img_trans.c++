#include <iostream>
#include <vector>
#include "image.hpp"
using namespace std;
typedef unsigned char uchar;

double max(vector<double> sigma){
    double Max = 0;
    int check;
    for(int i = 0 ; i < 256; i++){
        if(Max < sigma[i]){
            Max = sigma[i];
            check = i;
        }
    }
    return check;
}

int main(void){
    Image sample("sample.png");
    Image gray_sample(sample.w,sample.h,1);
    Image otu_sample(sample.w,sample.h,1);

    double m_average=0;
    for(int y = 0; y < sample.h; y++){
        for(int x = 0; x < sample.w; x++){
            uchar v = (sample.GetPixel(y,x,0)+sample.GetPixel(y,x,1)+sample.GetPixel(y,x,2))/3;
            gray_sample.SetPixel(y,x,0,v);
            m_average += v;
        }
    }
    m_average /= sample.w*sample.h;
    vector<double> sigma(256,0);

    for(int i = 0; i < 255; i++){
        double m_b = 0;
        double m_w = 0;
        double m_b_pixel = 0;
        double m_w_pixel = 0;
        for(int y = 0; y < sample.h; y++){
            for(int x = 0; x < sample.w; x++){
                uchar a = sample.GetPixel(y,x,0);
                if(a > i){
                    m_b_pixel++;
                    m_b += a;
                }else{
                    m_w_pixel++;
                    m_w += a;
                }
            }
        }
        m_b /= m_b_pixel;
        m_w /= m_w_pixel;
        sigma[i] = (m_b_pixel*(m_b - m_average)*(m_b - m_average)+m_w_pixel*(m_w - m_average)*(m_w - m_average))/(m_b_pixel+m_w_pixel);
    }
    double t = max(sigma);

    for(int y = 0; y < sample.h; y++){
        for(int x = 0; x < sample.w; x++){
            uchar l = gray_sample.GetPixel(y,x,0);
            if(l > t) l = 255;
            if(l < t) l = 0;
            otu_sample.SetPixel(y,x,0,l);
        }
    }
    cout << t;
    otu_sample.save("otu.png");

    return 0;
}