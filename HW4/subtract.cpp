#include"interval.h"

// function which checks if the value is in range, else rotates the value.
// If there was a rotation returns true, else false
inline bool get_valid_value(int *a) {
  int b = *a;
  if (*a > interval::MAX) {
    *a = interval::MIN + (*a % (interval::MAX + 1));
    return true;
  } else if (*a < interval::MIN) {
    *a = interval::MAX + (*a % (interval::MIN - 1));
    return true;
  }
  return false;
}

interval interval::operator-(const interval &other) {
  int lowest, highest;
  bool lowRotated = false, highRotated = false;
  lowest = lo - other.hi;
  highest = hi - other.lo; 
  lowRotated = get_valid_value(&lowest);
  highRotated = get_valid_value(&highest);


  // Means one of the values(low/high) is rotated. So we have to have the
  // full set or
  // After rotation low > high, then it means the new interval is wrapped.
  // so result is full interval
  if ((lowRotated != highRotated) || (lowest > highest)){
    return interval::top();
  } else { 
    // Means both the values(low, high) have rotated. Room to optimize and 
    // give a smaller set
    
    // After rotation low < high, then this low, high is the 
    // new precise interval
    return interval(lowest, highest);
  }
}
