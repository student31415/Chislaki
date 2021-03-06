#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <algorithm>
#define endl '\n'

using namespace std;       
//интегрирование по формуле симпсона h/3*( f(l) + 4*sum_{i=1,3,5..}f(xi) + 2*sum_{i=2,4,6..}f(xi) + f(b)))
double int_simpson(auto f, double l, double r, int n){
  double h = (r-l)/double(n), res=0;
  int width = 12;                           //ширина столбца таблицы
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');                  //нижняя линия ячейки таблицы

  
  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(width)<<'X'<<'|'<<setw(width)<<'Y'<<'|'<<endl;
  cout<<line<<'+'<<line<<'+'<<endl;
  for(int i=0; i<=n; ++i){
    if(i==0 || i==n)
      res+=h/3.0*f(l+double(i)*h);
    else
      if(i%2==1)
        res+=h*4.0/3.0*f(l+double(i)*h);
      else
        res+=h*2.0/3.0*f(l+double(i)*h);
    cout<<setw(width)<<l+double(i)*h<<'|'<<setw(width)<<f(l+double(i)*h)<<'|'<<endl;
  }
  cout<<line<<'+'<<line<<'+'<<endl;
  cout<<"h = "<<h<<endl;
  return res;
}

//уточнение по формуле Рунге-Ромберга r = r1 + (r1-r2)/((h2/h1)^p -1)
double Runge_Romberg(pair<double, double> r1, pair<double, double>r2, int p){
  return r1.first + (r1.first - r2.first)/(pow(r2.second/r1.second, double(p))-1);
}


int main(){
  //auto f= [](double x){ return sin(x);};
  //double l=0, r=M_PI/2, h1=M_PI/8, h2 = M_PI/16;
  //началные условия
  auto f= [](double x){ return (-2*x+1)/(x*x+9);};
  double l=-4, r=0, h1=1.0, h2=0.5;
  double res1, res2, res3;
  
  res1 = int_simpson(f, l, r,(r-l)/h1);
  cout<<"ans = "<<res1<<endl;
  
  res2 = int_simpson(f, l, r,(r-l)/h2);
  cout<<"ans = "<<res2<<endl;
  res3=Runge_Romberg({res1, h1}, {res2, h2}, 4);
  cout<<"R-R ans = "<<res3<<endl;
  return 0;
}