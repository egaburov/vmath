#pragma once

#include <cassert>

template<typename REAL>
struct Vector3;

template<typename REAL>
struct Vector3ref
{
  REAL &x, &y, &z;

  Vector3ref(REAL &_x, REAL &_y, REAL &_z) : x(_x), y(_y), z(_z) {}
  Vector3ref(const REAL &_x, const REAL &_y, const REAL &_z) : x(_x), y(_y), z(_z) {}
  Vector3ref(const Vector3<REAL>&);
  inline Vector3ref operator=(const Vector3<REAL>&);
};

template<typename REAL>
struct Vector3
{
  REAL x, y, z;
  Vector3() {};
  Vector3(const REAL _r) : x(_r), y(_r), z(_r) {}
  Vector3(const REAL _x, const REAL _y, const REAL _z) : x(_x), y(_y), z(_z) {}
  Vector3(const Vector3ref<REAL> r) : x(r.x), y(r.y), z(r.z) {}
  inline const REAL& operator[](const int i) const 
  {
    switch(i)
    {
      case 0: return x;
      case 1: return y;
      case 2: return z;
    }
    return x;
  }
  inline REAL& operator[](const int i)
  {
    switch(i)
    {
      case 0: return x;
      case 1: return y;
      case 2: return z;
    }
    return x;
  }

  REAL norm2() const { return (*this)*(*this); }
  REAL   abs() const { return REAL::sqrt(norm2); }
  Vector3 operator + (const Vector3 &v) const
  {
    return Vector3(x+v.x, y+v.y, z+v.z);
  }
  Vector3 operator - (const Vector3 &v) const
  {
    return Vector3(x-v.x, y-v.y, z-v.z);
  }
  Vector3 operator * (const Vector3 &v) const
  {
    return Vector3(x*v.x, y*v.y, z*v.z);
  }
  Vector3 operator % (const Vector3 &v) const 
  {
    return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
  }
  Vector3 operator * (const REAL s) const
  {
    return Vector3(x*s, y*s, z*s);
  }
  friend Vector3 operator * (const REAL s, const Vector3 &v)
  {
    return v*s;
  };
  Vector3 operator / (const REAL s) const
  {
    const REAL r = REAL(1.0)/s;
    return (*this)*r;
  }

  Vector3 operator-() const { return Vector3(-x,-y,-z); }

  const Vector3& operator += (const Vector3 &v) { *this = *this + v; return *this;}
  const Vector3& operator -= (const Vector3 &v) { *this = *this - v; return *this;}
  const Vector3& operator *= (const REAL     s) { *this = *this * s; return *this;}
  const Vector3& operator /= (const REAL     s) { *this = *this / s; return *this;}

  friend Vector3 maxeach (const Vector3 &a, const Vector3 &b)
  {
    return Vector3(REAL::max(a.x,b.x), REAL::max(a.y, b.y), REAL::max(a.z, b.z));
  }
  friend Vector3 mineach (const Vector3 &a, const Vector3 &b)
  {
    return Vector3(REAL::min(a.x,b.x), REAL::min(a.y, b.y), REAL::min(a.z, b.z));
  }
  friend Vector3 abseach (const Vector3 &a, const Vector3 &b)
  {
    return Vector3(REAL::abs(a.x,b.x), REAL::abs(a.y, b.y), REAL::abs(a.z, b.z));
  }

};

  template<typename REAL>
inline Vector3ref<REAL> Vector3ref<REAL>::operator=(const Vector3<REAL> &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
};

#if 0
template <class REAL> struct vector3{
  public:
    REAL x, y, z;
    vector3(){
      x = y = z = REAL(0);
    }
    vector3(const REAL &r){
      x = y = z = r;
    }
    vector3(const REAL &_x, const REAL &_y, const REAL &_z){
      x = _x;  y = _y;  z = _z;
    }
    vector3(const REAL *p){
      x = p[0]; y = p[1]; z = p[2];
    }
    ~vector3(){}

    REAL &operator [](int i){
      return (&x)[i];
    }
    template <class real> 
      operator vector3<real> () const {
        return vector3<real> (real(x), real(y), real(z));
      }
    operator REAL *(){
      return &x;
    }
    operator const REAL *() const{
      return &x;
    }
    REAL (*toPointer())[3]{
      return (REAL (*)[3])&x;
    }
    const REAL (*toConstPointer())[3]{
      return (const REAL (*)[3])&x;
    }
    typedef REAL (*pArrayOfReal3)[3];
    typedef const REAL (*cpArrayOfReal3)[3];
    operator pArrayOfReal3(){
      return toPointer();
    }
    operator cpArrayOfReal3(){
      return toConstPointer();
    }

    void outv(std::ostream &ofs = std::cout) const{
      ofs << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
    bool are_numbers () const{
      // returns false if *this has (a) NaN member(s)
      return (norm2() >= REAL(0));
    }

    REAL norm2() const{
      return (*this)*(*this);
    }
    REAL abs() const{
      return std::sqrt(norm2());
    }

    friend std::ostream &operator << (std::ostream &ofs, const vector3<REAL> &v){
      ofs << v.x << " " << v.y << " " << v.z;
      return ofs;
    }
    friend std::istream &operator >> (std::istream &ifs, vector3<REAL> &v){
      ifs >> v.x >> v.y >> v.z;
      return ifs;
    }
    const vector3<REAL> operator + (const vector3<REAL> &v) const{
      return vector3<REAL> (x+v.x, y+v.y, z+v.z);
    }
    const vector3<REAL> operator - (const vector3<REAL> &v) const{
      return vector3<REAL> (x-v.x, y-v.y, z-v.z);
    }
    const vector3<REAL> operator * (const REAL &s) const{
      return vector3<REAL> (x*s, y*s, z*s);
    }
    friend const vector3<REAL> operator * (const REAL &s, const vector3<REAL> &v){
      return v*s;
    }
    // dot product
    const REAL operator * (const vector3<REAL> &v) const{
      return (x*v.x + y*v.y + z*v.z);
    }
    const vector3<REAL> cross(const vector3<REAL> &v) const 
    {
      return vector3<REAL>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
    // vector product
    const vector3<REAL> operator % (const vector3<REAL> &v) const{
      return vector3<REAL> (
          y*v.z - z*v.y, 
          z*v.x - x*v.z, 
          x*v.y - y*v.x);
    }
    const vector3<REAL> operator / (const REAL &s) const{
      REAL r = REAL(1)/s;
      return (*this)*r;
    }
    const vector3<REAL> operator = (const vector3<REAL> &v){
      x = v.x; y=v.y; z=v.z;
      return *this;
    }

    const vector3<REAL> operator - () const {
      return vector3<REAL> (-x, -y, -z);
    }
    const vector3<REAL> &operator += (const vector3<REAL> &v){
      *this = *this + v;
      return *this;
    }
    const vector3<REAL> &operator -= (const vector3<REAL> &v){
      *this = *this - v;
      return *this;
    }
    const vector3<REAL> &operator *= (const REAL &s){
      *this = *this * s;
      return *this;
    }
    const vector3<REAL> &operator /= (const REAL &s){
      *this = *this / s;
      return *this;
    }

    friend const vector3<REAL> maxeach (const vector3<REAL> &a, const vector3<REAL> &b){
      return vector3<REAL> (std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
    }
    friend const vector3<REAL> mineach (const vector3<REAL> &a, const vector3<REAL> &b){
      return vector3<REAL> (std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    }
    const vector3<REAL> abseach() const {
      return vector3<REAL> (std::fabs(x), std::fabs(y), std::fabs(z));
    }
};

typedef double real;
typedef vector3<real> vec3;

#endif
