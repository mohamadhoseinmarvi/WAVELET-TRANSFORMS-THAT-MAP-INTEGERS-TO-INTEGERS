
template <class T>
class delta_trans
{
public:

  void forward( T *vec, size_t len )
  {
    if (vec != 0 && len > 0) {
      T next;
      T refVal = vec[0];

      for (size_t i = 1; i < len; i++) {
	next = vec[i];
	vec[i] = vec[i] - refVal;
	refVal = next;
      }
    }
  } 

  void inverse( T *vec, size_t len )
  {
    if (vec != 0 && len > 0) {
      for (size_t i = 1; i < len; i++) {
	vec[i] = vec[i] + vec[i-1];
      }
    }
  } // inverse

}; // delta_trans
