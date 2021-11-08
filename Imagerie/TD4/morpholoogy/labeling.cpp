#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int
_find(int p, int* roots)
{
  while(roots[p] != p)
    p = roots[p];
  return p;
}

int
_union(int r0, int r1, int* roots)
{
  if(r0 == r1) return r0;
  if(r0 == -1) return r1;
  if(r1 == -1) return r0;
  if(r0 <  r1){
    roots[r1] = r0;
    return r0;
  }else{
    roots[r0]=r1;
    return r1;  
  }
}

int
_add(int p, int r, int* roots)
{
  if(r==-1) 
    roots[p]=p;
  else 
    roots[p]=r;
  return roots[p];
}

void 
process(const char* imsname)
{

}

void 
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 1
int 
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;  
}

