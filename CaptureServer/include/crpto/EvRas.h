#ifndef EV_RAS_H
#define EV_RAS_H

#include <iostream>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32

#pragma warning (disable : 4334)

typedef __int64 _INT64_;
typedef unsigned __int64 _UINT64_;

#else

typedef long long _INT64_;
typedef unsigned long long	_UINT64_;

#endif

using namespace std;//RSA算法所需参数

struct  RSA_PARAM
{
	_UINT64_    p, q;   //两个素数，不参与加密解密运算
	_UINT64_    f;      //f=(p-1)*(q-1)，不参与加密解密运算
	_UINT64_    n, e;   //公匙，n=p*q，gcd(e,f)=1 
	_UINT64_    d;      //私匙，e*d=1 (mod f)，gcd(n,d)=1
	_UINT64_    s;      //块长，满足2^s<=n的最大的s，即log2(n)

	RSA_PARAM(){};

	RSA_PARAM(_UINT64_ p64, _UINT64_ q64, _UINT64_ f64, _UINT64_ n64, _UINT64_ e64, _UINT64_ d64, _UINT64_ s64)
	{
		p = p64;
		q = q64;
		f = f64;
		n = n64;
		e = e64;
		d = d64;
		s = s64;
	}
} ;//小素数表

class  RandNumber
{
private:
	_UINT64_ randSeed;
public:
	RandNumber(_UINT64_ s = 0);
	_UINT64_ Random(_UINT64_ n);
};

// 模乘运算，返回值 x = a*b mod n
inline _UINT64_ MulMod(_UINT64_ a, _UINT64_ b, _UINT64_ n)
{
	return a * b % n;
}

// 模幂运算，返回值 x=base^pow mod n
_UINT64_ PowMod(_UINT64_ &base, _UINT64_ &pow, _UINT64_ &n);

// Rabin-Miller素数测试，通过测试返回1，否则返回0。
// n是待测素数。
// 注意：通过测试并不一定就是素数，非素数通过测试的概率是1/4
long RabinMillerKnl(_UINT64_ &n);

// Rabin-Miller素数测试，循环调用核心loop次
// 全部通过返回1，否则返回0
long RabinMiller(_UINT64_ &n, long loop);

// 随机生成一个bits位(二进制位)的素数，最多32位
_UINT64_ RandomPrime(char bits);

// 欧几里得法求最大公约数
_UINT64_ EuclidGcd(_UINT64_ &p, _UINT64_ &q);

// Stein法求最大公约数
_UINT64_ SteinGcd(_UINT64_ &p, _UINT64_ &q);

// 已知a、b，求x，满足a*x =1 (mod b)
// 相当于求解a*x-b*y=1的最小整数解
_UINT64_ Euclid(_UINT64_ &a, _UINT64_ &b);

// 随机产生一个RSA加密参数
RSA_PARAM RsaGetParam(void);

#endif