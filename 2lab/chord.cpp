#include <string>
#include <iostream>  //  ________  ___  ___  ________  ________  ________      ________  ________  ________      |
#include <vector>    // |\   ____\|\  \|\  \|\   __  \|\   __  \|\   ___ \    |\   ____\|\   __  \|\   __  \     |
#include <iomanip>   // \ \  \___|\ \  \\\  \ \  \|\  \ \  \|\  \ \  \_|\ \   \ \  \___|\ \  \|\  \ \  \|\  \    |
#include <cmath>     //  \ \  \    \ \   __  \ \  \\\  \ \   _  _\ \  \ \\ \   \ \  \    \ \   ____\ \   ____\   |
#include <stdexcept> //   \ \  \____\ \  \ \  \ \  \\\  \ \  \\  \\ \  \_\\ \ __\ \  \____\ \  \___|\ \  \___|   |
using namespace std; //    \ \_______\ \__\ \__\ \_______\ \__\\ _\\ \_______\\__\ \_______\ \__\    \ \__\      |
#define endl '\n'    //     \|_______|\|__|\|__|\|_______|\|__|\|__|\|_______\|__|\|_______|\|__|     \|__|      |

const double eps = 0.01;                            //точность решения - наш эпсилон

double chord(auto f, double a,double b, int n){//функция f(x) границы отрезка [а, b] и максимальное число итераций
  if(f(a)*f(b)>=0)                          //проверка, что зачение функции на концах отрезка разные
    throw invalid_argument("f(a)*f(b)>=0"); //чтобы быть точно уверенными, что решение есть

  double c, cn=a;                           //точки пересечения хордой оси на текущей и предыдущей итерации
  int width = 12;                           //ширина столбца таблицы
  cout<<setprecision(width-4)<<fixed;       //количество знаков после запятой
  string line(width, '-');                  //нижняя линия ячейки таблицы
                                            //печать заголовка таблицы
  cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;
  cout<<setw(3)<<"i"<<'|'
  <<setw(width)<<"a"<<'|'<<setw(width)<<"c"<<'|'<<setw(width)<<"b"<<'|'
  <<setw(width)<<"f(a)"<<'|'<<setw(width)<<"f(c)"<<'|'<<setw(width)<<"f(b)"<<'|'<<endl;
  cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;

  for(int i=0; i<n; ++i){             //начало итераций
    c=(a*f(b)-b*f(a))/(f(b)-f(a));    //нахождения точки пересечения прямой, проходящей через (а, f(a)) и (b, f(b))
    
    //печать очередной строки таблицы
    cout<<setw(3)<<i+1<<'|'
      <<setw(width)<<a<<'|'<<setw(width)<<c<<'|'<<setw(width)<<b<<'|'
      <<setw(width)<<f(a)<<'|'<<setw(width)<<f(c)<<'|'<<setw(width)<<f(b)<<'|'<<endl;
    cout<<"---+"
      <<line<<'+'<<line<<'+'<<line<<'+'
      <<line<<'+'<<line<<'+'<<line<<'+'<<endl;
    
    if(abs(c-cn)<eps && abs(f(c))<eps ){ //проверка окончания итерационного процесса
      break;                             // что шаги уже достаточно маленькие и функция в текущей точке близка к нулю
    }  
                            // выбор отрезка
    if(f(a)*f(c)<0)         // выбираем левый отрезок [а, с]
      b=c;
    else if(f(b)*f(c)<0)    //выбираем правый [c, b]
      a=c;
    else 
      break;                //попали в ноль, т.е. f(c) = 0
    
    
    cn=c;                   //запоминаем текущую точку
  }

  
  return c;
}

int main(){
  auto f=[](double x) -> double{ return 0.5*x*x*x  + 5*x  + 16; } ;         //задаём функцию 0.5x^3 + 5x + 16
  try{
    cout<<setprecision(9);
    double ans = chord(f, -3, -2, 20);             // ищем рещение f(x)=0 на отрезке [-3, -2], делая не более 20ти итераций
    cout<<"ans    = "<<ans<<endl
        <<"f(ans) = "<<f(ans)<<endl
        <<"epsilon= "<<eps  <<endl;
  }
  catch(const logic_error& e){
    cout<<"Error : "<<e.what()<<endl;
  }
  return 0;
}
