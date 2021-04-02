#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

#define endl '\n'

using namespace std;

vector<double> operator - (vector<double> l, const vector<double>& r ){
  if(l.size()!=r.size())
    return{};
  for(int i=0; i<l.size(); ++i)
    l[i]-=r[i];
  return l;
}

vector<double> operator * (double l, vector<double> r ){
  for(int i=0; i<r.size(); ++i)
    r[i]*=l;
  return r;
}

vector<double> operator * (vector<double> l,const vector<double>& r ){
  for(int i=0; i<r.size(); ++i)
    l[i]*=r[i];
  return l;
}

double sum(vector<double> l){
  double res=0;
  for(double i:l )
    res+=i;
  return res;
}

vector<double> gaus(vector<vector<double>> syst){
  if(syst.size() != (syst[0].size()-1))
    return{};
  vector<double> ans(syst.size());
  for(int i=0; i<syst.size(); ++i){
    for(int j=i+1; j<syst.size(); ++j)
      syst[j]=syst[j]-(syst[j][i]/syst[i][i])*syst[i];
  }

  for(int i=syst.size()-1; i>=0; --i){
    double sum=0;
    for(int j=syst.size()-1; j>i; --j)
      sum+=ans[j]*syst[i][j];
    ans[i]=(syst[i].back()-sum)/syst[i][i];
  }
  return ans;
}


vector<double> mnk(const vector<vector<double>>& p, int step){
  
  const int mnk_step=step+1;
  vector<double> x_pow(p.size(), 1), x(p.size()), y(p.size());
  
  for(int i=0; i<p.size(); ++i){
    x[i]=p[i][0];
    y[i]=p[i][1];
  }
  
  vector<vector<double>> syst(mnk_step, vector<double>(mnk_step+1));
  
  for(int i=0; i<(2*mnk_step-1); ++i){
    double s=sum(x_pow);
    
    if(i<mnk_step)
      syst[i].back() = sum(x_pow*y);
    
    for(int j=0; j<=i; ++j)
      if(j<mnk_step && i-j<mnk_step)
        syst[j][i-j]=s;
    
    x_pow=x_pow*x;
   
  }
  return gaus(syst);
}

void print_points( vector<vector<double>> points){
  int width = 12;
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<points.size(); ++i)
    cout<<line<<'+';
  cout<<endl;
  
  cout<<setw(width)<<"X"<<'|';
  for(int i=0; i<points.size(); ++i)
    cout<<setw(width)<<points[i][0]<<'|';
  cout<<endl;
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<points.size(); ++i)
    cout<<line<<'+';
  cout<<endl;
  
  cout<<setw(width)<<"Y"<<'|';
  for(int i=0; i<points.size(); ++i)
    cout<<setw(width)<<points[i][1]<<'|';
  cout<<endl;
  
  cout<<setw(width)<<line<<'+';
  for(int i=0; i<points.size(); ++i)
    cout<<line<<'+';
  cout<<endl;
  
}

double polynom_at(const vector<double>& pol, double x0){
  double pow=1, res=0;
  for(int i=0; i<pol.size(); ++i){
    res+=pow*pol[i];
    pow*=x0;
  }
  return res;
}

double newazka(vector<double> pol, const vector<vector<double>>& points ){
  double res=0.0;
  for(const vector<double>& p : points)
    res+=pow((p[1] - polynom_at(pol, p[0])), 2.0);
  return res;
}

void print_pol(vector<double> pol){
  for(int i=0; i<pol.size(); ++i)
    cout<<((i>0 && pol[i]>=0)? '+'+to_string(pol[i]): to_string(pol[i])) <<" * x^"<<i<<' ';
  return;
}

int main(){
  // vector<vector<double>> points1{
  //   {-2, 3},
  //   {-1, 4},
  //   { 0, 2},
  //   { 1, 1},
  //   { 2, 1}};

  // vector<vector<double>> points2{
  //   { 1, 7},
  //   { 2, 7},
  //   { 3, 6},
  //   { 4, 7},
  //   { 5, 6},
  //   { 6, 5},
  //   { 7, 4},
  //   { 8, 4},
  //   { 9, 4},
  //   {10, 3}};
  
  vector<vector<double>> points{
    {-2,-4},
    {-1, 0},
    { 1, -2},
    { 3, -16}};

  print_points(points);
  vector<double> pol = mnk(points, 2); 
  cout<<"P2(x) = ";
  print_pol(pol);
  cout<<endl;
  cout<<"Newazka = "<<newazka(pol, points)<<endl;
  cout<<endl;
  
  print_points(points);
  pol = mnk(points, 1);
  cout<<"P1(x) = ";
  print_pol(pol);
  cout<<endl;
  cout<<"Newazka = "<<newazka(pol, points)<<endl;
  return 0;
}