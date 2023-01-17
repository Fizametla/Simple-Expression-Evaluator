#ifndef __BIGINT_H__
#define __BIGINT_H__

#include "VList.h"
#include <iostream>
#include <string>

namespace ds {

class BigInt {
private:
  VList<int> digits; // stores the digits of the BigInt

public:
  /**
   * Construct a new BigInt object from string.
   *
   * @param val a string of unlimited digits; default is empty string
   */
  explicit BigInt(const std::string &val = "") {
    for (unsigned j = 0; j < val.length(); j++) {
      digits.addLast(val[j] - '0');
    }
  }

  /** Override `<<` to print all digits to os. */
  friend std::ostream &operator<<(std::ostream &os, const BigInt &bi) {
    for (int i = 0; i < bi.digits.size(); i++)
      os << bi.digits.get(i);
    return os;
  }

  inline BigInt operator+(const BigInt &other) const;
  inline BigInt operator-(const BigInt &other) const;

  /** 
 * * Override < to check which BigInt list is larger 
 * @param two BigIntlists **/ 
friend bool operator<(const BigInt &a, const BigInt &b) {
  if (a.digits.size() > b.digits.size())
    return false;

  if (a.digits.size() < b.digits.size())
    return true;

  
      for(int i = 0; i < a.digits.size(); i++)
      {
        if (a.digits.get(i) < b.digits.get(i))
          return true;
        else if (a.digits.get(i) > b.digits.get(i)) 
          return false;
      }

  return false; 
}
};

/** @param BigInt list to be added to invoking BigInt list
 Return the *sum* of this BigInt and the `other` BigInt. */
BigInt BigInt::operator+(const BigInt &other) const {
  BigInt total;
  int sum= 0, carry = 0;
  int d1, d2;

  int i = digits.size() - 1;
  int j = other.digits.size() -1; 
  while(i>=0 || j >= 0){
    if (i >= 0)
      d1 = digits.get(i);
    else
      d1 = 0;
    if (j >= 0)
      d2 = other.digits.get(j);
    else
      d2 = 0;
    sum = d1 + d2 + carry;
    if (sum < 10)
      carry = 0;
    else{
      carry = 1;
      sum -= 10; 
    }
    total.digits.addFirst(sum);
    i--;
    j--;
  }
  
  if (carry == 1 )
    total.digits.addFirst(1);

  return total;
}

/** Return the *absolute difference* between this and the `other` BigInt. */
BigInt BigInt::operator-(const BigInt &other) const {
  BigInt total;
  int diff= 0, borrow = 0;
  int d1, d2; 
  int i = digits.size() - 1;
  int j = other.digits.size() -1;
  // current list - other list: current - other 
  if (other < *this)
  {
    while(i>=0 || j >= 0){
      d1 = digits.get(i);
      if (j < 0)
        d2 = 0;
      else d2 = other.digits.get(j);
      diff = d1 - d2 - borrow;
      if (diff < 0)
      {
        borrow = 1;
        diff += 10;
      }
      else 
        borrow = 0;
    total.digits.addFirst(diff);
    i--;
    j--;
    }
  }
  /** other list > current list: other - current
   */ 
  else 
  { 
    while(i>=0 || j >= 0){
      int d2 = other.digits.get(j);
      if ( i < 0)
        d1 = 0; 
      else d1 = digits.get(i); 
      diff = d2 - d1 - borrow;
      if (diff < 0)
      {
        borrow = 1;
        diff += 10;
      }
      else 
        borrow = 0;
      total.digits.addFirst(diff);
      i--;
      j--;
    }
  }
while(total.digits.getFirst() == 0){
  if (total.digits.size() == 1)
    return total; 
  else 
    total.digits.removeFirst();
}
return total;
}

} // namespace ds

#endif // __BIGINT_H__